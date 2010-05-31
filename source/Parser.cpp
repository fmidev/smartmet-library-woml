// ======================================================================
/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "MeteorologicalAnalysis.h"
#include "WarmFront.h"
#include "Weather.h"

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <iostream>
#include <stdexcept>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Require value between tags to be whitespace only
 */
// ----------------------------------------------------------------------

void require_whitespace(const xmlpp::TextReader & theReader)
{
  if(!theReader.has_value())
	return;

  std::string text = theReader.get_value();
  if(!boost::algorithm::all(text,boost::algorithm::is_space()))
	throw std::runtime_error("Non whitespace between XML tags: "+text);

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a point
 */
// ----------------------------------------------------------------------

Point parse_point(xmlpp::TextReader & theReader)
{
  // TODO: Parse text content
  return Point(0,0);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse Envelope
 */
// ----------------------------------------------------------------------

Envelope parse_envelope(xmlpp::TextReader & theReader)
{
  Point lc(0,0), uc(0,0);
  bool lc_ok = false, uc_ok = false;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:lowerCorner")
		{
		  lc = parse_point(theReader);
		  lc_ok = true;
		}
	  else if(name == "gml:upperCorner")
		{
		  uc = parse_point(theReader);
		  uc_ok = true;
		}
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in Envelope");
	}

  if(lc_ok & uc_ok)
	return Envelope(lc,uc);
  else
	throw std::runtime_error("Invalid corner spec in Envelope");

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a boundedBy object
 */
// ----------------------------------------------------------------------

Envelope parse_boundedby(xmlpp::TextReader & theReader)
{
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:Envelope")
		return parse_envelope(theReader);
	  else if(name == "gml:Null")
		return Envelope();
	  else if(name == "#text")
		require_whitespace(theReader);
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in boundedBy");
	}
  throw std::runtime_error("boundedBy not fully defined");

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a warm front description
 */
// ----------------------------------------------------------------------

WarmFront * parse_warmfront(xmlpp::TextReader & theReader)
{
  WarmFront * front = new WarmFront();

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		;
	  else if(name == "gml:boundedBy")
		front->envelope(parse_boundedby(theReader));
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in WarmFront");
	}
  return front;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a meteorological feature
 */
// ----------------------------------------------------------------------

void parse_feature(MeteorologicalAnalysis & theAnalysis,
				   xmlpp::TextReader & theReader)
{
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "metobj:WarmFront")
		theAnalysis.addFeature(parse_warmfront(theReader));
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in MeteorologicalAnalysis featureMembers");
	}
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse WeatherAnalysis data
 */
// ----------------------------------------------------------------------

boost::shared_ptr<MeteorologicalAnalysis>
parse_weatheranalysis(xmlpp::TextReader & theReader)
{
  boost::shared_ptr<MeteorologicalAnalysis>
	analysis(new MeteorologicalAnalysis());

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		;
	  else if(name == "gml:featureMember")
		parse_feature(*analysis,theReader);
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in MeteorologicalAnalysis");
	}
  return analysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse WeatherForecast data
 */
// ----------------------------------------------------------------------

boost::shared_ptr<WeatherForecast>
parse_weatherforecast(const xmlpp::TextReader & theReader)
{
  return boost::shared_ptr<WeatherForecast>();
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a WOML file
 */
// ----------------------------------------------------------------------

Weather parse(const boost::filesystem::path & thePath)
{
  xmlpp::TextReader reader(thePath.file_string());

  Weather weather;

  while(reader.read())
	{
	  std::string name = reader.get_name();
	  if(name == "metobj:WeatherForecast")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  weather.forecast(parse_weatherforecast(reader));
		}
	  else if(name == "metobj:MeteorologicalAnalysis")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  weather.analysis(parse_weatheranalysis(reader));
		}
	  else if(name == "#text")
		require_whitespace(reader);
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> at top level of "
								 + thePath.file_string());

	}

  return weather;
}



} // namespace woml
