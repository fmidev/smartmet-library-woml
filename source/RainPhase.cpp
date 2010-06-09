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

RainPhase parseRainPhase(const std::string & theName)
{
  if(theName == "rain")
	return rain;
  else if(theName == "snow")
	return snow;
  else if(theName == "fog")
	return fog;
  else if(theName == "sleet")
	return sleet;
  else if(theName == "hail")
	return hail;
  else if(theName == "freezing-precipitation")
	return freezing_precipitation;
  else if(theName == "drizzle")
	return drizzle;
  else if(theName == "mixed")
	return mixed;
  else return unknown;
}


} // namespace woml
