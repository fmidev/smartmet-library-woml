// ======================================================================
/*!
 * \brief FeatureVisitor is not part of the WOML spec
 *
 * FeatureVisitor enables double dispatching for external classes.
 * Jus inherit from FeatureVisitor in order to be able to dispatch
 * based on Feature type.
 */
// ======================================================================

#ifndef WOML_FEATUREVISITOR_H
#define WOML_FEATUREVISITOR_H

namespace woml
{
  class ColdAdvection;
  class ColdFront;
  class JetStream;
  class OccludedFront;
  class Ridge;
  class Trough;
  class UpperTrough;
  class WarmAdvection;
  class WarmFront;

  class AntiCyclone;
  class Antimesocyclone;
  class Cyclone;
  class HighPressureCenter;
  class LowPressureCenter;
  class Mesocyclone;
  class Mesolow;
  class ParameterValueSetPoint;
  class PointMeteorologicalSymbol;
  class PolarCyclone;
  class PolarLow;
  class TropicalCyclone;
  class ConvectiveStorm;
  class Storm;

  class CloudArea;
  class SurfacePrecipitationArea;

  class InfoText;

  class TimeGeophysicalParameterValueSet;

  class FeatureVisitor
  {
  public:
	virtual ~FeatureVisitor() {}

	virtual void visit(const ColdAdvection & theFeature) = 0;
	virtual void visit(const ColdFront & theFeature) = 0;
	virtual void visit(const JetStream & theFeature) = 0;
	virtual void visit(const OccludedFront & theFeature) = 0;
	virtual void visit(const Ridge & theFeature) = 0;
	virtual void visit(const Trough & theFeature) = 0;
	virtual void visit(const UpperTrough & theFeature) = 0;
	virtual void visit(const WarmAdvection & theFeature) = 0;
	virtual void visit(const WarmFront & theFeature) = 0;

	virtual void visit(const AntiCyclone & theFeature) = 0;
	virtual void visit(const Antimesocyclone & theFeature) = 0;
	virtual void visit(const Cyclone & theFeature) = 0;
	virtual void visit(const HighPressureCenter & theFeature) = 0;
	virtual void visit(const LowPressureCenter & theFeature) = 0;
	virtual void visit(const Mesocyclone & theFeature) = 0;
	virtual void visit(const Mesolow & theFeature) = 0;
	virtual void visit(const ParameterValueSetPoint & theFeature) = 0;
	virtual void visit(const PointMeteorologicalSymbol & theFeature) = 0;
	virtual void visit(const PolarCyclone & theFeature) = 0;
	virtual void visit(const PolarLow & theFeature) = 0;
	virtual void visit(const TropicalCyclone & theFeature) = 0;
	virtual void visit(const ConvectiveStorm & theFeature) = 0;
	virtual void visit(const Storm & theFeature) = 0;

	virtual void visit(const CloudArea & theFeature) = 0;
	virtual void visit(const SurfacePrecipitationArea & theFeature) = 0;

	virtual void visit(const InfoText & theFeature) = 0;

	virtual void visit(const TimeGeophysicalParameterValueSet & theFeature) = 0;

  }; // class FeatureVisitor
} // namespace woml

#endif // WOML_FEATUREVISITOR_H
