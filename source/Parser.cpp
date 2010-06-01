// ======================================================================
/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "ColdFront.h"
#include "MeteorologicalAnalysis.h"
#include "WarmFront.h"
#include "Weather.h"
#include "WeatherForecast.h"

#include <smartmet/macgyver/TimeParser.h>

#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>
#include <iostream>
#include <sstream>
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
 * \brief Parse #text XML time
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime parse_text_time(xmlpp::TextReader & theReader)
{
  if(!theReader.read())
	throw std::runtime_error("Time element missing from XML");

  if(theReader.get_name() != "#text")
	throw std::runtime_error("Expecting XML time in #text, not "+theReader.get_name());

  boost::posix_time::ptime t = Fmi::TimeParser::parse_xml(theReader.get_value());
  theReader.next();
  return t;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimeInstant
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime parse_timeinstant(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime t(boost::posix_time::not_a_date_time);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:timePosition")
		t = parse_text_time(theReader);
	  else if(name == "gml:TimeInstant")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in TimeInstant");
	}

  if(t.is_not_a_date_time())
	throw std::runtime_error("Invalid TimeInstant");

  return t;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimePeriod
 */
// ----------------------------------------------------------------------

boost::posix_time::time_period parse_timeperiod(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime starttime(boost::posix_time::not_a_date_time);
  boost::posix_time::ptime endtime(boost::posix_time::not_a_date_time);
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:beginPosition")
		starttime = parse_text_time(theReader);
	  else if(name == "gml:endPosition")
		endtime = parse_text_time(theReader);
	  else if(name == "gml:TimePeriod")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in TimeInstant");
	}

  return boost::posix_time::time_period(starttime,endtime);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:ValidTime
 */
// ----------------------------------------------------------------------

boost::posix_time::time_period parse_validtime(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime badtime(boost::posix_time::not_a_date_time);
  boost::posix_time::time_period period(badtime,badtime);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:TimeInstant")
		{
		  boost::posix_time::ptime t = parse_timeinstant(theReader);
		  period = boost::posix_time::time_period(t,t);
		}
	  else if(name == "gml:TimePeriod")
		period = parse_timeperiod(theReader);
	  else if(name == "gml:validTime")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in validTime");
	}

  return period;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:latestModificationTime
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime parse_latestmodificationtime(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime t = Fmi::TimeParser::parse_xml(theReader.get_value());
  theReader.next();
  return t;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:shortInfo
 */
// ----------------------------------------------------------------------

std::pair<std::string,std::string> parse_shortinfo(xmlpp::TextReader & theReader)
{
  std::string lang = theReader.get_attribute("xml:lang");
  std::string value = theReader.get_value();
  theReader.next();
  return std::make_pair(lang,value);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:longInfo
 */
// ----------------------------------------------------------------------

std::pair<std::string,std::string> parse_longinfo(xmlpp::TextReader & theReader)
{
  std::string lang = theReader.get_attribute("xml:lang");
  std::string value = theReader.get_value();
  theReader.next();
  return std::make_pair(lang,value);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a point
 */
// ----------------------------------------------------------------------

Point parse_point(xmlpp::TextReader & theReader)
{
  if(!theReader.read())
	throw std::runtime_error("Error in coordinate specifications");

  if(theReader.get_name() != "#text")
	throw std::runtime_error("Error in coordinate specifications, text part missing");

  if(!theReader.has_value())
	throw std::runtime_error("Text part missing from coordinate element");

  std::stringstream s;
  s.str(theReader.get_value());
  double lat, lon;
  s >> lat >> lon;
  if(s.fail())
	throw std::runtime_error("Failed to parse coordinate element");

  theReader.next();

  return Point(lon,lat);
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
	  else if(name == "gml:Envelope")
		break;
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
  Envelope env;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:Envelope")
		env = parse_envelope(theReader);
	  else if(name == "gml:Null")
		;
	  else if(name == "gml:boundedBy")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in boundedBy");
	}
  return env;

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:SimpleCubicSpline
 */
// ----------------------------------------------------------------------

SimpleCubicSpline parse_simplecubicspline(xmlpp::TextReader & theReader)
{
  SimpleCubicSpline spline;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:posList")
		{
		  theReader.read();
		  if(theReader.get_name() != "#text")
			throw std::runtime_error("#text missing from SimpleCubicSpline");
		  
		  if(!theReader.has_value())
			throw std::runtime_error("Text part missing from simple cubic spline");

		  std::stringstream s;

		  s.str(theReader.get_value());
		  while(s.good())
			{
			  double lon, lat;
			  s >> lat >> lon;
			  if(s.fail())
				throw std::runtime_error("Error parsing "+theReader.get_value());
			  spline.add(Point(lon,lat));
			}

		  theReader.next();
		}
	  else if(name == "metobj:vectorAtStart")
		theReader.next();
	  else if(name == "metobj:vectorAtEnd")
		theReader.next();
	  else if(name == "metobj:SimpleCubicSpline")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in SimpleCubicSpline");
	}

  return spline;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:cubicSplineSegments
 */
// ----------------------------------------------------------------------

CubicSplineCurve parse_cubicsplinesegments(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "metobj:SimpleCubicSpline")
		curve.add(parse_simplecubicspline(theReader));
	  else if(name == "metobj:cubicSplineSegments")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in cubicSplineSegments");
	}

  return curve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:CubicSplineCurve
 */
// ----------------------------------------------------------------------

CubicSplineCurve parse_cubicsplinecurve(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "metobj:cubicSplineSegments")
		curve = parse_cubicsplinesegments(theReader);
	  else if(name == "metobj:CubicSplineCurve")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in CubicSplineCurve");
	}

  return curve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:controlCurve
 */
// ----------------------------------------------------------------------

CubicSplineCurve parse_controlcurve(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "metobj:CubicSplineCurve")
		curve = parse_cubicsplinecurve(theReader);
	  else if(name == "metobj:controlCurve")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in controlCurve");
	}

  return curve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a warm front description
 */
// ----------------------------------------------------------------------

WarmFront * parse_warmfront(xmlpp::TextReader & theReader)
{
  WarmFront * front = new WarmFront;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		front->envelope(parse_boundedby(theReader));
	  else if(name == "gml:validTime")
		parse_validtime(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_shortinfo(theReader);
	  else if(name == "metobj:longInfo")
		parse_longinfo(theReader);
	  else if(name == "metobj:controlCurve")
		front->controlCurve(parse_controlcurve(theReader));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:WarmFront")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in WarmFront");
	}
  return front;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a cold front description
 */
// ----------------------------------------------------------------------

ColdFront * parse_coldfront(xmlpp::TextReader & theReader)
{
  ColdFront * front = new ColdFront;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		front->envelope(parse_boundedby(theReader));
	  else if(name == "gml:validTime")
		parse_validtime(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_shortinfo(theReader);
	  else if(name == "metobj:longInfo")
		parse_longinfo(theReader);
	  else if(name == "metobj:controlCurve")
		front->controlCurve(parse_controlcurve(theReader));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:ColdFront")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in ColdFront");
	}
  return front;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a meteorological feature
 */
// ----------------------------------------------------------------------

void parse_featuremember(MeteorologicalAnalysis & theAnalysis,
						 xmlpp::TextReader & theReader)
{
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "metobj:WarmFront")
		theAnalysis.addFeature(parse_warmfront(theReader));
	  else if(name == "metobj:ColdFront")
		theAnalysis.addFeature(parse_coldfront(theReader));
	  else if(name == "gml:featureMember")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in featureMember");
	}
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a meteorological feature
 */
// ----------------------------------------------------------------------

void parse_featuremember(WeatherForecast & theForecast,
						 xmlpp::TextReader & theReader)
{
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "metobj:WarmFront")
		theForecast.addFeature(parse_warmfront(theReader));
	  else if(name == "gml:featureMember")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in featureMember");
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
		theReader.next();
	  else if(name == "gml:featureMember")
		parse_featuremember(*analysis,theReader);
	  else if(name == "gml:validTime")
		analysis->validTime(parse_validtime(theReader));
	  else if(name == "metobj:metaData")
		theReader.next();
	  else if(name == "metobj:creationTime")
		analysis->creationTime(parse_text_time(theReader));
	  else if(name == "metobj:analysisTime")
		analysis->analysisTime(parse_text_time(theReader));
	  else if(name == "metobj:latestModificationTime")
		analysis->latestModificationTime(parse_text_time(theReader));
	  else if(name == "metobj:shortInfo")
		theReader.next();
	  else if(name == "metobj:longInfo")
		theReader.next();
	  else if(name == "metobj:targetRegion")
		theReader.next();
	  else if(name == "metobj:usedReferenceData")
		theReader.next();
	  else if(name == "metobj:MeteorologicalAnalysis")
		break;
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
parse_weatherforecast(xmlpp::TextReader & theReader)
{
  boost::shared_ptr<WeatherForecast>
	forecast(new WeatherForecast());

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:featureMember")
		parse_featuremember(*forecast,theReader);
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in WeatherForecast");
	}
  return forecast;
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
