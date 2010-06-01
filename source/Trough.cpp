// ======================================================================
/*!
 * \brief class woml::Trough
 */
// ======================================================================

#include "Trough.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void Trough::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void Trough::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void Trough::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the start point
 */
// ----------------------------------------------------------------------

void Trough::connectStartPoint(const std::string & theName)
{
  itsStartPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the end point
 */
// ----------------------------------------------------------------------

void Trough::connectEndPoint(const std::string & theName)
{
  itsEndPointConnectsTo = theName;
}


} // namespace woml
