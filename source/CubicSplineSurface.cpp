// ======================================================================
/*!
 * \brief woml::CubicSplineSurface
 */
// ======================================================================

#include "CubicSplineSurface.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Add exterior to the surface
 */
// ----------------------------------------------------------------------

void CubicSplineSurface::exterior(const CubicSplineRing & theRing)
{
  itsExterior = theRing;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add interior to the surface
 */
// ----------------------------------------------------------------------

void CubicSplineSurface::interior(const CubicSplineRing & theRing)
{
  itsInterior.push_back(theRing);
}


} // namespace woml
