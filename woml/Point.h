// ======================================================================
/*!
 * \brief woml::Point
 */
// ======================================================================

#pragma once

#include <boost/optional.hpp>

namespace woml
{
class Point
{
 public:
  Point(double theLon, double theLat) : itsLon(theLon), itsLat(theLat) {}
  double lon() const { return itsLon; }
  double lat() const { return itsLat; }
 private:
  Point();
  double itsLon;
  double itsLat;

};  // class Point

class Rect
{
 public:
  Rect(boost::optional<Point>& theLowerCorner, boost::optional<Point>& theUpperCorner)
      : itsLowerCorner(theLowerCorner), itsUpperCorner(theUpperCorner)
  {
  }
  const boost::optional<Point>& lowerCorner() const { return itsLowerCorner; }
  const boost::optional<Point>& upperCorner() const { return itsUpperCorner; }
 private:
  Rect();
  boost::optional<Point> itsLowerCorner;
  boost::optional<Point> itsUpperCorner;

};  // class Rect
}  // namespace woml

