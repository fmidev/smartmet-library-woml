// ======================================================================
/*!
 * \brief woml::Point
 */
// ======================================================================

#ifndef WOML_POINT_H
#define WOML_POINT_H

namespace woml
{
  class Point
  {
  public:

	Point(double theLon, double theLat) : itsLon(theLon), itsLat(theLat) { }
	double lon() const { return itsLon; }
	double lat() const { return itsLat; }

  private:
	Point();
	double itsLon;
	double itsLat;

  }; // class Point
} // namespace woml

#endif // WOML_POINT_H
