// ======================================================================
/*!
 * \brief woml::StormType
 */
// ======================================================================

#pragma once

#include "AbstractPointObject.h"
#include "FeatureVisitor.h"
#include "MeasureValue.h"
#include "RainPhase.h"

// c is the class name, it cannot be parenthesized
// NOLINTBEGIN(bugprone-macro-parentheses)
#define StormTypeClass(c)                                                     \
  class c : public StormType                                                  \
  {                                                                           \
   public:                                                                    \
    c() : StormType() {}                                                      \
    void visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); } \
    const char* className() const { return #c; }                              \
  }
// NOLINTEND(bugprone-macro-parentheses)

namespace woml
{
class StormType : public AbstractPointObject
{
 public:
  StormType();
  ~StormType() override = default;
  void rainPhase(RainPhase theRainPhase);
  RainPhase rainPhase() const;
  void approximateRainFall(
      const std::optional<NumericalSingleValueMeasure>& theApproximateRainFall);
  const std::optional<NumericalSingleValueMeasure>& approximateRainFall() const;
  void isThunderStorm(const std::optional<bool>& IsThunderStorm);
  const std::optional<bool>& isThunderStorm() const;

 private:
  RainPhase itsRainPhase;
  std::optional<NumericalSingleValueMeasure> itsApproximateRainFall;
  std::optional<bool> itsIsThunderStorm;

};  // class StormType

StormTypeClass(ConvectiveStorm);
StormTypeClass(Storm);

}  // namespace woml
