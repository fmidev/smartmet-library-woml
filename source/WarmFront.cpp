// ======================================================================
/*!
 * \brief class woml::WarmFront
 */
// ======================================================================

#include "WarmFront.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void WarmFront::visit(FeatureVisitor & visitor) const
{
  visitor.visit(*this);
}

} // namespace woml
