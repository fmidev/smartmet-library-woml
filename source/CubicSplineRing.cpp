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

void CubicSplineRing::add(const Point & thePoint)
{
  itsPosList.push_back(thePoint);
}


} // namespace woml
