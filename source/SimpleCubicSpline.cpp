// ======================================================================
/*!
 * \brief woml::SimpleCubicSpline
 */
// ======================================================================

#include "SimpleCubicSpline.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Add new control point
 */
// ----------------------------------------------------------------------

void SimpleCubicSpline::add(const Point& thePoint) { itsPosList.push_back(thePoint); }
// ----------------------------------------------------------------------
/*!
 * \brief Test if the container is empty
 */
// ----------------------------------------------------------------------

bool SimpleCubicSpline::empty() const { return itsPosList.empty(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the size of the spline
 */
// ----------------------------------------------------------------------

SimpleCubicSpline::size_type SimpleCubicSpline::size() const { return itsPosList.size(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinates at the given position
 */
// ----------------------------------------------------------------------

const Point& SimpleCubicSpline::operator[](size_type theIndex) const
{
  return itsPosList[theIndex];
}

}  // namespace woml
