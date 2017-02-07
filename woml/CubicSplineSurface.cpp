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

void CubicSplineSurface::exterior(const CubicSplineRing& theRing) { itsExterior = theRing; }
// ----------------------------------------------------------------------
/*!
 * \brief Add interior to the surface
 */
// ----------------------------------------------------------------------

void CubicSplineSurface::interior(const CubicSplineRing& theRing)
{
  itsInterior.push_back(theRing);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get exterior of the surface
 */
// ----------------------------------------------------------------------

const CubicSplineRing& CubicSplineSurface::exterior() const { return itsExterior; }
// ----------------------------------------------------------------------
/*!
 * \brief begin-iterator for interior objects
 */
// ----------------------------------------------------------------------

CubicSplineSurface::const_iterator CubicSplineSurface::begin() const { return itsInterior.begin(); }
// ----------------------------------------------------------------------
/*!
 * \brief end-iterator
 */
// ----------------------------------------------------------------------

CubicSplineSurface::const_iterator CubicSplineSurface::end() const { return itsInterior.end(); }
}  // namespace woml
