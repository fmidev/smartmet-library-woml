// ======================================================================
/*!
 * \brief class woml::PointMeteorologicalSymbol
 */
// ======================================================================

#include "PointMeteorologicalSymbol.h"
#include "FeatureVisitor.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

PointMeteorologicalSymbol::PointMeteorologicalSymbol()
    : AbstractPointObject(), itsMeteorologicalSymbol()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); }
// ----------------------------------------------------------------------
/*!
 * \brief Set the symbol
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::symbol(const MeteorologicalSymbol& theSymbol)
{
  itsMeteorologicalSymbol = theSymbol;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the symbol
 */
// ----------------------------------------------------------------------

const MeteorologicalSymbol& PointMeteorologicalSymbol::symbol() const
{
  return itsMeteorologicalSymbol;
}

}  // namespace woml
