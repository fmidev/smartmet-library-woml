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
bool Weather::strictParsing = true;

// ----------------------------------------------------------------------
/*!
 * \brief True if analysis has been set
 */
// ----------------------------------------------------------------------

bool Weather::hasAnalysis() const { return !!itsAnalysis; }
// ----------------------------------------------------------------------
/*!
 * \brief True if forecast has been set
 */
// ----------------------------------------------------------------------

bool Weather::hasForecast() const { return !!itsForecast; }
// ----------------------------------------------------------------------
/*!
 * \brief True if WOML was empty
 */
// ----------------------------------------------------------------------

bool Weather::empty() const
{
  return (((!itsAnalysis) || (itsAnalysis->begin() == itsAnalysis->end())) &&
          ((!itsForecast) || (itsForecast->begin() == itsForecast->end())));
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the analysis
 */
// ----------------------------------------------------------------------

const MeteorologicalAnalysis& Weather::analysis() const
{
  if (!hasAnalysis()) throw std::runtime_error("analysis requested when not available");
  return *itsAnalysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the forecast
 */
// ----------------------------------------------------------------------

const WeatherForecast& Weather::forecast() const
{
  if (!hasForecast()) throw std::runtime_error("forecast requested when not available");
  return *itsForecast;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the analysis
 */
// ----------------------------------------------------------------------

void Weather::analysis(std::shared_ptr<MeteorologicalAnalysis> theAnalysis)
{
  itsAnalysis = theAnalysis;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the forecast
 */
// ----------------------------------------------------------------------

void Weather::forecast(std::shared_ptr<WeatherForecast> theForecast)
{
  itsForecast = theForecast;
}

// ----------------------------------------------------------------------
/*!
 * \brief Synchronize feature members
 */
// ----------------------------------------------------------------------

void Weather::synchronize()
{
  hasAnalysis() ? itsAnalysis->synchronize() : itsForecast->synchronize();
}

}  // namespace woml
