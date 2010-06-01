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
  : itsBoundedBy()
  , itsPoint(0,0)
  , itsMeteorologicalSymbol()
{ }


// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the coordinate for the symbol
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::point(const Point & thePoint)
{
  itsPoint = thePoint;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the symbol
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::symbol(MeteorologicalSymbol * theSymbol)
{
  itsMeteorologicalSymbol.reset(theSymbol);
}

} // namespace woml
