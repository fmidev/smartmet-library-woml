// ======================================================================
/*!
 * \brief woml::AbstractSurfaceObject
 */
// ======================================================================

#ifndef WOML_ABSTRACTSURFACEOBJECT_H
#define WOML_ABSTRACTSURFACEOBJECT_H

#include "Feature.h"
#include "Envelope.h"
#include "Elevation.h"
#include "CubicSplineSurface.h"
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

	void envelope(const boost::optional<Envelope> & theEnvelope);

	void elevation(const boost::optional<Elevation> & theElevation);
	const boost::optional<Elevation> & elevation() const;

	void controlSurface(const CubicSplineSurface & theControlSurface);
	const CubicSplineSurface & controlSurface() const;

	typedef std::list<TargetRegion> TargetRegionList;
	void addTargetRegion(const TargetRegion & theTargetRegion);
	typedef TargetRegionList::const_iterator TargetRegions_const_iterator;
	TargetRegions_const_iterator TargetRegions_begin() const;
	TargetRegions_const_iterator TargetRegions_end() const;

  protected:
	boost::optional<Envelope> itsBoundedBy;
	boost::optional<Elevation> itsElevation;
	CubicSplineSurface itsControlSurface;
	TargetRegionList itsTargetRegions;

  }; // class AbstractSurfaceObject

} // namespace woml

#endif // WOML_ABSTRACTSURFACEOBJECT_H
