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
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void PointMeteorologicalSymbol::visit(FeatureVisitor & visitor) const
{
  visitor.visit(*this);
}

} // namespace woml
