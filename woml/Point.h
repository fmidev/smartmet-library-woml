// ======================================================================
/*!
 * \brief woml::Point
 */
// ======================================================================

#pragma once

#include <optional>

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
  Rect(std::optional<Point>& theLowerCorner, std::optional<Point>& theUpperCorner)
      : itsLowerCorner(theLowerCorner), itsUpperCorner(theUpperCorner)
  {
  }
  const std::optional<Point>& lowerCorner() const { return itsLowerCorner; }
  const std::optional<Point>& upperCorner() const { return itsUpperCorner; }

 private:
  Rect();
  std::optional<Point> itsLowerCorner;
  std::optional<Point> itsUpperCorner;

};  // class Rect
}  // namespace woml
