// ======================================================================
/*!
 * \brief woml::PointMeteorologicalSymbol
 */
// ======================================================================

#ifndef WOML_POINTMETEOROLOGICALSYMBOL_H
#define WOML_POINTMETEOROLOGICALSYMBOL_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include "MeteorologicalSymbol.h"
#include "Point.h"
#include <boost/shared_ptr.hpp>

namespace woml
{
  class FeatureVisitor;

  class PointMeteorologicalSymbol : public Feature
  {
  public:
	PointMeteorologicalSymbol();
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void point(const Point & thePoint);
	void symbol(MeteorologicalSymbol * theSymbol);

	const Point & point() const;
	boost::shared_ptr<MeteorologicalSymbol> symbol() const;

  private:
	Envelope itsBoundedBy;
	Point itsPoint;
	boost::shared_ptr<MeteorologicalSymbol> itsMeteorologicalSymbol;

  }; // class PointMeteorologicalSymbol

} // namespace woml

#endif // WOML_POINTMETEOROLOGICALSYMBOL_H
