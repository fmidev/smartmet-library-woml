// ======================================================================
/*!
 * \brief class woml::UpperTrough
 */
// ======================================================================

#include "UpperTrough.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void UpperTrough::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void UpperTrough::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void UpperTrough::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the start point
 */
// ----------------------------------------------------------------------

void UpperTrough::connectStartPoint(const std::string & theName)
{
  itsStartPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the end point
 */
// ----------------------------------------------------------------------

void UpperTrough::connectEndPoint(const std::string & theName)
{
  itsEndPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control curve
 */
// ----------------------------------------------------------------------

const CubicSplineCurve & UpperTrough::controlCurve() const
{
  return itsControlCurve;
}


} // namespace woml
