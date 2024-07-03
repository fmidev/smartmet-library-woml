// ======================================================================
/*!
 * \brief woml::CloudArea
 */
// ======================================================================

#pragma once

#include "AbstractSurfaceObject.h"
#include "CloudType.h"
#include "CubicSplineCurve.h"
#include <string>

namespace woml
{
class Envelope;
class FeatureVisitor;

class CloudArea : public AbstractSurfaceObject
{
 public:
  CloudArea();

  virtual void visit(FeatureVisitor& theVisitor) const;

  void cloudType(CloudType theCloudType, const std::string& theCloudTypeName);
  CloudType cloudType() const;
  const std::string& cloudTypeName() const;

  void cloudCoverPercent(const std::optional<double>& theCloudCoverPercent);
  const std::optional<double>& cloudCoverPercent() const;

  void cloudCoverEighths(const std::string& theCloudCoverEighths);
  const std::string& cloudCoverEighths() const;

 private:
  CloudType itsCloudType;
  std::string itsCloudTypeName;
  std::optional<double> itsCloudCoverPercent;
  std::string itsCloudCoverEighths;

};  // class CloudArea

}  // namespace woml
