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
  class WarmFront;
  class OccludedFront;
  class ColdFront;
  class CloudAreaBorder;
  class Jet;
  class Trough;
  class UpperTrough;
  class PointMeteorologicalSymbol;

  class FeatureVisitor
  {
  public:
	virtual ~FeatureVisitor() {}

	virtual void visit(const WarmFront & theFeature) = 0;
	virtual void visit(const ColdFront & theFeature) = 0;
	virtual void visit(const OccludedFront & theFeature) = 0;
	virtual void visit(const Jet & theFeature) = 0;
	virtual void visit(const CloudAreaBorder & theFeature) = 0;
	virtual void visit(const Trough & theFeature) = 0;
	virtual void visit(const UpperTrough & theFeature) = 0;
	virtual void visit(const PointMeteorologicalSymbol & theFeature) = 0;

  }; // class FeatureVisitor
} // namespace woml

#endif // WOML_FEATUREVISITOR_H
