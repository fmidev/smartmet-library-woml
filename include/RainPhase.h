// ======================================================================
/*!
 * \brief woml::RainPhase
 */
// ======================================================================

#ifndef WOML_RAINPHASE_H
#define WOML_RAINPHASE_H

#include <string>

namespace woml
{
  enum RainPhase
	{
	  rain,
	  snow,
	  fog,
	  sleet,
	  hail,
	  freezing_precipitation,
	  drizzle,
	  mixed,
	  unknown
	};

  RainPhase parseRainPhase(const std::string & theName);

} // namespace woml

#endif // WOML_RAINPHASE_H
