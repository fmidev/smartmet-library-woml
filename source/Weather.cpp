// ======================================================================
/*!
 * \brief Weather container, not from metobj schema
 */
// ======================================================================

#include "Weather.h"
#include "MeteorologicalAnalysis.h"
#include "WeatherForecast.h"
#include <stdexcept>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief True if analysis has been set
 */
// ----------------------------------------------------------------------

bool Weather::hasAnalysis() const
{
  return !!itsAnalysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief True if forecast has been set
 */
// ----------------------------------------------------------------------

bool Weather::hasForecast() const
{
  return !!itsForecast;
}

// ----------------------------------------------------------------------
/*!
 * \brief True if WOML was empty
 */
// ----------------------------------------------------------------------

bool Weather::empty() const
{
  return (!itsAnalysis & !itsForecast);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the analysis
 */
// ----------------------------------------------------------------------

const MeteorologicalAnalysis & Weather::analysis() const
{
  if(!hasAnalysis())
	throw std::runtime_error("analysis requested when not available");
  return *itsAnalysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the forecast
 */
// ----------------------------------------------------------------------

const WeatherForecast & Weather::forecast() const
{
  if(!hasForecast())
	throw std::runtime_error("forecast requested when not available");
  return *itsForecast;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the analysis
 */
// ----------------------------------------------------------------------

void Weather::analysis(boost::shared_ptr<MeteorologicalAnalysis> theAnalysis)
{
  itsAnalysis = theAnalysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the forecast
 */
// ----------------------------------------------------------------------

void Weather::forecast(boost::shared_ptr<WeatherForecast> theForecast)
{
  itsForecast = theForecast;
}

} // namespace woml