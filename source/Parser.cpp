// ======================================================================
/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "CloudAreaBorder.h"
#include "ColdFront.h"
#include "FontSymbol.h"
#include "GraphicSymbol.h"
#include "Jet.h"
#include "MeteorologicalAnalysis.h"
#include "OccludedFront.h"
#include "PointMeteorologicalSymbol.h"
#include "Trough.h"
#include "UpperTrough.h"
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

void
require_whitespace(const xmlpp::TextReader & theReader)
{
  if(!theReader.has_value())
	return;

  std::string text = theReader.get_value();
  if(!boost::algorithm::all(text,boost::algorithm::is_space()))
	throw std::runtime_error("Non whitespace between XML tags: "+text);

}

// ----------------------------------------------------------------------
/*!
 * \brief Read the value field coming up
 */
// ----------------------------------------------------------------------

std::string read_text_value(xmlpp::TextReader & theReader)
{
  theReader.read();
  std::string value = theReader.get_value();
  theReader.next();
  return value;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse #text XML time
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime
parse_text_time(xmlpp::TextReader & theReader)
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
 * \brief Parse a point
 */
// ----------------------------------------------------------------------

Point
parse_text_point(xmlpp::TextReader & theReader)
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
 * \brief Parse gml:TimeInstant
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime
parse_gml_time_instant(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime t(boost::posix_time::not_a_date_time);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
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

boost::posix_time::time_period
parse_gml_time_period(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime starttime(boost::posix_time::not_a_date_time);
  boost::posix_time::ptime endtime(boost::posix_time::not_a_date_time);
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
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

boost::posix_time::time_period
parse_gml_valid_time(xmlpp::TextReader & theReader)
{
  boost::posix_time::ptime badtime(boost::posix_time::not_a_date_time);
  boost::posix_time::time_period period(badtime,badtime);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:TimeInstant")
		{
		  boost::posix_time::ptime t = parse_gml_time_instant(theReader);
		  period = boost::posix_time::time_period(t,t);
		}
	  else if(name == "gml:TimePeriod")
		period = parse_gml_time_period(theReader);
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
 * \brief Parse metobj:shortInfo
 */
// ----------------------------------------------------------------------

std::pair<std::string,std::string>
parse_metobj_short_info(xmlpp::TextReader & theReader)
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

std::pair<std::string,std::string>
parse_metobj_long_info(xmlpp::TextReader & theReader)
{
  std::string lang = theReader.get_attribute("xml:lang");
  std::string value = theReader.get_value();
  theReader.next();
  return std::make_pair(lang,value);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:Point
 */
// ----------------------------------------------------------------------

Point
parse_gml_point(xmlpp::TextReader & theReader)
{
  Point p(0,0);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:pos")
		p = parse_text_point(theReader);
	  else if(name == "gml:Point")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in Point");
	}

  return p;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:pointProperty
 */
// ----------------------------------------------------------------------

Point
parse_gml_point_property(xmlpp::TextReader & theReader)
{
  Point p(0,0);
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:Point")
		p = parse_gml_point(theReader);
	  else if(name == "gml:pointProperty")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in pointProperty");
	}

  return p;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse Envelope
 */
// ----------------------------------------------------------------------

Envelope
parse_gml_envelope(xmlpp::TextReader & theReader)
{
  Point lc(0,0), uc(0,0);
  bool lc_ok = false, uc_ok = false;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:lowerCorner")
		{
		  lc = parse_text_point(theReader);
		  lc_ok = true;
		}
	  else if(name == "gml:upperCorner")
		{
		  uc = parse_text_point(theReader);
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

Envelope
parse_gml_bounded_by(xmlpp::TextReader & theReader)
{
  Envelope env;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:Envelope")
		env = parse_gml_envelope(theReader);
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

SimpleCubicSpline
parse_metobj_simple_cubic_spline(xmlpp::TextReader & theReader)
{
  SimpleCubicSpline spline;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
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

CubicSplineCurve
parse_metobj_cubic_spline_segments(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:SimpleCubicSpline")
		curve.add(parse_metobj_simple_cubic_spline(theReader));
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

CubicSplineCurve
parse_metobj_cubic_spline_curve(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:cubicSplineSegments")
		curve = parse_metobj_cubic_spline_segments(theReader);
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

CubicSplineCurve
parse_metobj_control_curve(xmlpp::TextReader & theReader)
{
  CubicSplineCurve curve;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:CubicSplineCurve")
		curve = parse_metobj_cubic_spline_curve(theReader);
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
 * \brief Parse metobj:SRGBColor
 */
// ----------------------------------------------------------------------

SRGBColor
parse_metobj_srgb_color(xmlpp::TextReader & theReader)
{
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 255;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:red")
		r = boost::lexical_cast<int>(read_text_value(theReader));
	  else if(name == "metobj:green")
		g = boost::lexical_cast<int>(read_text_value(theReader));
	  else if(name == "metobj:blue")
		b = boost::lexical_cast<int>(read_text_value(theReader));
	  else if(name == "metobj:alpha")
		a = boost::lexical_cast<int>(read_text_value(theReader));
	  else if(name == "metobj:SRGBColor")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in SRGBColor");
	}
  
  return SRGBColor(r,g,b,a);

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:color
 */
// ----------------------------------------------------------------------

SRGBColor
parse_metobj_color(xmlpp::TextReader & theReader)
{
  SRGBColor color(0,0,0,255);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:SRGBColor")
		color = parse_metobj_srgb_color(theReader);
	  else if(name == "metobj:color")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in color");
	}
  
  return color;

}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:FontSymbol
 */
// ----------------------------------------------------------------------

FontSymbol *
parse_metobj_font_symbol(xmlpp::TextReader & theReader)
{
  std::string fontname;
  int symbolindex = 0;
  double fontsize = 0;
  SRGBColor color(0,0,0,0);

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:knownSymbol")
		theReader.next();
	  else if(name == "metobj:localizedSymbolName")
		theReader.next();
	  else if(name == "metobj:fontName")
		fontname = read_text_value(theReader);
	  else if(name == "metobj:symbolIndex")
		symbolindex = boost::lexical_cast<int>(read_text_value(theReader));
	  else if(name == "metobj:fontSizePoints")
		fontsize = boost::lexical_cast<double>(read_text_value(theReader));
	  else if(name == "metobj:color")
		color = parse_metobj_color(theReader);
	  else if(name == "metobj:FontSymbol")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in FontSymbol");
	}

  return new FontSymbol(fontname,fontsize,symbolindex,color);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GraphicSymbol
 */
// ----------------------------------------------------------------------

GraphicSymbol *
parse_metobj_graphic_symbol(xmlpp::TextReader & theReader)
{
  return 0; // TODO
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:meteorologicalSymbolProperty
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol *
parse_metobj_meteorological_symbol_property(xmlpp::TextReader & theReader)
{
  MeteorologicalSymbol * symbol = 0;
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:FontSymbol")
		{
		  if(symbol) delete symbol;
		  symbol = parse_metobj_font_symbol(theReader);
		}
	  else if(name == "metobj:GraphicSymbol")
		{
		  if(symbol) delete symbol;
		  symbol = parse_metobj_graphic_symbol(theReader);
		}
	  else if(name == "metobj:meteorologicalSymbolProperty")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in meteorologicalSymbolProperty");
	}

  return symbol;
}



// ----------------------------------------------------------------------
/*!
 * \brief Parse a warm front description
 */
// ----------------------------------------------------------------------

WarmFront *
parse_metobj_warm_front(xmlpp::TextReader & theReader)
{
  WarmFront * front = new WarmFront;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		front->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		front->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		front->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		front->connectEndPoint(theReader.get_attribute("xlin:href"));
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
 * \brief Parse a occluded front description
 */
// ----------------------------------------------------------------------

OccludedFront *
parse_metobj_occluded_front(xmlpp::TextReader & theReader)
{
  OccludedFront * front = new OccludedFront;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		front->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		front->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		front->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		front->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:OccludedFront")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in OccludedFront");
	}
  return front;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:ColdFront
 */
// ----------------------------------------------------------------------

ColdFront *
parse_metobj_cold_front(xmlpp::TextReader & theReader)
{
  ColdFront * front = new ColdFront;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		front->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		front->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		front->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		front->connectEndPoint(theReader.get_attribute("xlin:href"));
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
 * \brief Parse metobj:CloudAreaBorder
 */
// ----------------------------------------------------------------------

CloudAreaBorder *
parse_metobj_cloud_area_border(xmlpp::TextReader & theReader)
{
  CloudAreaBorder * cloud = new CloudAreaBorder;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		cloud->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		cloud->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		cloud->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		cloud->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:CloudAreaBorder")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in CloudAreaBorder");
	}
  return cloud;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:Jet
 */
// ----------------------------------------------------------------------

Jet *
parse_metobj_jet(xmlpp::TextReader & theReader)
{
  Jet * jet = new Jet;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		jet->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		jet->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		jet->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		jet->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:Jet")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in Jet");
	}
  return jet;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:Trough
 */
// ----------------------------------------------------------------------

Trough *
parse_metobj_trough(xmlpp::TextReader & theReader)
{
  Trough * trough = new Trough;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		trough->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		trough->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		trough->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		trough->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:Trough")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in Trough");
	}
  return trough;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:UpperTrough
 */
// ----------------------------------------------------------------------

UpperTrough *
parse_metobj_upper_trough(xmlpp::TextReader & theReader)
{
  UpperTrough * trough = new UpperTrough;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		trough->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		trough->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		trough->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		trough->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "metobj:UpperTrough")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in UpperTrough");
	}
  return trough;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse a point meteorologial symbol
 */
// ----------------------------------------------------------------------

PointMeteorologicalSymbol *
parse_metobj_point_meteorological_symbol(xmlpp::TextReader & theReader)
{
  PointMeteorologicalSymbol * symbol = new PointMeteorologicalSymbol;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:boundedBy")
		symbol->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		parse_gml_valid_time(theReader);
	  else if(name == "metobj:creationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		parse_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == "gml:pointProperty")
		symbol->point(parse_gml_point_property(theReader));
	  else if(name == "metobj:meteorologicalSymbolProperty")
		symbol->symbol(parse_metobj_meteorological_symbol_property(theReader));
	  else if(name == "metobj:PointMeteorologicalSymbol")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in PointMeteorologicalSymbol");
	}
  return symbol;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a meteorological feature
 */
// ----------------------------------------------------------------------

template <typename T>
void
parse_gml_feature_member(T & theWeatherObject,
						 xmlpp::TextReader & theReader)
{
  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "metobj:WarmFront")
		theWeatherObject.addFeature(parse_metobj_warm_front(theReader));
	  else if(name == "metobj:ColdFront")
		theWeatherObject.addFeature(parse_metobj_cold_front(theReader));
	  else if(name == "metobj:OccludedFront")
		theWeatherObject.addFeature(parse_metobj_occluded_front(theReader));
	  else if(name == "metobj:CloudAreaBorder")
		theWeatherObject.addFeature(parse_metobj_cloud_area_border(theReader));
	  else if(name == "metobj:Jet")
		theWeatherObject.addFeature(parse_metobj_jet(theReader));
	  else if(name == "metobj:Trough")
		theWeatherObject.addFeature(parse_metobj_trough(theReader));
	  else if(name == "metobj:UpperTrough")
		theWeatherObject.addFeature(parse_metobj_upper_trough(theReader));
	  else if(name == "metobj:PointMeteorologicalSymbol")
		theWeatherObject.addFeature(parse_metobj_point_meteorological_symbol(theReader));
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
 * \brief Parse woml::ConnectionPoint
 */
// ----------------------------------------------------------------------

SharedConnectionPoints::value_type
parse_metobj_connection_point(xmlpp::TextReader & theReader)
{
  std::string id = theReader.get_attribute("gml:id");
  Point p(0,0);
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:pos")
		p = parse_text_point(theReader);
	  else if(name == "metobj:ConnectionPoint")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in ConnectionPoint");
	}

  return SharedConnectionPoints::value_type(id,p);

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml::sharedConnectionPoints
 */
// ----------------------------------------------------------------------

SharedConnectionPoints
parse_metobj_shared_connection_points(xmlpp::TextReader & theReader)
{
  SharedConnectionPoints points;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:ConnectionPoint")
		points.insert(parse_metobj_connection_point(theReader));
	  else if(name == "metobj:sharedConnectionPoints")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in sharedConnectionPoints");
	}

  return points;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse WeatherAnalysis data
 */
// ----------------------------------------------------------------------

boost::shared_ptr<MeteorologicalAnalysis>
parse_metobj_meteorological_analysis(xmlpp::TextReader & theReader)
{
  boost::shared_ptr<MeteorologicalAnalysis>
	analysis(new MeteorologicalAnalysis());

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:featureMember")
		parse_gml_feature_member(*analysis,theReader);
	  else if(name == "gml:validTime")
		analysis->validTime(parse_gml_valid_time(theReader));
	  else if(name == "metobj:metaData")
		theReader.next();
	  else if(name == "metobj:creationTime")
		analysis->creationTime(parse_text_time(theReader));
	  else if(name == "metobj:analysisTime")
		analysis->analysisTime(parse_text_time(theReader));
	  else if(name == "metobj:latestModificationTime")
		analysis->latestModificationTime(parse_text_time(theReader));
	  else if(name == "metobj:sharedConnectionPoints")
		analysis->addConnectionPoints(parse_metobj_shared_connection_points(theReader));
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
parse_metobj_weather_forecast(xmlpp::TextReader & theReader)
{
  boost::shared_ptr<WeatherForecast>
	forecast(new WeatherForecast());

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:name")
		theReader.next();
	  else if(name == "gml:featureMember")
		parse_gml_feature_member(*forecast,theReader);
	  else if(name == "gml:validTime")
		forecast->validTime(parse_gml_valid_time(theReader));
	  else if(name == "metobj:metaData")
		theReader.next();
	  else if(name == "metobj:creationTime")
		forecast->creationTime(parse_text_time(theReader));
	  else if(name == "metobj:analysisTime")
		forecast->analysisTime(parse_text_time(theReader));
	  else if(name == "metobj:forecastTime")
		forecast->forecastTime(parse_text_time(theReader));
	  else if(name == "metobj:latestModificationTime")
		forecast->latestModificationTime(parse_text_time(theReader));
	  else if(name == "metobj:sharedConnectionPoints")
		forecast->addConnectionPoints(parse_metobj_shared_connection_points(theReader));
	  else if(name == "metobj:shortInfo")
		theReader.next();
	  else if(name == "metobj:longInfo")
		theReader.next();
	  else if(name == "metobj:targetRegion")
		theReader.next();
	  else if(name == "metobj:WeatherForecast")
		break;
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

Weather
parse(const boost::filesystem::path & thePath)
{
  xmlpp::TextReader reader(thePath.file_string());

  Weather weather;

  while(reader.read())
	{
	  std::string name = reader.get_name();

	  if(name == "#text")
		require_whitespace(reader);
	  else if(name == "#comment")
		reader.next();
	  if(name == "metobj:WeatherForecast")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  weather.forecast(parse_metobj_weather_forecast(reader));
		}
	  else if(name == "metobj:MeteorologicalAnalysis")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  weather.analysis(parse_metobj_meteorological_analysis(reader));
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
