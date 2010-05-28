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

void CloudAreaBorder::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

} // namespace woml
