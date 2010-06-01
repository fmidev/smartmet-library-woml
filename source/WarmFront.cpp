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

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void WarmFront::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void WarmFront::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}


} // namespace woml
