// ======================================================================
/*!
 * \brief woml::CubicSplineCurve
 */
// ======================================================================

#include "CubicSplineCurve.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Add segment to the spline
 */
// ----------------------------------------------------------------------

void CubicSplineCurve::add(const SimpleCubicSpline & theSpline)
{
  itsCubicSplineSegments.push_back(theSpline);
}


} // namespace woml
