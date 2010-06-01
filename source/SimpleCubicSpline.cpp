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

void SimpleCubicSpline::add(const Point & thePoint)
{
  itsPosList.push_back(thePoint);
}


} // namespace woml
