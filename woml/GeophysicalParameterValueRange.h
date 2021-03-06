// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValueRange
 */
// ======================================================================

#pragma once

#include "GeophysicalParameter.h"

namespace woml
{
class GeophysicalParameterValueRange
{
 public:
  GeophysicalParameterValueRange(const GeophysicalParameter& theParam,
                                 double theLowerLimit,
                                 double theUpperLimit);

  const GeophysicalParameter& parameter() const { return itsParameter; }
  double lowerLimit() const { return itsLowerLimit; }
  double upperLimit() const { return itsUpperLimit; }

 private:
  GeophysicalParameterValueRange();

  GeophysicalParameter itsParameter;
  double itsLowerLimit;
  double itsUpperLimit;

};  // class GeophysicalParamterValueRange

}  // namespace woml
