// ======================================================================
/*!
 * \brief woml::CubicSplineSurface
 */
// ======================================================================

#ifndef WOML_CUBICSPLINESURFACE_H
#define WOML_CUBICSPLINESURFACE_H

#include "CubicSplineRing.h"
#include <list>

namespace woml
{
  class CubicSplineSurface
  {
  public:
	void exterior(const CubicSplineRing & theRing);
	void interior(const CubicSplineRing & theRing);

  private:
	CubicSplineRing itsExterior;
	std::list<CubicSplineRing> itsInterior;

  }; // class CubicSplineSurface
} // namespace woml

#endif // WOML_CUBICSPLINESURFACE_H
