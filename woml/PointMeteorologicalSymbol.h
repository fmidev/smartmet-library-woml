// ======================================================================
/*!
 * \brief woml::PointMeteorologicalSymbol
 */
// ======================================================================

#pragma once

#include "AbstractPointObject.h"
#include "MeteorologicalSymbol.h"

namespace woml
{
class FeatureVisitor;

class PointMeteorologicalSymbol : public AbstractPointObject
{
 public:
  PointMeteorologicalSymbol();
  void visit(FeatureVisitor& theVisitor) const override;
  void symbol(const MeteorologicalSymbol& theSymbol);
  const MeteorologicalSymbol& symbol() const;

 private:
  MeteorologicalSymbol itsMeteorologicalSymbol;

};  // class PointMeteorologicalSymbol

}  // namespace woml
