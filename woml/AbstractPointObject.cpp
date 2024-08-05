// ======================================================================
/*!
 * \brief class woml::AbstractPointObject
 */
// ======================================================================

#include "AbstractPointObject.h"
#include "FeatureVisitor.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void AbstractPointObject::envelope(const std::optional<Envelope>& theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the point
 */
// ----------------------------------------------------------------------

void AbstractPointObject::point(const std::optional<Point>& thePoint) { itsPoint = thePoint; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the point
 */
// ----------------------------------------------------------------------

const std::optional<Point>& AbstractPointObject::point() const { return itsPoint; }
}  // namespace woml
