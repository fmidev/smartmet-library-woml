// ======================================================================
/*!
 * \brief class woml::OccludedFront
 */
// ======================================================================

#include "OccludedFront.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void OccludedFront::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the stationary
 */
// ----------------------------------------------------------------------

void OccludedFront::stationary(bool theStationary)
{
  itsStationary = theStationary;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the stationary
 */
// ----------------------------------------------------------------------

bool OccludedFront::stationary() const
{
  return itsStationary;
}

} // namespace woml
