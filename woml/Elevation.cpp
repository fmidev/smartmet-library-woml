// ======================================================================
/*!
 * \brief woml::Elevation
 */
// ======================================================================

#include "Elevation.h"
#include <optional>
#include <cassert>

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

Elevation::Elevation(const std::optional<NumericalSingleValueMeasure>& theValue)
    : itsBounded(false), itsValue(theValue), itsRange()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Elevation::Elevation(const std::optional<NumericalValueRangeMeasure>& theRange)
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

const std::optional<NumericalSingleValueMeasure>& Elevation::value() const
{
  assert(itsValue);
  return itsValue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Lower limit accessor
 */
// ----------------------------------------------------------------------

std::optional<NumericalSingleValueMeasure> Elevation::lowerLimit() const
{
  assert(itsBounded);

  std::optional<NumericalSingleValueMeasure> limit;
  if (itsRange) limit = itsRange->lowerLimit();

  return limit;
}

// ----------------------------------------------------------------------
/*!
 * \brief Upper limit accessor
 */
// ----------------------------------------------------------------------

std::optional<NumericalSingleValueMeasure> Elevation::upperLimit() const
{
  assert(itsBounded);

  std::optional<NumericalSingleValueMeasure> limit;
  if (itsRange) limit = itsRange->upperLimit();

  return limit;
}

}  // namespace woml
