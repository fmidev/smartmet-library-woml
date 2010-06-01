// ======================================================================
/*!
 * \brief woml::SimpleCubicSpline
 */
// ======================================================================

#ifndef WOML_SIMPLECUBICSPLINE_H
#define WOML_SIMPLECUBICSPLINE_H

#include "Point.h"
#include <vector>

namespace woml
{
  class SimpleCubicSpline
  {
  public:
	void add(const Point & thePoint);
  private:
	std::vector<Point> itsPosList;

  }; // SimpleCubicSpline
} // namespace woml

#endif // WOML_SIMPLECUBICSPLINE_H
