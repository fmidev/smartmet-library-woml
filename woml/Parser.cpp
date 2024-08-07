/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "AbstractLineObject.h"
#include "CloudArea.h"
#include "DataSource.h"
#include "GeophysicalParameterValueSet.h"
#include "JetStream.h"
#include "MeteorologicalAnalysis.h"
#include "NumericalModelRun.h"
#include "OccludedFront.h"
#include "ParameterTimeSeriesPoint.h"
#include "ParameterValueSetArea.h"
#include "ParameterValueSetPoint.h"
#include "PointMeteorologicalSymbol.h"
#include "PressureCenterType.h"
#include "StormType.h"
#include "SurfacePrecipitationArea.h"
#include "TimeSeriesSlot.h"
#include "Weather.h"
#include "WeatherForecast.h"

#include <smartmet/macgyver/TimeParser.h>

#include <boost/algorithm/string.hpp>
#include <macgyver/DateTime.h>
#include <macgyver/StringConversion.h>
#include <filesystem>
#include <boost/lexical_cast.hpp>
#include <optional>
#include <memory>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xqilla/xqilla-dom3.hpp>

XERCES_CPP_NAMESPACE_USE;

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Namespace resolver
 */
// ----------------------------------------------------------------------

class nsResolver
{
 public:
  static DOMXPathNSResolver *set(DOMDocument *doc, DOMXPathNSResolver *nsR)
  {
    _doc = doc;
    _nsR = nsR;

    for (const char **ns = _namespaces, **url = _namespaces + 1; *ns && *url; ns++, url++)
      _nsR->addNamespaceBinding(X(*ns), X(*url));

    return nsR;
  }
  static DOMXPathExpression *createExpression(std::string expr)
  {
    return _doc->createExpression(X(expr.c_str()), _nsR);
  }

 private:
  static DOMDocument *_doc;
  static DOMXPathNSResolver *_nsR;
  static const char *_namespaces[];
};

DOMDocument *nsResolver::_doc = nullptr;
DOMXPathNSResolver *nsResolver::_nsR = nullptr;

const char *nsResolver::_namespaces[] = {"gml",
                                         "http://www.opengis.net/gml/3.2",
                                         "womlcore",
                                         "http://xml.fmi.fi/namespace/woml/core/2011/11/15",
                                         "womlqty",
                                         "http://xml.fmi.fi/namespace/woml/quantity/2011/11/15",
                                         "womlswo",
                                         "http://xml.fmi.fi/namespace/woml/swo/2011/11/15",
                                         "dc",
                                         "http://purl.org/dc/elements/1.1/",
                                         nullptr,
                                         nullptr};

#define EXPR(expr) (nsResolver::createExpression(expr))
#define ATTR(elem, attr) \
  (elem->hasAttribute(X(attr)) ? XMLChptr2str(elem->getAttribute(X(attr))) : "")

#define XQEXC(msg) \
  throw std::runtime_error(std::string(EXCFUNC) + ": XQillaException: " + std::string(msg))
#define DXPEXC(code)                              \
  throw std::runtime_error(std::string(EXCFUNC) + \
                           ": DOMXPathException: " + Fmi::to_string(code))
#define DEXC(code)                                \
  throw std::runtime_error(std::string(EXCFUNC) + \
                           ": DOMException: " + Fmi::to_string(code))
#define REXC(msg) throw std::runtime_error(std::string(msg) + "\nat " + std::string(EXCFUNC))
#define UEXC REXC("unknown exception")
#define TRY()                                 \
  std::string __EXCFUNC(__PRETTY_FUNCTION__); \
  std::string _EXCFUNC;                       \
  (void)_EXCFUNC;                             \
  const char *EXCFUNC = __EXCFUNC.c_str();    \
  try
#define TRYA(arg)                                        \
  _EXCFUNC = (__EXCFUNC + std::string("(") + arg + ")"); \
  EXCFUNC = _EXCFUNC.c_str();
#define TRYFA(arg)                                   \
  std::string __EXCFUNC(__PRETTY_FUNCTION__);        \
  std::string _EXCFUNC(__EXCFUNC + "(" + arg + ")"); \
  const char *EXCFUNC = _EXCFUNC.c_str();            \
  try
#define CATCH                                                                     \
  catch (DOMXPathException & exc) { DXPEXC(exc.code); }                           \
  catch (DOMException & exc) { DEXC(exc.code); }                                  \
  catch (std::runtime_error & exc) { REXC(std::string(exc.what())); }             \
  catch (std::exception & exc) { REXC(std::string("exception: ") + exc.what()); } \
  catch (...) { UEXC; }
// ----------------------------------------------------------------------
/*!
 * \brief Convert XMLCh* to a string
 */
// ----------------------------------------------------------------------

std::string XMLChptr2str(const XMLCh *xp)
{
  char *p = XMLString::transcode(xp);
  std::string s(p);
  XMLString::release(&p);

  return s;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return next DOMXPathResult node
 */
// ----------------------------------------------------------------------

DOMNode *searchNode(DOMNode *node, const char *pathExpr);

DOMNode *getResultNode(DOMXPathResult *result, DOMText **text = nullptr, bool textRequired = true){
    TRY(){DOMNode *node = (result->iterateNext() ? result->getNodeValue() : nullptr);

if (node && text)
{
  TRYA(XMLChptr2str(node->getNodeName()))
  {
    if ((!(*text = ((DOMText *)searchNode(node, "text()[1]")))) && textRequired)
      throw std::runtime_error("Text element missing");
  }
}

return node;
}  // namespace woml
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Search the tree for a node.
 */
// ----------------------------------------------------------------------

DOMNode *searchNode(DOMNode *node, const char *pathExpr){
    TRYFA(pathExpr){AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

return getResultNode(result);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse line object orientation
 */
// ----------------------------------------------------------------------

std::optional<std::string> parse_woml_orientation(DOMNode *node){
    TRY(){std::optional<std::string> orientation;

DOMElement *elem = (DOMElement *)node;
std::string o = ATTR(elem, "orientation");

if (o.length() > 0) orientation = o;

return orientation;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:Point
 */
// ----------------------------------------------------------------------

std::optional<Point> parse_gml_point(DOMNode *node, const char *pathExpr){
    TRYFA(pathExpr){std::optional<Point> p;

AutoRelease<DOMXPathExpression> expression(EXPR(std::string(pathExpr) + "/text()[1]"));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

if ((node = getResultNode(result)))
{
  std::stringstream s(XMLChptr2str(((DOMText *)node)->getNodeValue()));
  double lat, lon;
  s >> lat >> lon;
  if (s.fail()) throw std::runtime_error("Invalid coordinate: " + s.str());

  p = Point(lon, lat);
}

return p;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse rectangle corners
 */
// ----------------------------------------------------------------------

std::optional<Rect> parse_rect_corners(DOMNode *node,
                                         const char *lowerCornerPathExpr,
                                         const char *upperCornerPathExpr){
    TRY(){std::optional<Rect> rect;
std::optional<Point> lowerCorner = parse_gml_point(node, lowerCornerPathExpr);
std::optional<Point> upperCorner = parse_gml_point(node, upperCornerPathExpr);

if (lowerCorner && upperCorner) rect = Rect(lowerCorner, upperCorner);

return rect;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse Envelope
 */
// ----------------------------------------------------------------------

std::optional<Envelope> parse_gml_envelope(DOMNode *node){
    TRY(){std::optional<Envelope> envelope;

DOMElement *elem = (DOMElement *)node;
std::string srsName = ATTR(elem, "srsName");
std::string srsDimension = ATTR(elem, "srsDimension");

std::optional<Rect> rect = parse_rect_corners(node, "gml:lowerCorner", "gml:upperCorner");

if (rect)
  envelope = Envelope(rect, srsName, srsDimension);
else
{
  std::optional<Point> point = parse_gml_point(node, "gml:coordinates");

  if (point) envelope = Envelope(point, srsName, srsDimension);
}

return envelope;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a boundedBy object
 */
// ----------------------------------------------------------------------

std::optional<Envelope> parse_gml_bounded_by(DOMNode *node,
                                               const char *pathExpr = "gml:boundedBy/gml:Envelope")
{
  std::optional<Envelope> envelope;

  TRYFA(pathExpr)
  {
    AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    if ((node = getResultNode(result))) envelope = parse_gml_envelope(node);

    return envelope;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:NumericalSingleValueMeasure
 */
// ----------------------------------------------------------------------

std::optional<NumericalSingleValueMeasure> parse_woml_numerical_single_value_measure(
    DOMNode *node,
    const char *pathExpr){TRYFA(pathExpr){std::optional<NumericalSingleValueMeasure> meas;

AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

DOMText *text;
if ((node = getResultNode(result, &text)))
{
  DOMElement *elem = (DOMElement *)node;

  std::string valstr(XMLChptr2str(text->getNodeValue()));
  std::string unit(ATTR(elem, "uom"));

  if (valstr != "")
  {
    double value = boost::lexical_cast<double>(valstr);
    meas = NumericalSingleValueMeasure(value, valstr, unit);
  }
}

return meas;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:NumericalValueRangeMeasure
 */
// ----------------------------------------------------------------------

std::optional<NumericalValueRangeMeasure> parse_woml_numerical_value_range_measure(
    DOMNode *node, const char *lowerLimitPathExpr, const char *upperLimitPathExpr){
    TRY(){std::optional<NumericalValueRangeMeasure> meas;
std::optional<NumericalSingleValueMeasure> lowerLimit =
    parse_woml_numerical_single_value_measure(node, lowerLimitPathExpr);
std::optional<NumericalSingleValueMeasure> upperLimit =
    parse_woml_numerical_single_value_measure(node, upperLimitPathExpr);

if (lowerLimit && upperLimit) meas = NumericalValueRangeMeasure(*lowerLimit, *upperLimit);

return meas;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:Elevation
 */
// ----------------------------------------------------------------------

Elevation parse_woml_elevation(DOMNode *node){TRY(){
    std::optional<NumericalValueRangeMeasure> range = parse_woml_numerical_value_range_measure(
        node,
        "womlqty:elevation/womlcore:Elevation/womlcore:valueLowerLimit",
        "womlqty:elevation/womlcore:Elevation/womlcore:valueUpperLimit");
if (range) return Elevation(range);

return Elevation(parse_woml_numerical_single_value_measure(
    node, "womlqty:elevation/womlcore:Elevation/womlcore:value"));
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse target region
 *
 * Note: only 'ICAO' or 'fmi' scheme region id parsed
 */
// ----------------------------------------------------------------------

TargetRegion parse_woml_target_region(DOMNode *theNode,
                                      const char *regionIdPathExpr =
                                          "womlcore:regionId[@scheme=\"urn:x-finnish-meterological-"
                                          "institute:icao:code\" or @scheme=\"fmi\"][1]",
                                      const char *localizedNamePathExpr = "womlcore:localizedName")
{
  TRY()
  {
    TargetRegion tr;
    tr.envelope(parse_gml_bounded_by(theNode));

    TRYA(regionIdPathExpr)
    {
      AutoRelease<DOMXPathExpression> expression(EXPR(regionIdPathExpr));
      AutoRelease<DOMXPathResult> result(
          expression->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

      DOMNode *node;
      DOMText *text;
      while ((node = getResultNode(result, &text)))
      {
        DOMElement *elem = (DOMElement *)node;
        std::string scheme = ATTR(elem, "scheme");

        tr.addRegionId(scheme, XMLChptr2str(text->getNodeValue()));
      }

      TRYA(localizedNamePathExpr)
      {
        AutoRelease<DOMXPathExpression> expression2(EXPR(localizedNamePathExpr));
        AutoRelease<DOMXPathResult> result2(
            expression2->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

        while ((node = getResultNode(result2, &text)))
        {
          DOMElement *elem = (DOMElement *)node;
          std::string lang = ATTR(elem, "xml:lang");

          tr.addLocalizedName(lang, XMLChptr2str(text->getNodeValue()));
        }

        return tr;
      }
    }
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse target regions
 *
 * Note: only 1 region (containing "ICAO" or "fmi" scheme region id) parsed
 */
// ----------------------------------------------------------------------

template <typename T>
void parse_woml_target_regions(T &theWeatherObject,
                               DOMNode *node,
                               const char *pathExpr =
                                   "womlcore:targetRegion/"
                                   "womlcore:GeographicRegion[womlcore:regionId/"
                                   "@scheme=\"urn:x-finnish-meterological-institute:icao:code\" or "
                                   "womlcore:regionId/@scheme=\"fmi\"][1]"){
    TRYFA(pathExpr){AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

while ((node = getResultNode(result)))
{
  theWeatherObject.addTargetRegion(parse_woml_target_region(node));
}

WeatherForecast::TargetRegions_const_iterator it = theWeatherObject.TargetRegions_begin();

if (it != theWeatherObject.TargetRegions_end())
  theWeatherObject.envelope(it->envelope());
else
  throw std::runtime_error(
      "Required target region (having regionId with "
      "@scheme=\"urn:x-finnish-meterological-institute:icao:code\" or @scheme=\"fmi\") element "
      "missing");
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse info texts
 */
// ----------------------------------------------------------------------

std::multimap<std::string, std::string> &parse_woml_info_texts(
    DOMNode *node, std::multimap<std::string, std::string> &infos, const char *pathExpr){
    TRYFA(pathExpr){AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

DOMText *text;
while ((node = getResultNode(result, &text, false)))
  if (text)
  {
    DOMElement *elem = (DOMElement *)node;
    std::string lang = ATTR(elem, "xml:lang");

    if (lang.length() > 0) infos.insert(std::make_pair(lang, XMLChptr2str(text->getNodeValue())));
  }

return infos;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:shortInfo
 */
// ----------------------------------------------------------------------

std::multimap<std::string, std::string> &parse_woml_shortinfo(
    DOMNode *node, std::multimap<std::string, std::string> &infos)
{
  return parse_woml_info_texts(node, infos, "womlcore:shortInfo");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:longInfo
 */
// ----------------------------------------------------------------------

std::multimap<std::string, std::string> &parse_woml_longinfo(
    DOMNode *node, std::multimap<std::string, std::string> &infos)
{
  return parse_woml_info_texts(node, infos, "womlcore:longInfo");
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse creator
 */
// ----------------------------------------------------------------------

std::string parse_woml_creator(
    DOMNode *node,
    const char *pathExpr =
        "womlcore:metaData/womlcore:MeteorologicalObjectMetaData/dc:creator/text()[1]"){
    TRYFA(pathExpr){std::string creator;

AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

if ((node = getResultNode(result))) creator = XMLChptr2str(((DOMText *)node)->getNodeValue());

return creator;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse #text XML time
 */
// ----------------------------------------------------------------------

std::optional<Fmi::DateTime> read_text_time(DOMNode *node, const char *pathExpr){
    TRYFA(pathExpr){std::optional<Fmi::DateTime> t;

AutoRelease<DOMXPathExpression> expression(EXPR(std::string(pathExpr) + "/text()[1]"));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

if ((node = getResultNode(result)))
{
  std::string ts(XMLChptr2str(((DOMText *)node)->getNodeValue()));

  // 03-Dec-2012: Get rid of possible millisecond part (all subsequent digits after period); not
  // supported by TimeParser

  std::string tail;
  size_t pos = ts.find('.');

  if ((pos > 0) && (pos != std::string::npos))
  {
    size_t tpos = pos + 1;
    const char *p = (ts.c_str() + tpos);

    for (; ((*p >= '0') && (*p <= '9')); p++)
      tpos++;

    // Keep whatever follows the millisecond part (e.g. YYYY-MM-DDTHH:MM:SS[.mmm]Z)
    //
    if (*p) tail = ts.substr(tpos);
  }
  else
    pos = std::string::npos;

  t = Fmi::TimeParser::parse((pos == std::string::npos) ? ts : ts.substr(0, pos) + tail);

  if (t->is_not_a_date_time()) throw std::runtime_error("Invalid datetime: " + ts);
}

return t;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a point
 */
// ----------------------------------------------------------------------

Point read_text_point(DOMNode *node){TRY(){
    if (!(node = searchNode(node, "/text()[1]"))) throw std::runtime_error("Text element missing");

std::stringstream s(XMLChptr2str(((DOMText *)node)->getNodeValue()));
double lat, lon;
s >> lat >> lon;
if (s.fail()) throw std::runtime_error("Invalid coordinate: " + s.str());

return Point(lon, lat);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimePositionUnion
 */
// ----------------------------------------------------------------------

std::optional<Fmi::DateTime> parse_gml_time_position_union(DOMNode *node,
                                                                        const char *pathExpr){TRY(){
    // TODO: parse_gml_time_position_union: only read_text_time/Fmi::TimeParser::parse_xml used
    return read_text_time(node, pathExpr);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimeInstant
 */
// ----------------------------------------------------------------------

std::optional<Fmi::DateTime> parse_gml_time_instant(DOMNode *node,
                                                                 const char *pathExpr){
    TRY(){return parse_gml_time_position_union(node, pathExpr);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:TimePeriod
 */
// ----------------------------------------------------------------------

std::optional<Fmi::TimePeriod> parse_gml_time_period(
    DOMNode *node, const char *beginPositionPathExpr, const char *endPositionPathExpr){
    TRY(){std::optional<Fmi::TimePeriod> period;
std::optional<Fmi::DateTime> starttime =
    parse_gml_time_position_union(node, beginPositionPathExpr);
std::optional<Fmi::DateTime> endtime =
    parse_gml_time_position_union(node, endPositionPathExpr);

if (starttime && endtime) period = Fmi::TimePeriod(*starttime, *endtime);

return period;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse required time element
 */
// ----------------------------------------------------------------------

Fmi::DateTime parse_woml_required_time(DOMNode *node, const char *pathExpr){
    TRYFA(pathExpr){std::optional<Fmi::DateTime> t = read_text_time(node, pathExpr);

if (!t) throw std::runtime_error("Required datetime element missing");

return *t;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:creationTime
 */
// ----------------------------------------------------------------------

Fmi::DateTime parse_woml_creation_time(DOMNode *node){
    TRY(){return parse_woml_required_time(node, "womlcore:creationTime");
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:latestModificationTime
 */
// ----------------------------------------------------------------------

std::optional<Fmi::DateTime> parse_woml_latest_modification_time(DOMNode *node){
    TRY(){return read_text_time(node, "womlcore:latestModificationTime");
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:validTime as time period or time instant
 */
// ----------------------------------------------------------------------

std::optional<Fmi::TimePeriod> parse_gml_valid_time(DOMNode *node){
    TRY(){std::optional<Fmi::TimePeriod> period;
std::optional<Fmi::DateTime> t =
    parse_gml_time_instant(node, "gml:validTime/gml:TimeInstant/gml:timePosition");

if (t)
  period = Fmi::TimePeriod(*t, *t);
else
  period = parse_gml_time_period(node,
                                 "gml:validTime/gml:TimePeriod/gml:beginPosition",
                                 "gml:validTime/gml:TimePeriod/gml:endPosition");

return period;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse gml:validTime expecting time instant only!
 */
// ----------------------------------------------------------------------

std::optional<Fmi::DateTime> parse_gml_valid_time_instant(DOMNode *node){
    TRYFA(XMLChptr2str(node->getNodeName())){
        std::optional<Fmi::TimePeriod> p = parse_gml_valid_time(node);

if (p)
{
  if (!(p->is_null()))
    throw std::runtime_error("Time instant element expected instead of time period");
}
else
  throw std::runtime_error("Required time instant element missing");

return p->begin();
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse required gml:validTime as time period or time instant
 */
// ----------------------------------------------------------------------

Fmi::TimePeriod parse_gml_required_valid_time(DOMNode *node)
{
  TRYFA(XMLChptr2str(node->getNodeName()))
  {
    std::optional<Fmi::TimePeriod> period = parse_gml_valid_time(node);

    if (!period) throw std::runtime_error("Required validtime element missing");

    return *period;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:BSpline, woml:CSpline
 */
// ----------------------------------------------------------------------

template <typename T>
T parse_woml_spline(DOMNode *node){TRY(){T spline;

std::string latlons(XMLChptr2str(((DOMText *)node)->getNodeValue()));
boost::trim(latlons);
std::stringstream s(latlons);

while (s.good())
{
  double lon, lat;
  s >> lat >> lon;
  if (s.fail()) throw std::runtime_error("Invalid coordinate: " + s.str());

  spline.add(Point(lon, lat));
}

return spline;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse line segments
 */
// ----------------------------------------------------------------------

CubicSplineCurve parse_woml_spline_segments(DOMNode *node,
                                            const char *pathExpr =
                                                "womlcore:controlCurve/gml:CompositeCurve/"
                                                "gml:curveMember/gml:Curve/gml:segments/gml:Bezier/"
                                                "gml:posList/text()[1]")
{
  TRYFA(pathExpr)
  {
    CubicSplineCurve curve;

    AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    while ((node = getResultNode(result)))
      curve.add(parse_woml_spline<SimpleCubicSpline>(node));

    return curve;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse line string
 */
// ----------------------------------------------------------------------

void parse_woml_spline_string(DOMNode *node,
                              CubicSplineCurve &curve,
                              const char *pathExpr =
                                  "womlcore:controlCurve/gml:CompositeCurve/gml:curveMember/"
                                  "gml:LineString[1]/gml:posList/text()[1]"){
    TRYFA(pathExpr){AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

if ((node = getResultNode(result)))
  curve.lineString(parse_woml_spline<SimpleCubicSpline>(node));
else
  throw std::runtime_error("Required linestring element missing");
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:ControlCurve
 */
// ----------------------------------------------------------------------

CubicSplineCurve parse_woml_control_curve(DOMNode *node){TRY(){
    // Note: temporarily storing linestring as a bezier segment.
    // To be uncommented later when frontier uses the bezier elements to construct bezier curves.
    //
    CubicSplineCurve curve;
//		CubicSplineCurve curve = parse_woml_spline_segments(node);
parse_woml_spline_string(node, curve);

// Note: temporary
//
curve.add(curve.lineString());

return curve;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:CubicSplineSurface
 */
// ----------------------------------------------------------------------

CubicSplineSurface parse_woml_cubic_spline_surface(DOMNode *theNode, const char *pathExpr)
{
  std::string exteriorPathExpr =
      std::string(pathExpr) + "/gml:exterior/gml:LinearRing/gml:posList/text()[1]";
  std::string interiorPathExpr =
      std::string(pathExpr) + "/gml:interior/gml:LinearRing/gml:posList/text()[1]";

  TRYFA(exteriorPathExpr.c_str())
  {
    CubicSplineSurface surface;

    AutoRelease<DOMXPathExpression> expression(EXPR(exteriorPathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    DOMNode *node;
    if ((node = getResultNode(result)))
    {
      std::string latlons(XMLChptr2str(((DOMText *)node)->getNodeValue()));
      boost::trim(latlons);

      if (!latlons.empty())
        surface.exterior(parse_woml_spline<CubicSplineRing>(node));
      else
        return surface;
    }
    //  16.8.16 Always skip/ignore empty posList
    //
    //  else if (Weather::strictMode())
    //    throw std::runtime_error("Required exterior element missing");
    else
      return surface;

    TRYA(interiorPathExpr.c_str())
    {
      AutoRelease<DOMXPathExpression> expression2(EXPR(interiorPathExpr));
      AutoRelease<DOMXPathResult> result2(
          expression2->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

      while ((node = getResultNode(result2)))
        surface.interior(parse_woml_spline<CubicSplineRing>(node));

      return surface;
    }
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:MeteorologicalSymbol
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol parse_woml_meteorological_symbol(
    DOMNode *theNode,
    const char *definitionReferencePathExpr =
        "womlswo:meteorologicalSymbolProperty/womlswo:MeteorologicalSymbol/"
        "womlswo:definitionReference[@scheme=\"fmi\"]",
    const char *localizedSymbolNamePathExpr =
        "womlswo:meteorologicalSymbolProperty/womlswo:MeteorologicalSymbol/"
        "womlswo:localizedSymbolName")
{
  TRYFA(definitionReferencePathExpr)
  {
    MeteorologicalSymbol symbol;

    AutoRelease<DOMXPathExpression> expression(EXPR(definitionReferencePathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    DOMNode *node;
    DOMText *text;
    while ((node = getResultNode(result, &text)))
    {
      DOMElement *elem = (DOMElement *)node;
      std::string scheme = ATTR(elem, "scheme");

      symbol.addDefinitionReference(scheme, XMLChptr2str(text->getNodeValue()));
    }

    TRYA(localizedSymbolNamePathExpr)
    {
      AutoRelease<DOMXPathExpression> expression2(EXPR(localizedSymbolNamePathExpr));
      AutoRelease<DOMXPathResult> result2(
          expression2->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

      while ((node = getResultNode(result2, &text)))
      {
        DOMElement *elem = (DOMElement *)node;
        std::string lang = ATTR(elem, "xml:lang");

        symbol.addLocalizedSymbolName(lang, XMLChptr2str(text->getNodeValue()));
      }

      return symbol;
    }
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:AbstractPoint
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_abstract_point(DOMNode *node)
{
  TRY()
  {
    T *point = new T;

    point->envelope(parse_gml_bounded_by(node));
    point->validTime(parse_gml_valid_time_instant(node));

    std::optional<Point> p = parse_gml_point(node, "womlcore:controlPoint/gml:Point/gml:pos");
    if (!p) throw std::runtime_error("Required point element missing");

    point->point(p);

    return point;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:PressureCenterType
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_pressure_center_type(DOMNode *theNode)
{
  TRY()
  {
    T *pct = parse_woml_abstract_point<T>(theNode);

    DOMNode *node;
    if (!(node = searchNode(theNode, "womlswo:tendency/text()[1]")))
      throw std::runtime_error("Required tendency element missing");

    pct->tendency(XMLChptr2str(((DOMText *)node)->getNodeValue()));
    pct->maxwindspeed(
        parse_woml_numerical_single_value_measure(theNode, "womlswo:maximumWindSpeed"));

    // Using 'shortInfos' member to store component info text

    MeteorologicalAnalysisInfo longInfos;
    pct->addShortInfos(parse_woml_longinfo(theNode, longInfos));

    return pct;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:StormType
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_storm_type(DOMNode *theNode)
{
  TRY()
  {
    T *st = parse_woml_abstract_point<T>(theNode);
    RainPhase rainPhase = unknown;
    std::optional<bool> isThunderStorm;

    DOMNode *node;

    if ((node = searchNode(theNode, "womlswo:rainPhase/text()[1]")))
      rainPhase = parseRainPhase(XMLChptr2str(((DOMText *)node)->getNodeValue()));

    if ((node = searchNode(theNode, "womlswo:isThunderStorm/text()[1]")))
      isThunderStorm = (XMLChptr2str(((DOMText *)node)->getNodeValue()) == "true");

    st->rainPhase(rainPhase);
    st->approximateRainFall(
        parse_woml_numerical_single_value_measure(theNode, "womlswo:approximateRainFall"));
    st->isThunderStorm(isThunderStorm);

    return st;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:AbstractLine
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_abstract_line(DOMNode *node)
{
  TRY()
  {
    T *line = new T;

    line->orientation(parse_woml_orientation(node));
    line->envelope(parse_gml_bounded_by(node));
    line->validTime(parse_gml_valid_time_instant(node));
    line->creationTime(parse_woml_creation_time(node));
    line->latestModificationTime(parse_woml_latest_modification_time(node));

    WeatherForecastInfo shortInfos;
    line->addShortInfos(parse_woml_shortinfo(node, shortInfos));

    // MIRWA-1141; gml:LineString/gml:posList might be an empty node (no text element), and parsing
    // throws runtime_error

    try
    {
      line->controlCurve(parse_woml_control_curve(node));
    }
    catch (std::runtime_error &exc)
    {
      if (Weather::strictMode()) throw;

      delete line;

      return nullptr;
    }

    return line;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:AbstractSurface
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_abstract_surface(DOMNode *node){TRY(){T * surface = new T;

surface->envelope(parse_gml_bounded_by(node));
surface->validTime(parse_gml_valid_time_instant(node));
surface->creationTime(parse_woml_creation_time(node));
surface->latestModificationTime(parse_woml_latest_modification_time(node));
surface->elevation(parse_woml_elevation(node));

MeteorologicalObjectInfo longInfos;
surface->addShortInfos(parse_woml_longinfo(node, longInfos));

surface->controlSurface(parse_woml_cubic_spline_surface(
    node, "womlcore:controlSurface/gml:CompositeSurface/gml:surfaceMember/gml:Polygon"));

return surface;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:NumericalModelRunForecastReference
 */
// ----------------------------------------------------------------------

std::optional<NumericalModelRun> parse_woml_numerical_model_run(DOMNode *theNode){
    TRYFA(XMLChptr2str(theNode->getNodeName())){DOMNode * node;
Fmi::DateTime analysisTime = parse_woml_required_time(theNode, "womlcore:analysisTime");

if (!(node = searchNode(
          theNode,
          "womlcore:model/womlcore:NumericalWeatherModel/womlcore:modelIdentifier/text()[1]")))
  throw std::runtime_error("Required modelidentifier element missing");

std::string model = XMLChptr2str(((DOMText *)node)->getNodeValue());

if (!(node = searchNode(
          theNode, "womlcore:model/womlcore:NumericalWeatherModel/womlcore:specifier/text()[1]")))
  throw std::runtime_error("Required specifier element missing");

std::string specifier = XMLChptr2str(((DOMText *)node)->getNodeValue());

return NumericalModelRun(model, specifier, analysisTime);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:usedReferenceData
 */
// ----------------------------------------------------------------------

DataSource parse_woml_used_reference_data(DOMNode *node)
{
  TRYFA(XMLChptr2str(node->getNodeName()))
  {
    DataSource source;
    std::optional<NumericalModelRun> model;

    AutoRelease<DOMXPathExpression> expression(
        EXPR("womlcore:usedReferenceData/womlcore:NumericalModelRunForecastReference"));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    if ((node = getResultNode(result))) model = parse_woml_numerical_model_run(node);

    if (!model)
      throw std::runtime_error("Required NumericalModelRunForecastReference element expected");

    source.numericalModelRun(model);

    return source;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:SegmentMaximumWind
 */
// ----------------------------------------------------------------------

void parse_woml_jet_stream_maximum_wind_speed(DOMNode *theNode, JetStream *stream){
    TRY(){const char *segmentIndexPathExpr = "womlswo:segmentIndex/text()[1]";

TRYA(segmentIndexPathExpr)
{
  AutoRelease<DOMXPathExpression> expression(EXPR(segmentIndexPathExpr));
  AutoRelease<DOMXPathResult> result(
      expression->evaluate(theNode, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

  DOMNode *node;
  if ((node = getResultNode(result)))
  {
    int index = boost::lexical_cast<int>(XMLChptr2str(((DOMText *)node)->getNodeValue()));

    std::optional<NumericalSingleValueMeasure> meas =
        parse_woml_numerical_single_value_measure(theNode, "womlswo:maximumWindSpeed");
    if (!meas) throw std::runtime_error("Required maximum wind speed element missing");

    stream->maximumWindSpeed(index, *meas);

    return;
  }

  throw std::runtime_error("Required segment index element missing");
}
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:JetStream
 */
// ----------------------------------------------------------------------

JetStream *parse_woml_jet_stream(DOMNode *node){
    TRY(){JetStream *stream = parse_woml_abstract_line<JetStream>(node);

if (!stream) return nullptr;

const char *segmentPathExpr = "womlswo:segmentMaximumWinds/womlswo:SegmentMaximumWind";

TRYA(segmentPathExpr)
{
  AutoRelease<DOMXPathExpression> expression(EXPR(segmentPathExpr));
  AutoRelease<DOMXPathResult> result(
      expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

  while ((node = getResultNode(result)))
    parse_woml_jet_stream_maximum_wind_speed(node, stream);
}

return stream;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:CloudArea
 */
// ----------------------------------------------------------------------

CloudArea *parse_woml_cloud_area(DOMNode *theNode){
    TRY(){CloudArea *area = parse_woml_abstract_surface<CloudArea>(theNode);

CloudType cloudType = UNKNOWN;
std::string cloudTypeName("");
std::optional<double> cloudCoverPercent;
std::string cloudCoverEighths;

DOMNode *node;

if ((node = searchNode(theNode, "womlswo:cloudType/text()[1]")))
{
  cloudTypeName = XMLChptr2str(((DOMText *)node)->getNodeValue());
  cloudType = parseCloudType(cloudTypeName);
}
else
  throw std::runtime_error("Required cloud type element missing");

if ((node = searchNode(theNode, "womlswo:cloudCoverPercent/text()[1]")))
  cloudCoverPercent = boost::lexical_cast<double>(XMLChptr2str(((DOMText *)node)->getNodeValue()));

if ((node = searchNode(theNode, "womlswo:continuity/text()[1]")))
  cloudCoverEighths = XMLChptr2str(((DOMText *)node)->getNodeValue());

area->cloudType(cloudType, cloudTypeName);
area->cloudCoverPercent(cloudCoverPercent);
area->cloudCoverEighths(cloudCoverEighths);

return area;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:OccludedFront
 *
 * Note: Has extra data member "itsStationary"
 */
// ----------------------------------------------------------------------

OccludedFront *parse_woml_occluded_front(DOMNode *node){
    TRY(){OccludedFront *front = parse_woml_abstract_line<OccludedFront>(node);

if (!front) return nullptr;

if (!(node = searchNode(node, "womlswo:stationary/text()[1]")))
  front->stationary(false);
else
  front->stationary(XMLChptr2str(((DOMText *)node)->getNodeValue()) == "true");

return front;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:SurfacePrecipitationArea
 */
// ----------------------------------------------------------------------

SurfacePrecipitationArea *parse_woml_surface_precipitation_area(DOMNode *theNode){TRY(){
    SurfacePrecipitationArea *area = parse_woml_abstract_surface<SurfacePrecipitationArea>(theNode);
RainPhase rainPhase = unknown;
std::string rainPhaseName;
std::optional<double> continuity, showeriness;

DOMNode *node;
if ((node = searchNode(theNode, "womlswo:rainPhase/text()[1]")))
{
  rainPhaseName = XMLChptr2str(((DOMText *)node)->getNodeValue());
  rainPhase = parseRainPhase(rainPhaseName);
}

if ((node = searchNode(theNode, "womlswo:continuity/text()[1]")))
  continuity = boost::lexical_cast<double>(XMLChptr2str(((DOMText *)node)->getNodeValue()));

if ((node = searchNode(theNode, "womlswo:showeriness/text()[1]")))
  showeriness = boost::lexical_cast<double>(XMLChptr2str(((DOMText *)node)->getNodeValue()));

area->rainPhase(rainPhase, rainPhaseName);
area->continuity(continuity);
area->showeriness(showeriness);
area->approximateRainFall(parse_woml_numerical_single_value_measure(theNode,
                                                                    "womlswo:approximateRainFall"));

return area;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:ParameterValueSetArea
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet *parse_woml_geophysical_parameter_value_set(
    DOMNode *node,
    bool multipleValues = false,
    const char *pathExpr =
        "womlqty:parameterValueSet/womlqty:GeophysicalParameterValueSet/womlqty:parameterValue/"
        "womlqty:GeophysicalParameterValue");

ParameterValueSetArea *parse_woml_parameter_value_set_area(DOMNode *node){
    TRY(){ParameterValueSetArea *area = parse_woml_abstract_surface<ParameterValueSetArea>(node);

area->param(parse_woml_geophysical_parameter_value_set(node, true));

return area;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a point meteorologial symbol
 */
// ----------------------------------------------------------------------

PointMeteorologicalSymbol *parse_woml_point_meteorological_symbol(DOMNode *node){TRY(){
    PointMeteorologicalSymbol *symbol = parse_woml_abstract_point<PointMeteorologicalSymbol>(node);
symbol->symbol(parse_woml_meteorological_symbol(node));

// Using 'shortInfos' member to store component info text

MeteorologicalAnalysisInfo longInfos;
symbol->addShortInfos(parse_woml_longinfo(node, longInfos));

return symbol;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:GeophysicalParameter
 */
// ----------------------------------------------------------------------

GeophysicalParameter parse_woml_geophysical_parameter(
    DOMNode *node,
    const char *pathExpr = "womlqty:parameter/womlqty:GeophysicalParameter/womlqty:reference"){
    TRYFA(pathExpr){std::string param = "";
int number = -1;

AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

DOMText *text;
if ((node = getResultNode(result, &text, false)))
  if (text)
  {
    param = XMLChptr2str(text->getNodeValue());

    //				DOMElement *elem = (DOMElement *) node;
    //				std::string scheme(ATTR(elem,"scheme"));
    //
    //				if(scheme == "fmi")
    //					number = boost::lexical_cast<int>(param);
  }

return GeophysicalParameter(param, number);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse wolmqty:CategoryValueMeasure
 */
// ----------------------------------------------------------------------

MeasureValue *parse_woml_category_value_measure(
    DOMNode *node, uint nodeIndex, const char *pathExpr = "womlqty:category"){TRYFA(pathExpr){
    if ((node = searchNode(node,
                           (std::string(pathExpr) + "[" +
                            Fmi::to_string(nodeIndex) + "]")
                               .c_str()))){DOMNode *text = ((DOMText *)searchNode(node, "text()"));
DOMElement *elem = (DOMElement *)node;

std::string category(text ? XMLChptr2str(text->getNodeValue()) : "");
std::string codebase(ATTR(elem, "codebase"));

return new CategoryValueMeasure(category, codebase);
}
else if (nodeIndex == 1) throw std::runtime_error("Required category element missing");
else return nullptr;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse wolmqty:FlowDirectionMeasure
 */
// ----------------------------------------------------------------------

MeasureValue *parse_woml_flow_direction_measure(
    DOMNode *theNode,
    const char *compassPointPathExpr = "womlqty:direction/gml:CompassPoint",
    const char *directionVectorPathExpr = "womlqty:direction/gml:DirectionVector/gml:vector"){
    TRY(){DOMNode * node;
DOMNode *text;

std::string compassPoint;

if ((node = searchNode(theNode, compassPointPathExpr)) &&
    (text = ((DOMText *)searchNode(node, "text()[1]"))))
  compassPoint = XMLChptr2str(text->getNodeValue());

std::string directionVector;

if ((node = searchNode(theNode, directionVectorPathExpr)) &&
    (text = ((DOMText *)searchNode(node, "text()[1]"))))
  directionVector = XMLChptr2str(text->getNodeValue());

return new FlowDirectionMeasure(compassPoint, directionVector);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse wolmqty:value
 */
// ----------------------------------------------------------------------

MeasureValue *parse_woml_parameter_measure_value(DOMNode *node,
                                                 uint nodeIndex,
                                                 const char *pathExpr = "womlqty:value/*[1]")
{
  TRYFA(pathExpr)
  {
    AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    if ((node = getResultNode(result)))
    {
      std::string tagName = XMLChptr2str(node->getLocalName());

      if (tagName == "CategoryValueMeasure")
        // ParameterValueSetArea can have multiple category values (warning symbols); pass on the
        // node index (1,2, ...)
        //
        return parse_woml_category_value_measure(node, nodeIndex);
      else if (tagName == "FlowDirectionMeasure")
        return parse_woml_flow_direction_measure(node);
      else if (tagName == "NumericalSingleValueMeasure")
      {
        std::optional<NumericalSingleValueMeasure> meas =
            parse_woml_numerical_single_value_measure(node, "womlqty:numericalValue");

        if (meas) return new NumericalSingleValueMeasure(*meas);

        throw std::runtime_error("Invalid NumericalSingleValueMeasure element");
      }
      else if (tagName == "NumericalValueRangeMeasure")
      {
        std::optional<NumericalValueRangeMeasure> meas = parse_woml_numerical_value_range_measure(
            node, "womlqty:numericalValueLowerLimit", "womlqty:numericalValueUpperLimit");

        if (meas) return new NumericalValueRangeMeasure(*meas);

        throw std::runtime_error("Invalid NumericalValueRangeMeasure element");
      }
      else
        throw std::runtime_error("Unknown element " + tagName);
    }
    else
      throw std::runtime_error("Measure value element expected");
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:GeophysicalParameterValue
 */
// ----------------------------------------------------------------------

void parse_woml_geophysical_parameter_value(DOMNode *node,
                                            GeophysicalParameterValueSet *values,
                                            bool multipleValues = false){
    TRY(){GeophysicalParameter param(parse_woml_geophysical_parameter(node));
Elevation elevation(parse_woml_elevation(node));

MeasureValue *measValue;
uint nodeIndex = 0;

do
{
  nodeIndex++;

  if ((measValue = parse_woml_parameter_measure_value(node, nodeIndex)))
    values->add(GeophysicalParameterValue(param, measValue, elevation));
} while (measValue && multipleValues);
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:GeophysicalParameterValueSet
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet *parse_woml_geophysical_parameter_value_set(DOMNode *node,
                                                                         bool multipleValues,
                                                                         const char *pathExpr){
    TRYFA(pathExpr){GeophysicalParameterValueSet *values = new GeophysicalParameterValueSet;

AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

while ((node = getResultNode(result)))
  parse_woml_geophysical_parameter_value(node, values, multipleValues);

return values;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:ParameterValueSetPoint
 */
// ----------------------------------------------------------------------

ParameterValueSetPoint *parse_woml_parameter_value_set_point(DOMNode *node){
    TRY(){ParameterValueSetPoint *point = parse_woml_abstract_point<ParameterValueSetPoint>(node);

point->param(parse_woml_geophysical_parameter_value_set(node));

// Using 'shortInfos' member to store component info text

MeteorologicalAnalysisInfo longInfos;
point->addShortInfos(parse_woml_longinfo(node, longInfos));

return point;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse woml:TimeSeriesSlot
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet *parse_woml_parameter_timeseriesslot(
    DOMNode *node,
    std::optional<Fmi::DateTime> &validTime,
    bool multipleValues = false)  // By default load only parameter's first value (category)
{
  TRY()
  {
    validTime = parse_gml_valid_time_instant(node);
    GeophysicalParameterValueSet *values =
        parse_woml_geophysical_parameter_value_set(node, multipleValues);

    return values;
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse timeseries point object
 */
// ----------------------------------------------------------------------

template <typename T>
T *parse_woml_parameter_timeseriespoint(
    const Fmi::TimePeriod &timePeriod,
    DOMNode *node,
    bool multipleValues = false,  // By default load only parameter's first value (category)
    const char *classNameExt = nullptr,
    const char *pathExpr = "womlqty:timeSlots/womlqty:TimeSeriesSlot")
{
  TRYFA(pathExpr)
  {
    T *tsp = new T(std::string(classNameExt ? classNameExt : ""));

    // Set forecast/analysis time period and feature validtime (validtime is checked but
    // not actually used by frontier)

    tsp->timePeriod(timePeriod);
    tsp->validTime(timePeriod.begin());

    AutoRelease<DOMXPathExpression> expression(EXPR(pathExpr));
    AutoRelease<DOMXPathResult> result(
        expression->evaluate(node, DOMXPathResult::ITERATOR_RESULT_TYPE, 0));

    std::optional<Fmi::DateTime> validTime;

    while ((node = getResultNode(result)))
    {
      GeophysicalParameterValueSet *values =
          parse_woml_parameter_timeseriesslot(node, validTime, multipleValues);
      tsp->add(validTime, values);
    }

    // Sort the time serie and parameter values (based on elevation) within each time instant

    tsp->sort();

    return tsp;
  }
  CATCH
}

template <typename T>
void parse_woml_parameter_timeseriespoint(T &theWeatherObject, DOMNode *node)
{
  TRY()
  {
    // Class name (eg. surfaceWeather) and class name "extension" (eg. [surfaceWeather]Tempo) is
    // taken from gml:id.
    //
    // Class name extension is used for surfaceWeather[Tempo|Prob] and surfaceVisibility[Tempo|Prob]
    // to identify the basic (""), tempo ("Tempo") and prob ("Prob") values
    //
    DOMElement *elem = (DOMElement *)node;
    std::string className = ATTR(elem, "gml:id"), classNameExt;
    const char *p;

    if ((className == "cloudLayers") || (className == "cloudLayersCB"))
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<CloudLayers>(theWeatherObject.validTime(), node,
                                                            false, className.c_str()));
    else if (className == "contrails")
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<Contrails>(theWeatherObject.validTime(), node));
    else if (className == "Icing")
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<Icing>(theWeatherObject.validTime(), node));
    else if (className == "turbulence")
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<Turbulence>(theWeatherObject.validTime(), node));
    else if (className == "migratoryBirds")
      theWeatherObject.addFeature(parse_woml_parameter_timeseriespoint<MigratoryBirds>(
          theWeatherObject.validTime(), node, true));
    else if (className.find(p = "surfaceVisibility") == 0)
    {
      // Sync basic symbol with surfaceWeather
      //
      // 22-Nov-2012: No sync for surfaceWeather and surfaceVisibility
      //
      classNameExt = className.substr(strlen(p));
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<SurfaceVisibility>(
              theWeatherObject.validTime(), node, false, classNameExt.c_str()),
          false /* classNameExt.empty() */);
    }
    else if (className.find(p = "surfaceWeather") == 0)
    {
      // Sync basic symbol with surfaceVisibility
      //
      // 22-Nov-2012: No sync for surfaceWeather and surfaceVisibility
      //
      classNameExt = className.substr(strlen(p));
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<SurfaceWeather>(
              theWeatherObject.validTime(), node, false, classNameExt.c_str()),
          false /* classNameExt.empty() */);
    }
    else if (className == "winds")
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<Winds>(theWeatherObject.validTime(), node));
    else if (className == "zeroTolerance")
      theWeatherObject.addFeature(
          parse_woml_parameter_timeseriespoint<ZeroTolerance>(theWeatherObject.validTime(), node));
  }
  CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse meteorological objects
 */
// ----------------------------------------------------------------------

template <typename T>
void parse_woml_meteorologicalobject(T &theWeatherObject, DOMNode *node){
    TRY(){std::string name = XMLChptr2str(node->getLocalName());

if (name == /*"womlqty:*/ "ParameterTimeSeriesPoint")
  parse_woml_parameter_timeseriespoint(theWeatherObject, node);
else if (name == /*"womlswo:*/ "ColdAdvection")
{
  ColdAdvection *coldAdvection = parse_woml_abstract_line<ColdAdvection>(node);

  if (coldAdvection) theWeatherObject.addFeature(coldAdvection);
}
else if (name == /*"womlswo:*/ "ColdFront")
{
  ColdFront *coldFront = parse_woml_abstract_line<ColdFront>(node);

  if (coldFront) theWeatherObject.addFeature(coldFront);
}
else if (name == /*"womlswo:*/ "JetStream")
{
  JetStream *jetStream = parse_woml_jet_stream(node);

  if (jetStream) theWeatherObject.addFeature(jetStream);
}
else if (name == /*"womlswo:*/ "OccludedFront")
{
  OccludedFront *occludedFront = parse_woml_occluded_front(node);

  if (occludedFront) theWeatherObject.addFeature(occludedFront);
}
else if (name == /*"womlswo:*/ "Ridge")
{
  Ridge *ridge = parse_woml_abstract_line<Ridge>(node);

  if (ridge) theWeatherObject.addFeature(ridge);
}
else if (name == /*"womlswo:*/ "Trough")
{
  Trough *trough = parse_woml_abstract_line<Trough>(node);

  if (trough) theWeatherObject.addFeature(trough);
}
else if (name == /*"womlswo:*/ "UpperTrough")
{
  UpperTrough *upperTrough = parse_woml_abstract_line<UpperTrough>(node);

  if (upperTrough) theWeatherObject.addFeature(upperTrough);
}
else if (name == /*"womlswo:*/ "WarmAdvection")
{
  WarmAdvection *warmAdvection = parse_woml_abstract_line<WarmAdvection>(node);

  if (warmAdvection) theWeatherObject.addFeature(warmAdvection);
}
else if (name == /*"womlswo:*/ "WarmFront")
{
  WarmFront *warmFront = parse_woml_abstract_line<WarmFront>(node);

  if (warmFront) theWeatherObject.addFeature(warmFront);
}
else if (name == /*"womlswo:*/ "PointMeteorologicalSymbol")
  theWeatherObject.addFeature(parse_woml_point_meteorological_symbol(node));
else if (name == /*"womlswo:*/ "AntiCyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<AntiCyclone>(node));
else if (name == /*"womlswo:*/ "Antimesocyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<Antimesocyclone>(node));
else if (name == /*"womlswo:*/ "Cyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<Cyclone>(node));
else if (name == /*"womlswo:*/ "HighPressureCenter")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<HighPressureCenter>(node));
else if (name == /*"womlswo:*/ "LowPressureCenter")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<LowPressureCenter>(node));
else if (name == /*"womlswo:*/ "Mesocyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<Mesocyclone>(node));
else if (name == /*"womlswo:*/ "Mesolow")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<Mesolow>(node));
else if (name == /*"womlswo:*/ "PolarCyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<PolarCyclone>(node));
else if (name == /*"womlswo:*/ "PolarLow")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<PolarLow>(node));
else if (name == /*"womlswo:*/ "TropicalCyclone")
  theWeatherObject.addFeature(parse_woml_pressure_center_type<TropicalCyclone>(node));
else if (name == /*"womlswo:*/ "ConvectiveStorm")
  theWeatherObject.addFeature(parse_woml_storm_type<ConvectiveStorm>(node));
else if (name == /*"womlswo:*/ "Storm")
  theWeatherObject.addFeature(parse_woml_storm_type<Storm>(node));
else if (name == /*"womlswo:*/ "ParameterValueSetPoint")
  theWeatherObject.addFeature(parse_woml_parameter_value_set_point(node));
else if (name == /*"womlswo:*/ "CloudArea")
  theWeatherObject.addFeature(parse_woml_cloud_area(node));
else if (name == /*"womlswo:*/ "SurfacePrecipitationArea")
  theWeatherObject.addFeature(parse_woml_surface_precipitation_area(node));
else if (name == /*"womlswo:*/ "ParameterValueSetArea")
  theWeatherObject.addFeature(parse_woml_parameter_value_set_area(node));
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse WeatherAnalysis data
 */
// ----------------------------------------------------------------------

std::shared_ptr<MeteorologicalAnalysis> parse_woml_meteorological_analysis(DOMNode *node){
    TRY(){std::shared_ptr<MeteorologicalAnalysis> analysis(new MeteorologicalAnalysis());

// Note: envelope is taken from targetRegion

parse_woml_target_regions(*analysis, node);

analysis->dataSource(parse_woml_used_reference_data(node));
analysis->creator(parse_woml_creator(node));
analysis->creationTime(parse_woml_creation_time(node));
analysis->validTime(parse_gml_required_valid_time(node));
analysis->analysisTime(parse_woml_required_time(node, "womlcore:analysisTime"));
analysis->latestModificationTime(parse_woml_latest_modification_time(node));

MeteorologicalAnalysisInfo shortInfos, longInfos;
analysis->addShortInfos(parse_woml_shortinfo(node, shortInfos));
analysis->addLongInfos(parse_woml_longinfo(node, longInfos));

AutoRelease<DOMXPathExpression> expression(EXPR("womlcore:member/*[1]"));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

while ((node = getResultNode(result)))
  parse_woml_meteorologicalobject(*analysis, node);

return analysis;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse WeatherForecast data
 */
// ----------------------------------------------------------------------

std::shared_ptr<WeatherForecast> parse_woml_weather_forecast(documentType docType, DOMNode *node){
    TRY(){std::shared_ptr<WeatherForecast> forecast(new WeatherForecast());

// Note: envelope is taken from targetRegion

parse_woml_target_regions(*forecast, node);

forecast->dataSource(parse_woml_used_reference_data(node));
forecast->creator(parse_woml_creator(node));
forecast->creationTime(parse_woml_creation_time(node));
forecast->validTime(parse_gml_required_valid_time(node));
forecast->forecastTime(parse_woml_required_time(node, "womlcore:forecastTime"));
forecast->latestModificationTime(parse_woml_latest_modification_time(node));

WeatherForecastInfo shortInfos, longInfos;
forecast->addShortInfos(parse_woml_shortinfo(node, shortInfos));
forecast->addLongInfos(parse_woml_longinfo(node, longInfos));

AutoRelease<DOMXPathExpression> expression(EXPR("womlcore:member/*[1]"));
AutoRelease<DOMXPathResult> result(expression->evaluate(node,
                                                        DOMXPathResult::ITERATOR_RESULT_TYPE,
                                                        0));

while ((node = getResultNode(result)))
  parse_woml_meteorologicalobject(*forecast, node);

return forecast;
}
CATCH
}

// ----------------------------------------------------------------------
/*!
 * \brief Parse a WOML file
 */
// ----------------------------------------------------------------------

Weather parse(const std::filesystem::path &thePath, documentType docType, bool strict)
{
  TRY()
  {
    if (!std::filesystem::exists(thePath))
      throw std::runtime_error("The file '" + thePath.string() + "' does not exist");

    // Initialise Xerces-C and XQilla
    XQillaPlatformUtils::initialize();

    // Get the XQilla DOMImplementation object
    DOMImplementation *xqillaImplementation =
        DOMImplementationRegistry::getDOMImplementation(X("XPath2 3.0"));

    if (!xqillaImplementation)
    {
      throw std::runtime_error("Could not get DOM impelementation");
    }

    Weather weather;

    Weather::strictMode(strict);

    // Autoreleases must be released before XQillaPlatformUtils::terminate()
    //
    TRYA(thePath.string())
    {
      // Create a DOMLSParser object
      AutoRelease<DOMLSParser> parser(
          xqillaImplementation->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0));
      parser->getDomConfig()->setParameter(XMLUni::fgDOMNamespaces, true);
      parser->getDomConfig()->setParameter(XMLUni::fgXercesSchema, false);
      parser->getDomConfig()->setParameter(XMLUni::fgDOMValidateIfSchema, false);

      // Parse the document
      DOMDocument *doc = parser->parseURI(thePath.string().c_str());
      if (!doc)
      {
        throw std::runtime_error("Could not parse '" + thePath.string() + "'");
      }

      // Get root element
      DOMElement *root = doc->getDocumentElement();
      if (!root)
      {
        throw std::runtime_error("Could not get root element from '" + thePath.string() + "'");
      }

      // Get namespace resolver
      AutoRelease<DOMXPathNSResolver> nsR(nsResolver::set(doc, doc->createNSResolver(root)));

      std::string rootName = XMLChptr2str(root->getLocalName());

      if (rootName == "WeatherForecast")
      {
        if ((docType != conceptualmodelforecast) && (docType != aerodromeforecast))
          throw std::runtime_error(
              rootName + ": document type is not 'conceptualmodelforecast': " + thePath.string());

        weather.forecast(parse_woml_weather_forecast(docType, (DOMNode *)root));
      }
      else if (rootName == "MeteorologicalAnalysis")
      {
        if (docType != conceptualmodelanalysis)
          throw std::runtime_error(
              rootName + ": document type is not 'conceptualmodelanalysis': " + thePath.string());

        weather.analysis(parse_woml_meteorological_analysis((DOMNode *)root));
      }
      else
        throw std::runtime_error("Unexpected tag <" + rootName + "> at top level of " +
                                 thePath.string());
    }

    // Terminate Xerces-C and XQilla using XQillaPlatformUtils
    XQillaPlatformUtils::terminate();

    return weather;
  }
  catch (XQillaException &exc) { XQEXC(std::string(UTF8(exc.getString())).c_str()); }
  CATCH
}

}  // namespace woml
