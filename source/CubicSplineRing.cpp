// ======================================================================
/*!
 * \brief woml::CubicSplineRing
 */
// ======================================================================

#include "CubicSplineRing.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Add new control point
 */
// ----------------------------------------------------------------------

void CubicSplineRing::add(const Point& thePoint) { itsPosList.push_back(thePoint); }
// ----------------------------------------------------------------------
/*!
 * \brief Test if the container is empty
 */
// ----------------------------------------------------------------------

bool CubicSplineRing::empty() const { return itsPosList.empty(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the size of the spline
 */
// ----------------------------------------------------------------------

CubicSplineRing::size_type CubicSplineRing::size() const { return itsPosList.size(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinates at the given position
 */
// ----------------------------------------------------------------------

const Point& CubicSplineRing::operator[](size_type theIndex) const { return itsPosList[theIndex]; }
}  // namespace woml
