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

void WarmFront::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

} // namespace woml
