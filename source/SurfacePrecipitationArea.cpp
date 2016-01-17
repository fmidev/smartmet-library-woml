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
    : AbstractSurfaceObject(),
      itsRainPhase(unknown),
      itsRainPhaseName(""),
      itsContinuity(),
      itsShoweriness(),
      itsApproximateRainFall()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); }
// ----------------------------------------------------------------------
/*!
 * \brief Set the rain phase
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::rainPhase(RainPhase thePhase, const std::string& thePhaseName)
{
  itsRainPhase = thePhase;
  itsRainPhaseName = thePhaseName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the rain continuity
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::continuity(boost::optional<double> thePercentage)
{
  itsContinuity = thePercentage;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the rain showeriness
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::showeriness(boost::optional<double> thePercentage)
{
  itsShoweriness = thePercentage;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the approximate rain fall
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::approximateRainFall(
    const boost::optional<NumericalSingleValueMeasure>& theAmount)
{
  itsApproximateRainFall = theAmount;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add an inner precipitation area
 */
// ----------------------------------------------------------------------

void SurfacePrecipitationArea::innerArea(SurfacePrecipitationArea* theArea)
{
  itsInnerArea.push_back(theArea);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get precipitation phase
 */
// ----------------------------------------------------------------------

RainPhase SurfacePrecipitationArea::rainPhase() const { return itsRainPhase; }
// ----------------------------------------------------------------------
/*!
 * \brief Get precipitation phase name
 */
// ----------------------------------------------------------------------

const std::string& SurfacePrecipitationArea::rainPhaseName() const { return itsRainPhaseName; }
}  // namespace woml
