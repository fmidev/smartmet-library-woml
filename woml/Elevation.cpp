// ======================================================================
/*!
 * \brief woml::Elevation
 */
// ======================================================================

#include "Elevation.h"
#include <cassert>
#include <boost/optional.hpp>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

Elevation::Elevation() : itsBounded(false), itsValue(), itsRange() {}
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Elevation::Elevation(const boost::optional<NumericalSingleValueMeasure>& theValue)
    : itsBounded(false), itsValue(theValue), itsRange()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Elevation::Elevation(const boost::optional<NumericalValueRangeMeasure>& theRange)
    : itsBounded(theRange ? true : false), itsValue(), itsRange(theRange)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief True if elevation is bounded
 */
//  ----------------------------------------------------------------------

bool Elevation::bounded() const { return itsBounded; }
// ----------------------------------------------------------------------
/*!
 * \brief Value accessor
 */
// ----------------------------------------------------------------------

const boost::optional<NumericalSingleValueMeasure>& Elevation::value() const
{
  assert(itsValue);
  return itsValue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Lower limit accessor
 */
// ----------------------------------------------------------------------

boost::optional<NumericalSingleValueMeasure> Elevation::lowerLimit() const
{
  assert(itsBounded);

  boost::optional<NumericalSingleValueMeasure> limit;
  if (itsRange) limit = itsRange->lowerLimit();

  return limit;
}

// ----------------------------------------------------------------------
/*!
 * \brief Upper limit accessor
 */
// ----------------------------------------------------------------------

boost::optional<NumericalSingleValueMeasure> Elevation::upperLimit() const
{
  assert(itsBounded);

  boost::optional<NumericalSingleValueMeasure> limit;
  if (itsRange) limit = itsRange->upperLimit();

  return limit;
}

}  // namespace woml
