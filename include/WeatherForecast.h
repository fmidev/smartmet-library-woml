// ======================================================================
/*!
 * \brief woml::WeatherForecast
 */
// ======================================================================

#ifndef WOML_WEATHER_FORECAST_H
#define WOML_WEATHER_FORECAST_H

#include "DataSource.h"
#include "Envelope.h"
#include "Feature.h"
#include "Point.h"
#include "TargetRegion.h"
#include "InfoText.h"
#include "MeteorologicalObject.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>

typedef std::multimap<std::string,std::string> WeatherForecastInfo;

namespace woml
{
  class WeatherForecast : public MeteorologicalObject
  {
  public:
	WeatherForecast();
	void addFeature(Feature * theFeature,bool timeSynchronized = false);
	void envelope(const boost::optional<Envelope> & theEnvelope);
	void validTime(const boost::posix_time::time_period & thePeriod);
	const boost::posix_time::time_period & validTime() const;
	void creator(const std::string & theCreator);
	void creationTime(const boost::posix_time::ptime & theTime);
	const boost::posix_time::ptime & creationTime() const;
	void latestModificationTime(const boost::optional<boost::posix_time::ptime> & theTime);
	const boost::optional<boost::posix_time::ptime> & latestModificationTime() const;
	void forecastTime(const boost::posix_time::ptime & theTime);
	const boost::posix_time::ptime & forecastTime() const;
//	void addShortInfo(const std::string & theLanguage,const std::string & theShortInfo);
	void addShortInfos(const WeatherForecastInfo & theShortInfos);
//	void addLongInfo(const std::string & theLanguage,const std::string & theLongInfo);
	void addLongInfos(const WeatherForecastInfo & theLongInfos);

	typedef std::list<TargetRegion> TargetRegionList;
	void addTargetRegion(const TargetRegion & theTargetRegion);
	typedef TargetRegionList::const_iterator TargetRegions_const_iterator;
	TargetRegions_const_iterator TargetRegions_begin() const;
	TargetRegions_const_iterator TargetRegions_end() const;

	void dataSource(const DataSource & theSource);
	const DataSource & dataSource() const;

	typedef boost::ptr_list<Feature>::const_iterator const_iterator;
	const_iterator begin() const;
	const_iterator end() const;
	
  private:

	boost::ptr_list<Feature> itsFeatureMembers;
	boost::optional<Envelope> itsBoundedBy;
	boost::posix_time::time_period itsValidTime;
	std::string itsCreator;
	boost::posix_time::ptime itsCreationTime;
	boost::optional<boost::posix_time::ptime> itsLatestModificationTime;
	boost::posix_time::ptime itsForecastTime;
	TargetRegionList itsTargetRegions;
//	WeatherForecastInfo itsShortInfos;
//	WeatherForecastInfo itsLongInfos;

	DataSource itsDataSource;

  }; // class WeatherForecast
} // namespace woml

#endif // WOML_WEATHERFORECAST_H



