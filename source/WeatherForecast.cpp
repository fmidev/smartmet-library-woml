// ======================================================================
/*!
 * \brief woml::WeatherForecast
 */
// ======================================================================

#include "WeatherForecast.h"
#include <boost/foreach.hpp>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

WeatherForecast::WeatherForecast()
  : itsFeatureMembers()
  , itsValidTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time),
				 boost::posix_time::ptime(boost::posix_time::not_a_date_time))
  , itsCreationTime(boost::posix_time::not_a_date_time)
  , itsLatestModificationTime(boost::posix_time::not_a_date_time)
  , itsForecastTime(boost::posix_time::not_a_date_time)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a feature member
 *
 * Ownership is transferrer to this class
 */
// ----------------------------------------------------------------------

void WeatherForecast::addFeature(Feature * theFeature)
{
  itsFeatureMembers.push_back(theFeature);
}


// ----------------------------------------------------------------------
/*!
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void WeatherForecast::validTime(const boost::posix_time::time_period & thePeriod)
{
  itsValidTime = thePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the creation time
 */
// ----------------------------------------------------------------------

void WeatherForecast::creationTime(const boost::posix_time::ptime & theTime)
{
  itsCreationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the latest modification time
 */
// ----------------------------------------------------------------------

void WeatherForecast::latestModificationTime(const boost::posix_time::ptime & theTime)
{
  itsLatestModificationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the analysis time
 */
// ----------------------------------------------------------------------

void WeatherForecast::analysisTime(const boost::posix_time::ptime & theTime)
{
  itsAnalysisTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the forecast time
 */
// ----------------------------------------------------------------------

void WeatherForecast::forecastTime(const boost::posix_time::ptime & theTime)
{
  itsForecastTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add connection point
 */
// ----------------------------------------------------------------------

void WeatherForecast::addConnectionPoint(const std::string & theName,
										 const Point & thePoint)
{
  itsSharedConnectionPoints.insert(std::make_pair(theName,thePoint));
}

// ----------------------------------------------------------------------
/*!
 * \brief Add connection points
 */
// ----------------------------------------------------------------------

void WeatherForecast::addConnectionPoints(const std::map<std::string,Point> & thePoints)
{
  BOOST_FOREACH(const SharedConnectionPoints::value_type & name_point, thePoints)
	{
	  addConnectionPoint(name_point.first, name_point.second);
	}
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the feature members
 */
// ----------------------------------------------------------------------

WeatherForecast::const_iterator
WeatherForecast::begin() const
{
  return itsFeatureMembers.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the feature members
 */
// ----------------------------------------------------------------------

WeatherForecast::const_iterator
WeatherForecast::end() const
{
  return itsFeatureMembers.end();
}


} // namespace woml
