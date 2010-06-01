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

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void ColdFront::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void ColdFront::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}


} // namespace woml
