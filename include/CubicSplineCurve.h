// ======================================================================
/*!
 * \brief woml::CubicSplineCurve
 */
// ======================================================================

#ifndef WOML_CUBICSPLINECURVE_H
#define WOML_CUBICSPLINECURVE_H

#include "SimpleCubicSpline.h"
#include <list>

namespace woml
{
  class CubicSplineCurve
  {
  public:
	void add(const SimpleCubicSpline & theSpline);

  private:
	std::list<SimpleCubicSpline> itsCubicSplineSegments;

  }; // class CubicSplineCurve
} // namespace woml

#endif // WOML_CUBICSPLINECURVE_H
