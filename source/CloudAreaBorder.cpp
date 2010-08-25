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

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void CloudAreaBorder::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void CloudAreaBorder::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the start point
 */
// ----------------------------------------------------------------------

void CloudAreaBorder::connectStartPoint(const std::string & theName)
{
  itsStartPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the end point
 */
// ----------------------------------------------------------------------

void CloudAreaBorder::connectEndPoint(const std::string & theName)
{
  itsEndPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control curve
 */
// ----------------------------------------------------------------------

const CubicSplineCurve & CloudAreaBorder::controlCurve() const
{
  return itsControlCurve;
}


} // namespace woml
