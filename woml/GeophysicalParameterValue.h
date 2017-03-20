// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValue
 */
// ======================================================================

#pragma once

#include "GeophysicalParameter.h"
#include "MeasureValue.h"
#include "Elevation.h"

#include <boost/shared_ptr.hpp>

namespace woml
{
class GeophysicalParameterValue
{
 public:
  GeophysicalParameterValue(const GeophysicalParameter& theParam,
                            MeasureValue* theValue,
                            const Elevation& theElevation);

  bool operator<(const GeophysicalParameterValue& theOther) const;

  const GeophysicalParameter& parameter() const { return itsParameter; }
  const MeasureValue* value() const { return itsValue.get(); }
  MeasureValue* editableValue() const { return itsValue.get(); }
  void elevation(const Elevation& theElevation) { itsElevation = theElevation; }
  const Elevation& elevation() const { return itsElevation; }
  void labelElevation(const Elevation& theLabelElevation);
  const boost::optional<Elevation>& labelElevation() const { return itsLabelElevation; }
  // For externally defined flagbits
  //
  void setFlags(unsigned int theFlagBits) { itsFlagBits |= theFlagBits; }
  void clearFlags(unsigned int theFlagBits) { itsFlagBits &= ~theFlagBits; }
  unsigned int getFlags() const { return itsFlagBits; }
 private:
  GeophysicalParameterValue();

  const GeophysicalParameter itsParameter;
  const boost::shared_ptr<MeasureValue> itsValue;
  Elevation itsElevation;
  boost::optional<Elevation> itsLabelElevation;

  unsigned int itsFlagBits;

};  // class GeophysicalParamterValue

}  // namespace woml

