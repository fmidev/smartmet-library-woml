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

void CubicSplineCurve::add(const SimpleCubicSpline& theSpline)
{
  itsCubicSplineSegments.push_back(theSpline);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set line string points
 */
// ----------------------------------------------------------------------

void CubicSplineCurve::lineString(const SimpleCubicSpline& theLineStringPoints)
{
  itsLineStringPoints = theLineStringPoints;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return line string points
 */
// ----------------------------------------------------------------------

const SimpleCubicSpline& CubicSplineCurve::lineString() const { return itsLineStringPoints; }
// ----------------------------------------------------------------------
/*!
 * \brief begin-iterator
 */
// ----------------------------------------------------------------------

CubicSplineCurve::const_iterator CubicSplineCurve::begin() const
{
  return itsCubicSplineSegments.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief end-iterator
 */
// ----------------------------------------------------------------------

CubicSplineCurve::const_iterator CubicSplineCurve::end() const
{
  return itsCubicSplineSegments.end();
}

}  // namespace woml
