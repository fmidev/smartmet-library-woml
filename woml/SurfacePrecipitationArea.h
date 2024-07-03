// ======================================================================
/*!
 * \brief woml::SurfacePrecipitationArea
 */
// ======================================================================

#pragma once

#include "AbstractSurfaceObject.h"
#include "Feature.h"
#include "MeasureValue.h"
#include "RainPhase.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <string>

namespace woml
{
class FeatureVisitor;

class SurfacePrecipitationArea : public AbstractSurfaceObject
{
 public:
  SurfacePrecipitationArea();

  virtual void visit(FeatureVisitor& theVisitor) const;

  void rainPhase(RainPhase thePhase, const std::string& thePhaseName);
  RainPhase rainPhase() const;
  const std::string& rainPhaseName() const;

  void continuity(std::optional<double> thePercentage);
  void showeriness(std::optional<double> thePercentage);
  void approximateRainFall(const std::optional<NumericalSingleValueMeasure>& theAmount);

  void innerArea(SurfacePrecipitationArea* theArea);

 private:
  RainPhase itsRainPhase;
  std::string itsRainPhaseName;
  std::optional<double> itsContinuity;
  std::optional<double> itsShoweriness;
  std::optional<NumericalSingleValueMeasure> itsApproximateRainFall;

  boost::ptr_list<SurfacePrecipitationArea> itsInnerArea;

};  // class SurfacePrecipitationArea

}  // namespace woml
