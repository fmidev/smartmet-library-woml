// ======================================================================
/*!
 * \brief Woml container, not from metobj schema
 *
 * MeteorologicalAnalysis and MeteorologicalForecast differ in one
 * member variable. Since we want to match class names, we need
 * a generic container for any Meteorological* object.
 */
// ======================================================================

#ifndef WOML_WEATHER_H
#define WOML_WEATHER_H

#include <boost/shared_ptr.hpp>

namespace woml
{
  class MeteorologicalAnalysis;
  class WeatherForecast;

  class Weather
  {
  public:
	bool hasAnalysis() const;
	bool hasForecast() const;
	bool empty() const;

	const MeteorologicalAnalysis & analysis() const;
	const WeatherForecast & forecast() const;

	void analysis(boost::shared_ptr<MeteorologicalAnalysis> theAnalysis);
	void forecast(boost::shared_ptr<WeatherForecast> theForecast);

  private:

	boost::shared_ptr<MeteorologicalAnalysis> itsAnalysis;
	boost::shared_ptr<WeatherForecast> itsForecast;

  }; // class Woml
} // namespace Woml

#endif // WOML_WEATHER_H