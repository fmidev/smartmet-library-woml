// ======================================================================
/*!
 * \brief woml::CubicSplineCurve
 */
// ======================================================================

#ifndef WOML_CUBICSPLINECURVE_H
#define WOML_CUBICSPLINECURVE_H

#include "SimpleCubicSpline.h"
#include <list>

namespace woml
{
  class CubicSplineCurve
  {
  public:
	void add(const SimpleCubicSpline & theSpline);
	void lineString(const SimpleCubicSpline & theLineStringPoints);
	const SimpleCubicSpline & lineString() const;

	typedef std::list<SimpleCubicSpline>::const_iterator const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

  private:
	std::list<SimpleCubicSpline> itsCubicSplineSegments;
	SimpleCubicSpline itsLineStringPoints;

  }; // class CubicSplineCurve
} // namespace woml

#endif // WOML_CUBICSPLINECURVE_H
