// ======================================================================
/*!
 * \brief woml::CubicSplineRing
 */
// ======================================================================

#ifndef WOML_CUBICSPLINERING_H
#define WOML_CUBICSPLINERING_H

#include "Point.h"
#include <vector>

namespace woml
{
  class CubicSplineRing
  {
  public:
	void add(const Point & thePoint);

  private:
	std::vector<Point> itsPosList;

  }; // class CubicSplineRing
} // namespace woml

#endif // WOML_CUBICSPLINERING_H
