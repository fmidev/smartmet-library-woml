// ======================================================================
/*!
 * \brief woml::WeatherForecast
 */
// ======================================================================

#include "WeatherForecast.h"

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

} // namespace woml
