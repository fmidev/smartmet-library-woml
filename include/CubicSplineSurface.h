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

	const CubicSplineRing & exterior() const;

	typedef std::list<CubicSplineRing>::const_iterator const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

  private:
	CubicSplineRing itsExterior;
	std::list<CubicSplineRing> itsInterior;

  }; // class CubicSplineSurface
} // namespace woml

#endif // WOML_CUBICSPLINESURFACE_H
