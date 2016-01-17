// ======================================================================
/*!
 * \brief woml::SimpleCubicSpline
 */
// ======================================================================

#ifndef WOML_SIMPLECUBICSPLINE_H
#define WOML_SIMPLECUBICSPLINE_H

#include "Point.h"
#include <vector>

namespace woml
{
class SimpleCubicSpline
{
 public:
  void add(const Point& thePoint);

  typedef std::vector<Point> value_type;
  typedef value_type::size_type size_type;

  bool empty() const;
  size_type size() const;
  const Point& operator[](size_type theIndex) const;

 private:
  value_type itsPosList;

};  // SimpleCubicSpline
}  // namespace woml

#endif  // WOML_SIMPLECUBICSPLINE_H
