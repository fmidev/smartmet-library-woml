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

	Point(double x, double y) : lon(x), lat(y) { }
	double lon;
	double lat;

  private:
	Point();

  }; // class Point
} // namespace woml

#endif // WOML_POINT_H
