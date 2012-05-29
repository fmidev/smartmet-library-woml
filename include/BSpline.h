// ======================================================================
/*!
 * \brief woml::BSpline
 */
// ======================================================================

#ifndef WOML_BSPLINE_H
#define WOML_BSPLINE_H

#include "Point.h"
#include <vector>

namespace woml
{
  class BSpline
  {
  public:
	void add(const Point & thePoint);

	typedef std::vector<Point> value_type;
	typedef value_type::size_type size_type;

	bool empty() const;
	size_type size() const;
	const Point & operator[](size_type theIndex) const;

  private:
	value_type itsPosList;

  }; // BSpline
} // namespace woml

#endif // WOML_BSPLINE_H
