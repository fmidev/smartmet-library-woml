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

StormType::StormType()
  : AbstractPointObject()
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Set the rainphase
 */
// ----------------------------------------------------------------------

void StormType::rainPhase(RainPhase theRainPhase)
{
  itsRainPhase = theRainPhase;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the rainphase
*/
// ----------------------------------------------------------------------

RainPhase StormType::rainPhase() const
{
  return itsRainPhase;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the approximate rainfall
 */
// ----------------------------------------------------------------------

void StormType::approximateRainFall(const boost::optional<NumericalSingleValueMeasure> & theApproximateRainFall)
{
  itsApproximateRainFall = theApproximateRainFall;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the approximate rainfall
*/
// ----------------------------------------------------------------------

const boost::optional<NumericalSingleValueMeasure> & StormType::approximateRainFall() const
{
  return itsApproximateRainFall;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set thunderstorm flag
 */
// ----------------------------------------------------------------------

void StormType::isThunderStorm(const boost::optional<bool> & theIsThunderStorm)
{
  itsIsThunderStorm = theIsThunderStorm;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the max wind speed
*/
// ----------------------------------------------------------------------

const boost::optional<bool> & StormType::isThunderStorm() const
{
  return itsIsThunderStorm;
}

} // namespace woml
