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
#include <boost/unique_ptr.hpp>
#include <map>
#include <string>

namespace woml
{
  class PointMeteorologicalSymbol : public Feature;
  {
  public:
  private:
	Envelope boundedBy;
	std::map<std::string,std::string> shortInfo;
	std::map<std::string,std::string> longInfo;
	Point point;
	boost::unique_ptr<MeteorologicalSymbol> meteorologicalSymbol;

  }; // class PointMeteorologicalSymbol

} // namespace woml

#endif // WOML_POINTMETEOROLOGICALSYMBOL_H
