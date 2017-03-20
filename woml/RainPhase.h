// ======================================================================
/*!
 * \brief woml::RainPhase
 */
// ======================================================================

#pragma once

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

RainPhase parseRainPhase(const std::string& theName);

}  // namespace woml

