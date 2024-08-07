// ======================================================================
/*!
 * \brief woml::AbstractSurfaceObject
 */
// ======================================================================

#pragma once

#include "CubicSplineSurface.h"
#include "Elevation.h"
#include "Envelope.h"
#include "Feature.h"
#include "TargetRegion.h"
#include <list>
#include <string>

namespace woml
{
class AbstractSurfaceObject : public Feature
{
 public:
  AbstractSurfaceObject();
  virtual ~AbstractSurfaceObject() {}
  void envelope(const std::optional<Envelope>& theEnvelope);

  void elevation(const std::optional<Elevation>& theElevation);
  const std::optional<Elevation>& elevation() const;

  void controlSurface(const CubicSplineSurface& theControlSurface);
  const CubicSplineSurface& controlSurface() const;

  typedef std::list<TargetRegion> TargetRegionList;
  void addTargetRegion(const TargetRegion& theTargetRegion);
  typedef TargetRegionList::const_iterator TargetRegions_const_iterator;
  TargetRegions_const_iterator TargetRegions_begin() const;
  TargetRegions_const_iterator TargetRegions_end() const;

 protected:
  std::optional<Envelope> itsBoundedBy;
  std::optional<Elevation> itsElevation;
  CubicSplineSurface itsControlSurface;
  TargetRegionList itsTargetRegions;

};  // class AbstractSurfaceObject

}  // namespace woml
