// ======================================================================
/*!
 * \brief woml::Elevation
 */
// ======================================================================

#pragma once

#include "MeasureValue.h"
#include <boost/optional.hpp>

namespace woml
{
class Elevation
{
 public:
  Elevation();
  Elevation(const boost::optional<NumericalSingleValueMeasure>& theValue);
  Elevation(const boost::optional<NumericalValueRangeMeasure>& theRange);
  bool bounded() const;
  const boost::optional<NumericalSingleValueMeasure>& value() const;
  boost::optional<NumericalSingleValueMeasure> lowerLimit() const;
  boost::optional<NumericalSingleValueMeasure> upperLimit() const;

 private:
  bool itsBounded;
  boost::optional<NumericalSingleValueMeasure> itsValue;
  boost::optional<NumericalValueRangeMeasure> itsRange;

};  // class Elevation
}  // namespace woml

