// ======================================================================
/*!
 * \brief woml::PointMeteorologicalSymbol
 */
// ======================================================================

#ifndef WOML_POINTMETEOROLOGICALSYMBOL_H
#define WOML_POINTMETEOROLOGICALSYMBOL_H

#include "AbstractPointObject.h"
#include "MeteorologicalSymbol.h"

namespace woml
{
class FeatureVisitor;

class PointMeteorologicalSymbol : public AbstractPointObject
{
 public:
  PointMeteorologicalSymbol();
  virtual void visit(FeatureVisitor& theVisitor) const;
  void symbol(const MeteorologicalSymbol& theSymbol);
  const MeteorologicalSymbol& symbol() const;

 private:
  MeteorologicalSymbol itsMeteorologicalSymbol;

};  // class PointMeteorologicalSymbol

}  // namespace woml

#endif  // WOML_POINTMETEOROLOGICALSYMBOL_H
