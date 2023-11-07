// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 *
 * 		  Note: Should inherit WeatherForecast and MeteorologicalAnalysis
 *				from new parent; all members and behaviour are equal!
 */
// ======================================================================

#include "MeteorologicalAnalysis.h"
#include <boost/foreach.hpp>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::MeteorologicalAnalysis()
    : MeteorologicalObject(),
      itsFeatureMembers(),
      itsValidTime(Fmi::DateTime(boost::posix_time::not_a_date_time),
                   Fmi::DateTime(boost::posix_time::not_a_date_time)),
      itsCreator(),
      itsCreationTime(boost::posix_time::not_a_date_time),
      itsLatestModificationTime(boost::posix_time::not_a_date_time),
      itsAnalysisTime(boost::posix_time::not_a_date_time),
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

void MeteorologicalAnalysis::addFeature(Feature *theFeature, bool timeSynchronized)
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

void MeteorologicalAnalysis::envelope(const boost::optional<Envelope> &theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::validTime(const boost::posix_time::time_period &thePeriod)
{
  itsValidTime = thePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the valid time
 */
// ----------------------------------------------------------------------

const boost::posix_time::time_period &MeteorologicalAnalysis::validTime() const
{
  return itsValidTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the creator
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::creator(const std::string &theCreator) { itsCreator = theCreator; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the creator
 */
// ----------------------------------------------------------------------

const std::string &MeteorologicalAnalysis::creator() const { return itsCreator; }
// ----------------------------------------------------------------------
/*!
 * \brief Set the creation time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::creationTime(const Fmi::DateTime &theTime)
{
  itsCreationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the creation time
 */
// ----------------------------------------------------------------------

const Fmi::DateTime &MeteorologicalAnalysis::creationTime() const
{
  return itsCreationTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the latest modification time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::latestModificationTime(
    const boost::optional<Fmi::DateTime> &theTime)
{
  itsLatestModificationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the latest modification time
 */
// ----------------------------------------------------------------------

const boost::optional<Fmi::DateTime> &MeteorologicalAnalysis::latestModificationTime()
    const
{
  return itsLatestModificationTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the analysis time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::analysisTime(const Fmi::DateTime &theTime)
{
  itsAnalysisTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the analysis time
 */
// ----------------------------------------------------------------------

const Fmi::DateTime &MeteorologicalAnalysis::analysisTime() const
{
  return itsAnalysisTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a target region
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::addTargetRegion(const TargetRegion &theTargetRegion)
{
  if (theTargetRegion.RegionIds_begin() != theTargetRegion.RegionIds_end())
    itsTargetRegions.push_back(theTargetRegion);
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the target regions
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::TargetRegions_const_iterator MeteorologicalAnalysis::TargetRegions_begin()
    const
{
  return itsTargetRegions.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the target regions
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::TargetRegions_const_iterator MeteorologicalAnalysis::TargetRegions_end()
    const
{
  return itsTargetRegions.end();
}

// ----------------------------------------------------------------------
/*!
 * \brief Add short info
 */
// ----------------------------------------------------------------------

// void MeteorologicalAnalysis::addShortInfo(const std::string & theLanguage,const std::string &
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

void MeteorologicalAnalysis::addShortInfos(const MeteorologicalAnalysisInfo &theShortInfos)
{
  // shortInfos is stored as a feature

  //  BOOST_FOREACH(const MeteorologicalAnalysis::value_type & shortInfo, theShortInfos)
  //	{
  //	  addShortInfo(shortInfo.first, shortInfo.second);
  //	}

  addFeature(new InfoText("shortInfo", theShortInfos));
}

// ----------------------------------------------------------------------
/*!
 * \brief Add long info
 */
// ----------------------------------------------------------------------

// void MeteorologicalAnalysis::addLongInfo(const std::string & theLanguage,const std::string &
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

void MeteorologicalAnalysis::addLongInfos(const MeteorologicalAnalysisInfo &theLongInfos)
{
  // longInfos is stored as a feature

  //  BOOST_FOREACH(const MeteorologicalAnalysis::value_type & longInfo, theLongInfos)
  //	{
  //	  addLongInfo(longInfo.first, longInfo.second);
  //	}

  // Note: Feature must be added, even through it is empty; otherwise a text area class definition
  // will be invalid (rect without width) in output document

  addFeature(new InfoText("longInfo", theLongInfos));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the feature members
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::const_iterator MeteorologicalAnalysis::begin() const
{
  return itsFeatureMembers.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the feature members
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::const_iterator MeteorologicalAnalysis::end() const
{
  return itsFeatureMembers.end();
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the data source
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::dataSource(const DataSource &theSource) { itsDataSource = theSource; }
// ----------------------------------------------------------------------
/*!
 * \brief Get the data source
 */
// ----------------------------------------------------------------------

const DataSource &MeteorologicalAnalysis::dataSource() const { return itsDataSource; }
}  // namespace woml
