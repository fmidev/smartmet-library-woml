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

#include <boost/shared_ptr.hpp>

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

  void analysis(boost::shared_ptr<MeteorologicalAnalysis> theAnalysis);
  void forecast(boost::shared_ptr<WeatherForecast> theForecast);

  void synchronize();

  static void strictMode(bool strict) { strictParsing = strict; }
  static bool strictMode() { return strictParsing; }
 private:
  static bool strictParsing;  // Terminate on broken/unexpected woml input

  boost::shared_ptr<MeteorologicalAnalysis> itsAnalysis;
  boost::shared_ptr<WeatherForecast> itsForecast;

};  // class Woml
}  // namespace Woml

