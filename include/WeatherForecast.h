// ======================================================================
/*!
 * \brief woml::WeatherForecast
 */
// ======================================================================

#ifndef WOML_WEATHER_FORECAST_H
#define WOML_WEATHER_FORECAST_H

#include "Feature.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace woml
{
  class WeatherForecast
  {
  public:
	
  private:

	boost::ptr_list<Feature> itsFeatureMembers;
	boost::posix_time::time_period itsValidTime;
	boost::posix_time::ptime itsCreationTime;
	boost::posix_time::ptime itsLatestModificationTime;

	// This part is different from MeteorologicalAnalysis
	boost::posix_time::ptime itsForecastTime;

  }; // class WeatherForecast
} // namespace woml

#endif // WOML_WEATHERFORECAST_H



