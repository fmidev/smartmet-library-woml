// ======================================================================
/*!
 * \brief class woml::StormType
 */
// ======================================================================

#include "StormType.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

StormType::StormType() : AbstractPointObject() {}
// ----------------------------------------------------------------------
/*!
 * \brief Set the rainphase
 */
// ----------------------------------------------------------------------

void StormType::rainPhase(RainPhase theRainPhase) { itsRainPhase = theRainPhase; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the rainphase
 */
// ----------------------------------------------------------------------

RainPhase StormType::rainPhase() const { return itsRainPhase; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the approximate rainfall
 */
// ----------------------------------------------------------------------

void StormType::approximateRainFall(
    const std::optional<NumericalSingleValueMeasure>& theApproximateRainFall)
{
  itsApproximateRainFall = theApproximateRainFall;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the approximate rainfall
 */
// ----------------------------------------------------------------------

const std::optional<NumericalSingleValueMeasure>& StormType::approximateRainFall() const
{
  return itsApproximateRainFall;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set thunderstorm flag
 */
// ----------------------------------------------------------------------

void StormType::isThunderStorm(const std::optional<bool>& theIsThunderStorm)
{
  itsIsThunderStorm = theIsThunderStorm;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the max wind speed
 */
// ----------------------------------------------------------------------

const std::optional<bool>& StormType::isThunderStorm() const { return itsIsThunderStorm; }
}  // namespace woml
