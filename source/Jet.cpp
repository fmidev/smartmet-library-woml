// ======================================================================
/*!
 * \brief class woml::Jet
 */
// ======================================================================

#include "Jet.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void Jet::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void Jet::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void Jet::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the start point
 */
// ----------------------------------------------------------------------

void Jet::connectStartPoint(const std::string & theName)
{
  itsStartPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the end point
 */
// ----------------------------------------------------------------------

void Jet::connectEndPoint(const std::string & theName)
{
  itsEndPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control curve
 */
// ----------------------------------------------------------------------

const CubicSplineCurve & Jet::controlCurve() const
{
  return itsControlCurve;
}


} // namespace woml
