// ======================================================================
/*!
 * \brief woml::SurfacePrecipitationArea
 */
// ======================================================================

#ifndef WOML_SURFACEPRECIPITATIONAREA_H
#define WOML_SURFACEPRECIPITATIONAREA_H

#include "CubicSplineSurface.h"
#include "Envelope.h"
#include "Feature.h"
#include "RainPhase.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <list>
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class SurfacePrecipitationArea : public Feature
  {
  public:
	SurfacePrecipitationArea();
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlSurface(const CubicSplineSurface & theControlSurface);
	void rainPhase(RainPhase thePhase);
	void continuity(double thePercentage);
	void showeriness(double thePercentage);
	void approximateRainFall(double theAmount);
	void innerArea(SurfacePrecipitationArea * theArea);

  private:
	Envelope itsBoundedBy;
	CubicSplineSurface itsControlSurface;
	RainPhase itsRainPhase;
	double itsContinuity;
	double itsShoweriness; 
	double itsApproximateRainFall;

	boost::ptr_list<SurfacePrecipitationArea> itsInnerArea;

  }; // class SurfacePrecipitationArea

} // namespace woml

#endif // WOML_SURFACEPRECIPITATIONAREA_H
