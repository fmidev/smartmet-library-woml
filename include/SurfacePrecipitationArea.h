// ======================================================================
/*!
 * \brief woml::SurfacePrecipitationArea
 */
// ======================================================================

#ifndef WOML_SURFACEPRECIPITATIONAREA_H
#define WOML_SURFACEPRECIPITATIONAREA_H

#include "AbstractSurfaceObject.h"
#include "Feature.h"
#include "RainPhase.h"
#include "MeasureValue.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <string>

namespace woml
{
  class FeatureVisitor;

  class SurfacePrecipitationArea : public AbstractSurfaceObject
  {
  public:
	SurfacePrecipitationArea();

	virtual void visit(FeatureVisitor & theVisitor) const;

	void rainPhase(RainPhase thePhase,const std::string & thePhaseName);
	RainPhase rainPhase() const;
	const std::string & rainPhaseName() const;

	void continuity(boost::optional<double> thePercentage);
	void showeriness(boost::optional<double> thePercentage);
	void approximateRainFall(const boost::optional<NumericalSingleValueMeasure> & theAmount);

	void innerArea(SurfacePrecipitationArea * theArea);

  private:
	RainPhase itsRainPhase;
	std::string itsRainPhaseName;
	boost::optional<double> itsContinuity;
	boost::optional<double> itsShoweriness; 
	boost::optional<NumericalSingleValueMeasure> itsApproximateRainFall;

	boost::ptr_list<SurfacePrecipitationArea> itsInnerArea;

  }; // class SurfacePrecipitationArea

} // namespace woml

#endif // WOML_SURFACEPRECIPITATIONAREA_H
