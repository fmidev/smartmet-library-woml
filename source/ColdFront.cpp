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

void ColdFront::visit(FeatureVisitor & visitor) const
{
  visitor.visit(*this);
}

} // namespace woml
