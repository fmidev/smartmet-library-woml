// ======================================================================
/*!
 * \brief class woml::ColdFront
 */
// ======================================================================

#include "ColdFront.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void ColdFront::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

} // namespace woml
