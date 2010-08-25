// ======================================================================
/*!
 * \brief class woml::SurfacePrecipitationArea
 */
// ======================================================================

#include "SurfacePrecipitationArea.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

SurfacePrecipitationArea::SurfacePrecipitationArea()
  : itsBoundedBy()
  , itsControlSurface()
  , itsRainPhase(unknown)
  , itsContinuity(0.0)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the control surface
 */
// ----------------------------------------------------------------------

const CubicSplineSurface & SurfacePrecipitationArea::controlSurface() const
{
  return itsControlSurface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the control curve
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::controlSurface(const CubicSplineSurface & theControlSurface)
{
  itsControlSurface = theControlSurface;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the rain phase
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::rainPhase(RainPhase thePhase)
{
  itsRainPhase = thePhase;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the rain continuity
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::continuity(double thePercentage)
{
  itsContinuity = thePercentage;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the rain showeriness
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::showeriness(double thePercentage)
{
  itsShoweriness = thePercentage;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the approximate rain fall
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::approximateRainFall(double theAmount)
{
  itsApproximateRainFall = theAmount;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add an inner precipitation area
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::innerArea(SurfacePrecipitationArea * theArea)
{
  itsInnerArea.push_back(theArea);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get precipitation phase
 */
// ----------------------------------------------------------------------

RainPhase SurfacePrecipitationArea::rainPhase() const
{
  return itsRainPhase;
}


} // namespace woml
