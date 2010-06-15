// ======================================================================
/*!
 * \brief woml::WeatherForecast
 */
// ======================================================================

#ifndef WOML_WEATHER_FORECAST_H
#define WOML_WEATHER_FORECAST_H

#include "Feature.h"
#include "Point.h"
#include "SharedConnectionPoints.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <map>
#include <string>

namespace woml
{
  class WeatherForecast
  {
  public:
	WeatherForecast();
	void addFeature(Feature * theFeature);
	void addConnectionPoint(const std::string & theName, const Point & thePoint);
	void addConnectionPoints(const std::map<std::string,Point> & thePoints);
	void validTime(const boost::posix_time::time_period & thePeriod);
	void creationTime(const boost::posix_time::ptime & theTime);
	void latestModificationTime(const boost::posix_time::ptime & theTime);
	void analysisTime(const boost::posix_time::ptime & theTime);
	void forecastTime(const boost::posix_time::ptime & theTime);

	typedef boost::ptr_list<Feature>::const_iterator const_iterator;
	const_iterator begin() const;
	const_iterator end() const;
	
  private:

	boost::ptr_list<Feature> itsFeatureMembers;
	boost::posix_time::time_period itsValidTime;
	boost::posix_time::ptime itsCreationTime;
	boost::posix_time::ptime itsLatestModificationTime;
	SharedConnectionPoints itsSharedConnectionPoints;
	boost::posix_time::ptime itsAnalysisTime;

	// This part is different from MeteorologicalAnalysis
	boost::posix_time::ptime itsForecastTime;

  }; // class WeatherForecast
} // namespace woml

#endif // WOML_WEATHERFORECAST_H



