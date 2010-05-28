// ======================================================================
/*!
 * \brief class woml::CloudAreaBorder
 */
// ======================================================================

#include "CloudAreaBorder.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void CloudAreaBorder::visit(FeatureVisitor & visitor) const
{
  visitor.visit(*this);
}

} // namespace woml
