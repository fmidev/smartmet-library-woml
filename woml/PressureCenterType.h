// ======================================================================
/*!
 * \brief woml::PressureCenterType
 */
// ======================================================================

#pragma once

#include "AbstractPointObject.h"
#include "FeatureVisitor.h"
#include "MeasureValue.h"

#define PressureCenterTypeDerivedClass(c)                                     \
  class c : public PressureCenterType                                         \
  {                                                                           \
   public:                                                                    \
    c() : PressureCenterType() {}                                             \
    void visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); } \
    const char* className() const { return #c; }                              \
  }

namespace woml
{
class PressureCenterType : public AbstractPointObject
{
 public:
  PressureCenterType();
  virtual ~PressureCenterType() {}
  void tendency(const std::string& theTendency);
  const std::string& tendency() const;

  void maxwindspeed(const std::optional<NumericalSingleValueMeasure>& theMaxWindSpeed);
  const std::optional<NumericalSingleValueMeasure>& maxwindspeed() const;

 private:
  std::string itsTendency;
  std::optional<NumericalSingleValueMeasure> itsMaxWindSpeed;

};  // class PressureCenterType

PressureCenterTypeDerivedClass(AntiCyclone);
PressureCenterTypeDerivedClass(Antimesocyclone);
PressureCenterTypeDerivedClass(Cyclone);
PressureCenterTypeDerivedClass(HighPressureCenter);
PressureCenterTypeDerivedClass(LowPressureCenter);
PressureCenterTypeDerivedClass(Mesocyclone);
PressureCenterTypeDerivedClass(Mesolow);
PressureCenterTypeDerivedClass(PolarCyclone);
PressureCenterTypeDerivedClass(PolarLow);
PressureCenterTypeDerivedClass(TropicalCyclone);

}  // namespace woml
