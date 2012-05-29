// ======================================================================
/*!
 * \brief class woml::AbstractLineObject
 */
// ======================================================================

#include "AbstractLineObject.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Set the orientation
 */
// ----------------------------------------------------------------------

void AbstractLineObject::orientation(const boost::optional<std::string> & theOrientation)
{
  itsOrientation = (theOrientation ? *theOrientation : "+");
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the orientation
 */
// ----------------------------------------------------------------------

const std::string & AbstractLineObject::orientation() const
{
  return *itsOrientation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void AbstractLineObject::envelope(const boost::optional<Envelope> & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void AbstractLineObject::controlCurve(const CubicSplineCurve & theControlCurve)
{
  itsControlCurve = theControlCurve;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the start point
 */
// ----------------------------------------------------------------------

void AbstractLineObject::connectStartPoint(const std::string & theName)
{
  itsStartPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Connect the end point
 */
// ----------------------------------------------------------------------

void AbstractLineObject::connectEndPoint(const std::string & theName)
{
  itsEndPointConnectsTo = theName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control curve
 */
// ----------------------------------------------------------------------

const CubicSplineCurve & AbstractLineObject::controlCurve() const
{
  return itsControlCurve;
}

} // namespace woml
