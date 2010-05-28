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
#include <boost/scoped_ptr.hpp>
#include <map>
#include <string>

namespace woml
{
  class FeatureVisitor;

  class PointMeteorologicalSymbol : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	Point point;
	boost::scoped_ptr<MeteorologicalSymbol> itsMeteorologicalSymbol;

  }; // class PointMeteorologicalSymbol

} // namespace woml

#endif // WOML_POINTMETEOROLOGICALSYMBOL_H
