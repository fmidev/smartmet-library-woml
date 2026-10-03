// ======================================================================
/*!
 * \brief Woml container, not from metobj schema
 *
 * MeteorologicalAnalysis and MeteorologicalForecast differ in one
 * member variable. Since we want to match class names, we need
 * a generic container for any Meteorological* object.
 */
// ======================================================================

#pragma once

#include <memory>

namespace woml
{
enum documentType
{
  conceptualmodelanalysis,
  conceptualmodelforecast,
  aerodromeforecast
};

class MeteorologicalAnalysis;
class WeatherForecast;

class Weather
{
 public:
  bool hasAnalysis() const;
  bool hasForecast() const;
  bool empty() const;

  const MeteorologicalAnalysis& analysis() const;
  const WeatherForecast& forecast() const;

  void analysis(std::shared_ptr<MeteorologicalAnalysis> theAnalysis);
  void forecast(std::shared_ptr<WeatherForecast> theForecast);

  void synchronize();

  static void strictMode(bool strict) { strictParsing = strict; }
  static bool strictMode() { return strictParsing; }

 private:
  // Terminate on broken/unexpected woml input. Set by parse() for the duration of
  // the call, per thread so that concurrent parses do not affect each other.
  static thread_local bool strictParsing;

  std::shared_ptr<MeteorologicalAnalysis> itsAnalysis;
  std::shared_ptr<WeatherForecast> itsForecast;

};  // class Woml
}  // namespace woml
