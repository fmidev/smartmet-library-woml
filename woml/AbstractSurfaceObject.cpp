// ======================================================================
/*!
 * \brief class woml::AbstractSurfaceObject
 */
// ======================================================================

#include "AbstractSurfaceObject.h"
#include "FeatureVisitor.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

AbstractSurfaceObject::AbstractSurfaceObject()
    : itsBoundedBy(), itsElevation(), itsControlSurface(), itsTargetRegions()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void AbstractSurfaceObject::envelope(const boost::optional<Envelope>& theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the elevation
 */
// ----------------------------------------------------------------------

void AbstractSurfaceObject::elevation(const boost::optional<Elevation>& theElevation)
{
  itsElevation = theElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control surface
 */
// ----------------------------------------------------------------------

void AbstractSurfaceObject::controlSurface(const CubicSplineSurface& theControlSurface)
{
  itsControlSurface = theControlSurface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control surface
 */
// ----------------------------------------------------------------------

const CubicSplineSurface& AbstractSurfaceObject::controlSurface() const
{
  return itsControlSurface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a target region
 */
// ----------------------------------------------------------------------

void AbstractSurfaceObject::addTargetRegion(const TargetRegion& theTargetRegion)
{
  if (theTargetRegion.RegionIds_begin() != theTargetRegion.RegionIds_end())
    itsTargetRegions.push_back(theTargetRegion);
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the target regions
 */
// ----------------------------------------------------------------------

AbstractSurfaceObject::TargetRegions_const_iterator AbstractSurfaceObject::TargetRegions_begin()
    const
{
  return itsTargetRegions.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the target regions
 */
// ----------------------------------------------------------------------

AbstractSurfaceObject::TargetRegions_const_iterator AbstractSurfaceObject::TargetRegions_end() const
{
  return itsTargetRegions.end();
}

}  // namespace woml
