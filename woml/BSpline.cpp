// ======================================================================
/*!
 * \brief woml::BSpline
 */
// ======================================================================

#include "BSpline.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Add new control point
 */
// ----------------------------------------------------------------------

void BSpline::add(const Point& thePoint) { itsPosList.push_back(thePoint); }
// ----------------------------------------------------------------------
/*!
 * \brief Test if the container is empty
 */
// ----------------------------------------------------------------------

bool BSpline::empty() const { return itsPosList.empty(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the size of the spline
 */
// ----------------------------------------------------------------------

BSpline::size_type BSpline::size() const { return itsPosList.size(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinates at the given position
 */
// ----------------------------------------------------------------------

const Point& BSpline::operator[](size_type theIndex) const { return itsPosList[theIndex]; }
}  // namespace woml
