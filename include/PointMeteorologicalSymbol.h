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
	virtual void visit(FeatureVisitor & visitor) const;
  private:
	Envelope boundedBy;
	std::map<std::string,std::string> shortInfo;
	std::map<std::string,std::string> longInfo;
	Point point;
	boost::scoped_ptr<MeteorologicalSymbol> meteorologicalSymbol;

  }; // class PointMeteorologicalSymbol

} // namespace woml

#endif // WOML_POINTMETEOROLOGICALSYMBOL_H
