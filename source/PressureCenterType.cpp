// ======================================================================
/*!
 * \brief class woml::PressureCenterType
 */
// ======================================================================

#include "PressureCenterType.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

PressureCenterType::PressureCenterType() : AbstractPointObject() {}
// ----------------------------------------------------------------------
/*!
 * \brief Set the tendency
 */
// ----------------------------------------------------------------------

void PressureCenterType::tendency(const std::string& theTendency) { itsTendency = theTendency; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the tendency
*/
// ----------------------------------------------------------------------

const std::string& PressureCenterType::tendency() const { return itsTendency; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the max wind speed
 */
// ----------------------------------------------------------------------

void PressureCenterType::maxwindspeed(
    const boost::optional<NumericalSingleValueMeasure>& theMaxWindSpeed)
{
  itsMaxWindSpeed = theMaxWindSpeed;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the max wind speed
*/
// ----------------------------------------------------------------------

const boost::optional<NumericalSingleValueMeasure>& PressureCenterType::maxwindspeed() const
{
  return itsMaxWindSpeed;
}

}  // namespace woml
