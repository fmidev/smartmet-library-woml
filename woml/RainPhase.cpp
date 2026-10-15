// ======================================================================
/*!
 * \brief woml::RainPhase
 */
// ======================================================================

#include "RainPhase.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Convert rain phase name to enum
 */
// ----------------------------------------------------------------------

RainPhase parseRainPhase(const std::string& theName)
{
  if (theName == "rain")
    return rain;
  if (theName == "snow")
    return snow;
  if (theName == "fog")
    return fog;
  if (theName == "sleet")
    return sleet;
  else if (theName == "hail")
    return hail;
  else if (theName == "freezing-precipitation")
    return freezing_precipitation;
  else if (theName == "drizzle")
    return drizzle;
  else if (theName == "mixed")
    return mixed;
  else
    return unknown;
}

}  // namespace woml
