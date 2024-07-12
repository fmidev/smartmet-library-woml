// ======================================================================
/*!
 * \brief woml::Elevation
 */
// ======================================================================

#pragma once

#include "MeasureValue.h"
#include <optional>

namespace woml
{
class Elevation
{
 public:
  Elevation();
  Elevation(const std::optional<NumericalSingleValueMeasure>& theValue);
  Elevation(const std::optional<NumericalValueRangeMeasure>& theRange);
  bool bounded() const;
  const std::optional<NumericalSingleValueMeasure>& value() const;
  std::optional<NumericalSingleValueMeasure> lowerLimit() const;
  std::optional<NumericalSingleValueMeasure> upperLimit() const;

 private:
  bool itsBounded;
  std::optional<NumericalSingleValueMeasure> itsValue;
  std::optional<NumericalValueRangeMeasure> itsRange;

};  // class Elevation
}  // namespace woml
