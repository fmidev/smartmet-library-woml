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
  class CloudAreaBorder;
  class ColdFront;
  class PointMeteorologicalSymbol;
  class WarmFront;

  class FeatureVisitor
  {
  public:
	virtual ~FeatureVisitor() {}

	virtual void visit(const CloudAreaBorder & feature) = 0;
	virtual void visit(const ColdFront & feature) = 0;
	virtual void visit(const PointMeteorologicalSymbol & feature) = 0;
	virtual void visit(const WarmFront & feature) = 0;

  }; // class FeatureVisitor
} // namespace woml

#endif // WOML_FEATUREVISITOR_H
