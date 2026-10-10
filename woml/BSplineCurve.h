// ======================================================================
/*!
 * \brief woml::BSplineCurve
 */
// ======================================================================

#pragma once

#include "BSpline.h"
#include <list>

namespace woml
{
class BSplineCurve
{
 public:
  void add(const BSpline& theSpline);
  void lineString(const BSpline& theLineStringPoints);
  const BSpline& lineString() const;

  using BSplineList = std::list<BSpline>;
  using BSplines_const_iterator = BSplineCurve::BSplineList::const_iterator;
  BSplines_const_iterator BSplines_begin() const;
  BSplines_const_iterator BSplines_end() const;

 private:
  BSplineList itsBSplineSegments;
  BSpline itsLineStringPoints;

};  // class BSplineCurve
}  // namespace woml
