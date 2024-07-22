// ======================================================================
/*!
 * \brief woml::WeatherForecast
 *
 * 		  Note: Should inherit WeatherForecast and MeteorologicalAnalysis
 *				from new parent; all members and behaviour are equal!
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
    : MeteorologicalObject(),
      itsFeatureMembers(),
      itsValidTime(Fmi::DateTime(Fmi::DateTime::NOT_A_DATE_TIME),
                   Fmi::DateTime(Fmi::DateTime::NOT_A_DATE_TIME)),
      itsCreator(),
      itsCreationTime(Fmi::DateTime::NOT_A_DATE_TIME),
      itsLatestModificationTime(Fmi::DateTime::NOT_A_DATE_TIME),
      itsForecastTime(Fmi::DateTime::NOT_A_DATE_TIME),
      itsTargetRegions()
//, itsShortInfos()
//, itsLongInfos()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a feature member
 *
 * Ownership is transferrer to this class
 */
// ----------------------------------------------------------------------

void WeatherForecast::addFeature(Feature *theFeature, bool timeSynchronized)
{
  itsFeatureMembers.push_back(theFeature);

  if (timeSynchronized)
    MeteorologicalObject::addTimeSynchronizedFeature(
        dynamic_cast<woml::ParameterTimeSeriesPoint *>(theFeature));
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void WeatherForecast::envelope(const std::optional<Envelope> &theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void WeatherForecast::validTime(const Fmi::TimePeriod &thePeriod)
{
  itsValidTime = thePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the valid time
 */
// ----------------------------------------------------------------------

const Fmi::TimePeriod &WeatherForecast::validTime() const { return itsValidTime; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the creator
 */
// ----------------------------------------------------------------------

void WeatherForecast::creator(const std::string &theCreator) { itsCreator = theCreator; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the creator
 */
// ----------------------------------------------------------------------

const std::string &WeatherForecast::creator() const { return itsCreator; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the creation time
 */
// ----------------------------------------------------------------------

void WeatherForecast::creationTime(const Fmi::DateTime &theTime)
{
  itsCreationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the creation time
 */
// ----------------------------------------------------------------------

const Fmi::DateTime &WeatherForecast::creationTime() const { return itsCreationTime; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the latest modification time
 */
// ----------------------------------------------------------------------

void WeatherForecast::latestModificationTime(
    const std::optional<Fmi::DateTime> &theTime)
{
  itsLatestModificationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the latest modification time
 */
// ----------------------------------------------------------------------

const std::optional<Fmi::DateTime> &WeatherForecast::latestModificationTime() const
{
  return itsLatestModificationTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the forecast time
 */
// ----------------------------------------------------------------------

void WeatherForecast::forecastTime(const Fmi::DateTime &theTime)
{
  itsForecastTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the forecast time
 */
// ----------------------------------------------------------------------

const Fmi::DateTime &WeatherForecast::forecastTime() const { return itsForecastTime; }
// ----------------------------------------------------------------------
/*!
 * \brief Add a target region
 */
// ----------------------------------------------------------------------

void WeatherForecast::addTargetRegion(const TargetRegion &theTargetRegion)
{
  if (theTargetRegion.RegionIds_begin() != theTargetRegion.RegionIds_end())
    itsTargetRegions.push_back(theTargetRegion);
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the target regions
 */
// ----------------------------------------------------------------------

WeatherForecast::TargetRegions_const_iterator WeatherForecast::TargetRegions_begin() const
{
  return itsTargetRegions.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the target regions
 */
// ----------------------------------------------------------------------

WeatherForecast::TargetRegions_const_iterator WeatherForecast::TargetRegions_end() const
{
  return itsTargetRegions.end();
}

// ----------------------------------------------------------------------
/*!
 * \brief Add short info
 */
// ----------------------------------------------------------------------

// void WeatherForecast::addShortInfo(const std::string & theLanguage,const std::string &
// theShortInfo)
//{
//	if ((theLanguage.length() > 0) && (theShortInfo.length() > 0))
//		itsShortInfos.insert(std::make_pair(theLanguage,theShortInfo));
//}

// ----------------------------------------------------------------------
/*!
 * \brief Add short infos
 */
// ----------------------------------------------------------------------

void WeatherForecast::addShortInfos(const WeatherForecastInfo &theShortInfos)
{
  // shortInfos is stored as a feature

  //  for(const WeatherForecastInfo::value_type & shortInfo :  theShortInfos)
  //	{
  //	  addShortInfo(shortInfo.first, shortInfo.second);
  //	}

  if (theShortInfos.size() > 0) addFeature(new InfoText("shortInfo", theShortInfos));
}

// ----------------------------------------------------------------------
/*!
 * \brief Add long info
 */
// ----------------------------------------------------------------------

// void WeatherForecast::addLongInfo(const std::string & theLanguage,const std::string &
// theLongInfo)
//{
//	if ((theLanguage.length() > 0) && (theLongInfo.length() > 0))
//		itsLongInfos.insert(std::make_pair(theLanguage,theLongInfo));
//}

// ----------------------------------------------------------------------
/*!
 * \brief Add long info
 */
// ----------------------------------------------------------------------

void WeatherForecast::addLongInfos(const WeatherForecastInfo &theLongInfos)
{
  // longInfos is stored as a feature

  //  for(const WeatherForecastInfo::value_type & longInfo : theLongInfos)
  //	{
  //	  addLongInfo(longInfo.first, longInfo.second);
  //	}

  if (theLongInfos.size() > 0) addFeature(new InfoText("longInfo", theLongInfos));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the feature members
 */
// ----------------------------------------------------------------------

WeatherForecast::const_iterator WeatherForecast::begin() const { return itsFeatureMembers.begin(); }
// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the feature members
 */
// ----------------------------------------------------------------------

WeatherForecast::const_iterator WeatherForecast::end() const { return itsFeatureMembers.end(); }
// ----------------------------------------------------------------------
/*!
 * \brief Set the data source
 */
// ----------------------------------------------------------------------

void WeatherForecast::dataSource(const DataSource &theSource) { itsDataSource = theSource; }
// ----------------------------------------------------------------------
/*!
 * \brief Get the data source
 */
// ----------------------------------------------------------------------

const DataSource &WeatherForecast::dataSource() const { return itsDataSource; }
}  // namespace woml
