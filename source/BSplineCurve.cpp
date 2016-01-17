// ======================================================================
/*!
 * \brief woml::BSplineCurve
 */
// ======================================================================

#include "BSplineCurve.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Add segment to the spline
 */
// ----------------------------------------------------------------------

void BSplineCurve::add(const BSpline& theSpline) { itsBSplineSegments.push_back(theSpline); }
// ----------------------------------------------------------------------
/*!
 * \brief Set line string points
 */
// ----------------------------------------------------------------------

void BSplineCurve::lineString(const BSpline& theLineStringPoints)
{
  itsLineStringPoints = theLineStringPoints;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return line string points
 */
// ----------------------------------------------------------------------

const BSpline& BSplineCurve::lineString() const { return itsLineStringPoints; }
// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the line segments
 */
// ----------------------------------------------------------------------

BSplineCurve::BSplines_const_iterator BSplineCurve::BSplines_begin() const
{
  return itsBSplineSegments.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the line segments
 */
// ----------------------------------------------------------------------

BSplineCurve::BSplines_const_iterator BSplineCurve::BSplines_end() const
{
  return itsBSplineSegments.end();
}

}  // namespace woml
