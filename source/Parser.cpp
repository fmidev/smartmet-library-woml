// ======================================================================
/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "CloudAreaBorder.h"
#include "ColdFront.h"
#include "DataSource.h"
#include "FontSymbol.h"
#include "GeophysicalParameterValueSet.h"
#include "GraphicSymbol.h"
#include "Jet.h"
#include "MeteorologicalAnalysis.h"
#include "NumericalModelRun.h"
#include "OccludedFront.h"
#include "PointGeophysicalParameterValueSet.h"
#include "PointMeteorologicalSymbol.h"
#include "PointNote.h"
#include "SurfacePrecipitationArea.h"
#include "Trough.h"
#include "UpperTrough.h"
#include "WarmFront.h"
#include "Weather.h"
#include "WeatherForecast.h"

#include <smartmet/macgyver/TimeParser.h>

#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

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
read_text_time(xmlpp::TextReader & theReader)
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
read_text_point(xmlpp::TextReader & theReader)
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
  boost::optional<boost::posix_time::ptime> t;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:timePosition")
		t = read_text_time(theReader);
	  else if(name == "gml:TimeInstant")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in gml:TimeInstant");
	}

  if(t->is_not_a_date_time())
	throw std::runtime_error("Invalid gml:TimeInstant");

  return *t;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimePeriod
 */
// ----------------------------------------------------------------------

boost::posix_time::time_period
parse_gml_time_period(xmlpp::TextReader & theReader)
{
  boost::optional<boost::posix_time::ptime> starttime;
  boost::optional<boost::posix_time::ptime> endtime;
  
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:beginPosition")
		starttime = read_text_time(theReader);
	  else if(name == "gml:endPosition")
		endtime = read_text_time(theReader);
	  else if(name == "gml:TimePeriod")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in gml:TimePeriod");
	}

  return boost::posix_time::time_period(*starttime,*endtime);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:validTime
 */
// ----------------------------------------------------------------------

boost::posix_time::time_period
parse_gml_valid_time(xmlpp::TextReader & theReader)
{
  boost::optional<boost::posix_time::time_period> period;

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
								 + "> in gml:validTime");
	}

  return *period;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:validTime expecting time instant only!
 */
// ----------------------------------------------------------------------

boost::posix_time::ptime
parse_gml_valid_time_instant(xmlpp::TextReader & theReader)
{
  boost::posix_time::time_period p = parse_gml_valid_time(theReader);

  if(!p.is_null())
	{
	  throw std::runtime_error("Meteorological features should not have time periods but time instants");
	}

  return p.begin();
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
  boost::optional<Point> p;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:pos")
		p = read_text_point(theReader);
	  else if(name == "gml:Point")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in gml:Point");
	}

  return *p;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:pointProperty
 */
// ----------------------------------------------------------------------

Point
parse_gml_point_property(xmlpp::TextReader & theReader)
{
  boost::optional<Point> p;
  
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
								 + "> in gml:pointProperty");
	}

  return *p;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse Envelope
 */
// ----------------------------------------------------------------------

Envelope
parse_gml_envelope(xmlpp::TextReader & theReader)
{
  boost::optional<Point> lc, uc;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();
	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "gml:lowerCorner")
		lc = read_text_point(theReader);
	  else if(name == "gml:upperCorner")
		uc = read_text_point(theReader);
	  else if(name == "gml:Envelope")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in gml:Envelope");
	}

  if(lc && uc)
	return Envelope(*lc,*uc);
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
  boost::optional<Envelope> env;

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
								 + "> in gml:boundedBy");
	}
  return *env;

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
			throw std::runtime_error("#text missing from metobj:SimpleCubicSpline");
		  
		  if(!theReader.has_value())
			throw std::runtime_error("Text part missing from metobj:SimpleCubicSpline");
		  std::stringstream s;

		  s.str(theReader.get_value());
		  while(s.good())
			{
			  double lon, lat;
			  s >> lat >> lon;
			  if(s.fail())
				throw std::runtime_error("Error parsing value '"+theReader.get_value()+"' in metobj:SimpleCubicSpline" );
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
								 + "> in metobj:SimpleCubicSpline");
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
								 + "> in metobj:cubicSplineSegments");
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
  boost::optional<CubicSplineCurve> curve;

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
								 + "> in metobj:CubicSplineCurve");
	}

  return *curve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:controlCurve
 */
// ----------------------------------------------------------------------

CubicSplineCurve
parse_metobj_control_curve(xmlpp::TextReader & theReader)
{
  boost::optional<CubicSplineCurve> curve;

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
								 + "> in metobj:controlCurve");
	}

  return *curve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:CubicSplineRing
 */
// ----------------------------------------------------------------------

CubicSplineRing
parse_metobj_cubic_spline_ring(xmlpp::TextReader & theReader)
{
  CubicSplineRing spline;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:vectorAtStart")
		theReader.next(); // DEPRECATED
	  else if(name == "metobj:vectorAtEnd")
		theReader.next(); // DEPRECATED
	  else if(name == "gml:posList")
		{
		  theReader.read();
		  if(theReader.get_name() != "#text")
			throw std::runtime_error("#text missing from metobj:CubicSplineRing");
		  
		  if(!theReader.has_value())
			throw std::runtime_error("Text part missing from metobj:CubicSplineRing");
		  std::stringstream s;

		  s.str(theReader.get_value());
		  while(s.good())
			{
			  double lon, lat;
			  s >> lat >> lon;
			  if(s.fail())
				throw std::runtime_error("Error parsing value '"+theReader.get_value()+"' in metobj:CubicSplineRing");
			  spline.add(Point(lon,lat));
			}

		  theReader.next();
		}
	  else if(name == "metobj:CubicSplineRing")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:CubicSplineRing");
	}

  return spline;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:exterior
 */
// ----------------------------------------------------------------------

CubicSplineRing
parse_metobj_exterior(xmlpp::TextReader & theReader)
{
  boost::optional<CubicSplineRing> spline;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:CubicSplineRing")
		spline = parse_metobj_cubic_spline_ring(theReader);
	  else if(name == "metobj:exterior")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:exterior");
	}

  return *spline;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:interior
 */
// ----------------------------------------------------------------------

CubicSplineRing
parse_metobj_interior(xmlpp::TextReader & theReader)
{
  boost::optional<CubicSplineRing> spline;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:CubicSplineRing")
		spline = parse_metobj_cubic_spline_ring(theReader);
	  else if(name == "metobj:interior")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:interior");
	}

  return *spline;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:CubicSplineSurface
 */
// ----------------------------------------------------------------------

CubicSplineSurface
parse_metobj_cubic_spline_surface(xmlpp::TextReader & theReader)
{
  CubicSplineSurface surface;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:exterior")
		surface.exterior(parse_metobj_exterior(theReader));
	  else if(name == "metobj:interior")
		surface.interior(parse_metobj_interior(theReader));
	  else if(name == "metobj:CubicSplineSurface")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:CubicSplineSurface");
	}

  return surface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:controlSurface
 */
// ----------------------------------------------------------------------

CubicSplineSurface
parse_metobj_control_surface(xmlpp::TextReader & theReader)
{
  boost::optional<CubicSplineSurface> surface;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:CubicSplineSurface")
		surface = parse_metobj_cubic_spline_surface(theReader);
	  else if(name == "metobj:controlSurface")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:controlSurface");
	}

  return *surface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:SRGBColor
 *
 * Note: scheme permits missing alpha
 */
// ----------------------------------------------------------------------

SRGBColor
parse_metobj_srgb_color(xmlpp::TextReader & theReader)
{
  boost::optional<int> r, g, b, a;

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
								 + "> in metobj:SRGBColor");
	}

  if(r && b && g && a)
	return SRGBColor(*r,*g,*b,*a);
  else if(r && b && g)
	return SRGBColor(*r,*g,*b,255);
  else
	throw std::runtime_error("Missing color components in metobj:SRGBColor");

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:color
 */
// ----------------------------------------------------------------------

SRGBColor
parse_metobj_color(xmlpp::TextReader & theReader)
{
  boost::optional<SRGBColor> color;

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
								 + "> in metobj:color");
	}
  
  return *color;

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
								 + "> in metobj:FontSymbol");
	}

  return new FontSymbol(fontname,fontsize,symbolindex,color);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:ResourceReference
 */
// ----------------------------------------------------------------------

std::string
parse_metobj_resource_reference(xmlpp::TextReader & theReader)
{
  std::string uri;
  std::string mimetype;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:mimeType")
		mimetype = read_text_value(theReader);
	  else if(name == "metobj:uri")
		uri = read_text_value(theReader);
	  else if(name == "metobj:ResourceReference")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:ResourceReference");
	}
  return uri;

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:image
 */
// ----------------------------------------------------------------------

std::string
parse_metobj_image(xmlpp::TextReader & theReader)
{
  std::string image;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:ResourceReference")
		image = parse_metobj_resource_reference(theReader);
	  else if(name == "metobj:image")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:image");
	}
  return image;

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GraphicSymbol
 */
// ----------------------------------------------------------------------

GraphicSymbol *
parse_metobj_graphic_symbol(xmlpp::TextReader & theReader)
{
  GraphicSymbol * symbol = new GraphicSymbol;

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
	  else if(name == "metobj:image")
		symbol->addURI(parse_metobj_image(theReader));
	  else if(name == "metobj:scaleFactor")
		symbol->scaleFactor(boost::lexical_cast<double>(read_text_value(theReader)));
	  else if(name == "metobj:GraphicSymbol")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:GraphicSymbol");
	}

  return symbol;
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
								 + "> in metobj:meteorologicalSymbolProperty");
	}

  return symbol;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:AbstractLine
 */
// ----------------------------------------------------------------------

template <typename T>
T *
parse_metobj_abstract_line(xmlpp::TextReader & theReader,
						   const std::string & theEndTag)
{
  T * line = new T;

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
		line->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		line->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlCurve")
		line->controlCurve(parse_metobj_control_curve(theReader));
	  else if(name == "metobj:startPointConnectsTo")
		line->connectStartPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:endPointConnectsTo")
		line->connectEndPoint(theReader.get_attribute("xlin:href"));
	  else if(name == "metobj:interpolatedCurve")
		theReader.next();
	  else if(name == theEndTag)
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in "
								 + theEndTag);
	}
  return line;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:NumericalWeatherModel
 */
// ----------------------------------------------------------------------

std::string
parse_metobj_numerical_weather_model(xmlpp::TextReader & theReader)
{
  std::string model;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:model")
		model = read_text_value(theReader);
	  else if(name == "metobj:specifier")
		theReader.next();
	  else if(name == "metobj:NumericalWeatherModel")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:NumericalWeatherModel");
	}

  return model;

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:model
 */
// ----------------------------------------------------------------------

std::string
parse_metobj_model(xmlpp::TextReader & theReader)
{
  std::string model;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:NumericalWeatherModel")
		model = parse_metobj_numerical_weather_model(theReader);
	  else if(name == "metobj:model")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:model");
	}

  return model;

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:NumericalModelRun
 */
// ----------------------------------------------------------------------

NumericalModelRun
parse_metobj_Numerical_model_run(xmlpp::TextReader & theReader)
{
  std::string model;
  boost::optional<boost::posix_time::ptime> origintime;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:model")
		model = parse_metobj_model(theReader);
	  else if(name == "metobj:originTime")
		origintime = read_text_time(theReader);
	  else if(name == "metobj:NumericalModelRun")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:NumericalModelRun");
	}
  if(!origintime)
	throw std::runtime_error("No origintime specified for NumericalModelRun");

  return NumericalModelRun(model,*origintime);

}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:numericalModelRun
 */
// ----------------------------------------------------------------------

NumericalModelRun
parse_metobj_numerical_model_run(xmlpp::TextReader & theReader)
{
  boost::optional<NumericalModelRun> model;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:NumericalModelRun")
		model = parse_metobj_Numerical_model_run(theReader);
	  else if(name == "metobj:numericalModelRun")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:numericalModelRun");
	}
  if(!model)
	throw std::runtime_error("No model specified for numericalModelRun");

  return *model;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:DataSource
 */
// ----------------------------------------------------------------------

DataSource
parse_metobj_data_source(xmlpp::TextReader & theReader)
{
  DataSource source;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:numericalModelRun")
		source.numericalModelRun(parse_metobj_numerical_model_run(theReader));
	  else if(name == "metobj:observationsCollectedUntil")
		theReader.next();
	  else if(name == "metobj:meteorologicalAnalysis")
		theReader.next();
	  else if(name == "metobj:weatherForecast")
		theReader.next();
	  else if(name == "metobj:satelliteImage")
		theReader.next();
	  else if(name == "metobj:radarImage")
		theReader.next();
	  else if(name == "metobj:DataSource")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:DataSource");
	}

  return source;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:usedReferenceData
 */
// ----------------------------------------------------------------------

DataSource parse_metobj_used_reference_data(xmlpp::TextReader & theReader)
{
  DataSource source;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:DataSource")
		source = parse_metobj_data_source(theReader);
	  else if(name == "metobj:usedReferenceData")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:usedReferenceData");
	}
  return source;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a warm front description
 */
// ----------------------------------------------------------------------

WarmFront *
parse_metobj_warm_front(xmlpp::TextReader & theReader)
{
  return parse_metobj_abstract_line<WarmFront>(theReader,"metobj:WarmFront");
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:ColdFront
 */
// ----------------------------------------------------------------------

ColdFront *
parse_metobj_cold_front(xmlpp::TextReader & theReader)
{
  return parse_metobj_abstract_line<ColdFront>(theReader,"metobj:ColdFront");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:CloudAreaBorder
 */
// ----------------------------------------------------------------------

CloudAreaBorder *
parse_metobj_cloud_area_border(xmlpp::TextReader & theReader)
{
  return parse_metobj_abstract_line<CloudAreaBorder>(theReader,"metobj:CloudAreaBorder");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:Trough
 */
// ----------------------------------------------------------------------

Trough *
parse_metobj_trough(xmlpp::TextReader & theReader)
{
  return parse_metobj_abstract_line<Trough>(theReader,"metobj:Trough");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:UpperTrough
 */
// ----------------------------------------------------------------------

UpperTrough *
parse_metobj_upper_trough(xmlpp::TextReader & theReader)
{
  return parse_metobj_abstract_line<UpperTrough>(theReader,"metobj:UpperTrough");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a occluded front description
 *
 * Note: Has extra data member "itsStationary"
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
		front->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
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
								 + "> in metobj:OccludedFront");
	}
  return front;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:innerArea
 */
// ----------------------------------------------------------------------

SurfacePrecipitationArea *
parse_metobj_surface_precipitation_area(xmlpp::TextReader & theReader);

SurfacePrecipitationArea *
parse_metobj_inner_area(xmlpp::TextReader & theReader)
{
  SurfacePrecipitationArea * area = 0;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:SurfacePrecipitationArea")
		area = parse_metobj_surface_precipitation_area(theReader);
	  else if(name == "metobj:innerArea")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:innerArea");
	}
  return area;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:SurfacePrecipitationArea
 */
// ----------------------------------------------------------------------

SurfacePrecipitationArea *
parse_metobj_surface_precipitation_area(xmlpp::TextReader & theReader)
{
  SurfacePrecipitationArea * area = new SurfacePrecipitationArea;

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
		area->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		area->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "metobj:controlSurface")
		area->controlSurface(parse_metobj_control_surface(theReader));
	  else if(name == "metobj:interpolatedSurface")
		theReader.next();
	  else if(name == "metobj:rainPhase")
		area->rainPhase(parseRainPhase(read_text_value(theReader)));
	  else if(name == "metobj:continuity")
		area->continuity(boost::lexical_cast<double>(read_text_value(theReader)));
	  else if(name == "metobj:approximateRainFall")
		area->approximateRainFall(boost::lexical_cast<double>(read_text_value(theReader)));
	  else if(name == "metobj:innerArea")
		area->innerArea(parse_metobj_inner_area(theReader));
	  else if(name == "metobj:SurfacePrecipitationArea")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:SurfacePrecipitationArea");
	}
  return area;
}



// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:Jet
 *
 * Note: Has extra data member "itsWindStrength"
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
		jet->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
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
								 + "> in metobj:Jet");
	}
  return jet;
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
		symbol->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
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
								 + "> in metobj:PointMeteorologicalSymbol");
	}
  return symbol;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GeophysicalParameter
 */
// ----------------------------------------------------------------------

GeophysicalParameter
parse_metobj_geophysical_parameter(xmlpp::TextReader & theReader)
{
  std::string param = "";
  int number = -1;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:localizedName")
		theReader.next();
	  else if(name == "metobj:abbreviation")
		theReader.next();
	  else if(name == "metobj:reference")
		{
		  std::string scheme = theReader.get_attribute("scheme");
		  std::string value = read_text_value(theReader);

		  if(scheme == "fmi")
			number = boost::lexical_cast<int>(value);
		  else if(scheme == "wmo")
			param = value;
		}
	  else if(name == "metobj:GeophysicalParameter")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:GeophysicalParameter");
	}

  return GeophysicalParameter(param,number);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:parameter
 */
// ----------------------------------------------------------------------

GeophysicalParameter
parse_metobj_parameter(xmlpp::TextReader & theReader)
{
  GeophysicalParameter param;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:GeophysicalParameter")
		param = parse_metobj_geophysical_parameter(theReader);
	  else if(name == "metobj:parameter")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:parameter");
	}
  return param;
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GeophysicalParameterValue
 */
// ----------------------------------------------------------------------

GeophysicalParameterValue
parse_metobj_geophysical_parameter_value(xmlpp::TextReader & theReader)
{
  GeophysicalParameter param;
  double value = 0.0;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  

	  else if(name == "metobj:parameter")
		param = parse_metobj_parameter(theReader);
	  else if(name == "metobj:value")
		value = boost::lexical_cast<double>(read_text_value(theReader));
	  else if(name == "metobj:elevation")
		theReader.next(); // TODO
	  else if(name == "metobj:symbol")
		theReader.next(); // TODO
	  else if(name == "metobj:GeophysicalParameterValue")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:GeophysicalParameterValue");
	}
  return GeophysicalParameterValue(param,value);
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GeophysicalParameterValueRange
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueRange
parse_metobj_geophysical_parameter_value_range(xmlpp::TextReader & theReader)
{
  GeophysicalParameter param;
  double lowerlimit = 0;
  double upperlimit = 0;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:parameter")
		param = parse_metobj_parameter(theReader);
	  else if(name == "metobj:lowerLimit")
		lowerlimit = boost::lexical_cast<double>(read_text_value(theReader));
	  else if(name == "metobj:upperLimit")
		upperlimit = boost::lexical_cast<double>(read_text_value(theReader));
	  else if(name == "metobj:elevation")
		theReader.next(); // TODO
	  else if(name == "metobj:symbol")
		theReader.next(); // TODO
	  else if(name == "metobj:GeophysicalParameterValueRange")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:GeophysicalParameterValueRange");
	}
  return GeophysicalParameterValueRange(param,lowerlimit,upperlimit);
}


// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:singleValue
 */
// ----------------------------------------------------------------------

GeophysicalParameterValue
parse_metobj_single_value(xmlpp::TextReader & theReader)
{
  boost::optional<GeophysicalParameterValue> value;
  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:GeophysicalParameterValue")
		value.reset(parse_metobj_geophysical_parameter_value(theReader));
	  else if(name == "metobj:singleValue")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:singleValue");
	}
  return *value;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:valueRange
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueRange
parse_metobj_value_range(xmlpp::TextReader & theReader)
{
  boost::optional<GeophysicalParameterValueRange> value;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:GeophysicalParameterValueRange")
		value.reset(parse_metobj_geophysical_parameter_value_range(theReader));
	  else if(name == "metobj:valueRange")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:valueRange");
	}
  return *value;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GeophysicalParameterValueSet
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet *
parse_metobj_geophysical_parameter_value_set(xmlpp::TextReader & theReader)
{
  GeophysicalParameterValueSet * values = new GeophysicalParameterValueSet;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:singleValue")
		values->add(parse_metobj_single_value(theReader));
	  else if(name == "metobj:valueRange")
		values->add(parse_metobj_value_range(theReader));
	  else if(name == "metobj:elevation")
		theReader.next(); // TODO
	  else if(name == "metobj:GeophysicalParameterValueSet")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:GeophysicalParameterValueSet");
	}
  return values;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:GeophysicalParameterValueSet
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet *
parse_metobj_parameter_value_set(xmlpp::TextReader & theReader)
{
  GeophysicalParameterValueSet * values = 0;

  while(theReader.read())
	{
	  std::string name = theReader.get_name();

	  if(name == "#text")
		require_whitespace(theReader);
	  else if(name == "#comment")
		theReader.next();
	  else if(name == "metobj:GeophysicalParameterValueSet")
		values = parse_metobj_geophysical_parameter_value_set(theReader);
	  else if(name == "metobj:parameterValueSet")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:parameterValueSet");
	}
  return values;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:PointGeophysicalParameterValueSet
 */
// ----------------------------------------------------------------------

PointGeophysicalParameterValueSet *
parse_metobj_point_geophysical_parameter_value_set(xmlpp::TextReader & theReader)
{
  PointGeophysicalParameterValueSet * param = new PointGeophysicalParameterValueSet;

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
		param->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		param->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "gml:pointProperty")
		param->point(parse_gml_point_property(theReader));
	  else if(name == "metobj:parameterValueSet")
		param->param(parse_metobj_parameter_value_set(theReader));
	  else if(name == "metobj:priority")
		param->priority(boost::lexical_cast<int>(read_text_value(theReader)));
	  else if(name == "metobj:PointGeophysicalParameterValueSet")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:PointGeophysicalParameterValueSet");
	}
  return param;
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse metobj:PointNote
 */
// ----------------------------------------------------------------------

PointNote *
parse_metobj_point_note(xmlpp::TextReader & theReader)
{
  PointNote * note = new PointNote;

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
		note->envelope(parse_gml_bounded_by(theReader));
	  else if(name == "gml:validTime")
		note->validTime(parse_gml_valid_time_instant(theReader));
	  else if(name == "metobj:creationTime")
		read_text_time(theReader);
	  else if(name == "metobj:latestModificationTime")
		read_text_time(theReader);
	  else if(name == "metobj:shortInfo")
		parse_metobj_short_info(theReader);
	  else if(name == "metobj:longInfo")
		parse_metobj_long_info(theReader);
	  else if(name == "gml:pointProperty")
		note->point(parse_gml_point_property(theReader));
	  else if(name == "metobj:priority")
		note->priority(boost::lexical_cast<int>(read_text_value(theReader)));
	  else if(name == "metobj:noteText")
		note->noteText(theReader.get_attribute("lang"),
					   read_text_value(theReader));
	  else if(name == "metobj:GraphicSymbol")
		theReader.next(); // IGNORED UNTIL EXAMPLE EXISTS
	  else if(name == "metobj:PointNote")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:PointNote");
	}
  return note;
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
	  else if(name == "metobj:PointGeophysicalParameterValueSet")
		theWeatherObject.addFeature(parse_metobj_point_geophysical_parameter_value_set(theReader));
	  else if(name == "metobj:SurfacePrecipitationArea")
		theWeatherObject.addFeature(parse_metobj_surface_precipitation_area(theReader));
	  else if(name == "metobj:PointNote")
		theWeatherObject.addFeature(parse_metobj_point_note(theReader));
	  else if(name == "gml:featureMember")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in gml:featureMember");
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
		p = read_text_point(theReader);
	  else if(name == "metobj:ConnectionPoint")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:ConnectionPoint");
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
								 + "> in metobj:sharedConnectionPoints");
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
		analysis->creationTime(read_text_time(theReader));
	  else if(name == "metobj:analysisTime")
		analysis->analysisTime(read_text_time(theReader));
	  else if(name == "metobj:latestModificationTime")
		analysis->latestModificationTime(read_text_time(theReader));
	  else if(name == "metobj:sharedConnectionPoints")
		analysis->addConnectionPoints(parse_metobj_shared_connection_points(theReader));
	  else if(name == "metobj:shortInfo")
		theReader.next();
	  else if(name == "metobj:longInfo")
		theReader.next();
	  else if(name == "metobj:targetRegion")
		theReader.next();
	  else if(name == "metobj:usedReferenceData")
		analysis->dataSource(parse_metobj_used_reference_data(theReader));
	  else if(name == "metobj:MeteorologicalAnalysis")
		break;
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> in metobj:MeteorologicalAnalysis");
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
		forecast->creationTime(read_text_time(theReader));
	  else if(name == "metobj:analysisTime")
		forecast->analysisTime(read_text_time(theReader));
	  else if(name == "metobj:forecastTime")
		forecast->forecastTime(read_text_time(theReader));
	  else if(name == "metobj:latestModificationTime")
		forecast->latestModificationTime(read_text_time(theReader));
	  else if(name == "metobj:sharedConnectionPoints")
		forecast->addConnectionPoints(parse_metobj_shared_connection_points(theReader));
	  else if(name == "metobj:usedReferenceData")
		forecast->dataSource(parse_metobj_used_reference_data(theReader));
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
								 + "> in metobj:WeatherForecast");
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
  if(!boost::filesystem::exists(thePath))
	throw std::runtime_error("The file '"+thePath.string()+"' does not exist");

  xmlpp::TextReader reader(thePath.string());

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
			throw std::runtime_error("Multiple meteorological objects in " + thePath.string());
		  weather.forecast(parse_metobj_weather_forecast(reader));
		}
	  else if(name == "metobj:MeteorologicalAnalysis")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.string());
		  weather.analysis(parse_metobj_meteorological_analysis(reader));
		}
	  else if(name == "#text")
		require_whitespace(reader);
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + "> at top level of "
								 + thePath.string());

	}

  return weather;
}



} // namespace woml
