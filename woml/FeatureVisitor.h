// ======================================================================
/*!
 * \brief FeatureVisitor is not part of the WOML spec
 *
 * FeatureVisitor enables double dispatching for external classes.
 * Jus inherit from FeatureVisitor in order to be able to dispatch
 * based on Feature type.
 */
// ======================================================================

#pragma once

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
class ParameterValueSetArea;

class InfoText;

class CloudLayers;
class Contrails;
class Icing;
class Turbulence;
class MigratoryBirds;
class SurfaceVisibility;
class SurfaceWeather;
class Winds;
class ZeroTolerance;

class FeatureVisitor
{
 public:
  virtual ~FeatureVisitor() {}
  virtual void visit(const ColdAdvection& theFeature) = 0;
  virtual void visit(const ColdFront& theFeature) = 0;
  virtual void visit(const JetStream& theFeature) = 0;
  virtual void visit(const OccludedFront& theFeature) = 0;
  virtual void visit(const Ridge& theFeature) = 0;
  virtual void visit(const Trough& theFeature) = 0;
  virtual void visit(const UpperTrough& theFeature) = 0;
  virtual void visit(const WarmAdvection& theFeature) = 0;
  virtual void visit(const WarmFront& theFeature) = 0;

  virtual void visit(const AntiCyclone& theFeature) = 0;
  virtual void visit(const Antimesocyclone& theFeature) = 0;
  virtual void visit(const Cyclone& theFeature) = 0;
  virtual void visit(const HighPressureCenter& theFeature) = 0;
  virtual void visit(const LowPressureCenter& theFeature) = 0;
  virtual void visit(const Mesocyclone& theFeature) = 0;
  virtual void visit(const Mesolow& theFeature) = 0;
  virtual void visit(const ParameterValueSetPoint& theFeature) = 0;
  virtual void visit(const PointMeteorologicalSymbol& theFeature) = 0;
  virtual void visit(const PolarCyclone& theFeature) = 0;
  virtual void visit(const PolarLow& theFeature) = 0;
  virtual void visit(const TropicalCyclone& theFeature) = 0;
  virtual void visit(const ConvectiveStorm& theFeature) = 0;
  virtual void visit(const Storm& theFeature) = 0;

  virtual void visit(const CloudArea& theFeature) = 0;
  virtual void visit(const SurfacePrecipitationArea& theFeature) = 0;
  virtual void visit(const ParameterValueSetArea& theFeature) = 0;

  virtual void visit(const InfoText& theFeature) = 0;

  virtual void visit(const CloudLayers& theFeature) = 0;
  virtual void visit(const Contrails& theFeature) = 0;
  virtual void visit(const Icing& theFeature) = 0;
  virtual void visit(const Turbulence& theFeature) = 0;
  virtual void visit(const MigratoryBirds& theFeature) = 0;
  virtual void visit(const SurfaceVisibility& theFeature) = 0;
  virtual void visit(const SurfaceWeather& theFeature) = 0;
  virtual void visit(const Winds& theFeature) = 0;
  virtual void visit(const ZeroTolerance& theFeature) = 0;

};  // class FeatureVisitor
}  // namespace woml
