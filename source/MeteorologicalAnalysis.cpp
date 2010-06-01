// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 */
// ======================================================================

#include "MeteorologicalAnalysis.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

MeteorologicalAnalysis::MeteorologicalAnalysis()
  : itsFeatureMembers()
  , itsValidTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time),
				 boost::posix_time::ptime(boost::posix_time::not_a_date_time))
  , itsCreationTime(boost::posix_time::not_a_date_time)
  , itsLatestModificationTime(boost::posix_time::not_a_date_time)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a feature member
 *
 * Ownership is transferrer to this class
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::addFeature(Feature * theFeature)
{
  itsFeatureMembers.push_back(theFeature);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::validTime(const boost::posix_time::time_period & thePeriod)
{
  itsValidTime = thePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the creation time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::creationTime(const boost::posix_time::ptime & theTime)
{
  itsCreationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the latest modification time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::latestModificationTime(const boost::posix_time::ptime & theTime)
{
  itsLatestModificationTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the analysis time
 */
// ----------------------------------------------------------------------

void MeteorologicalAnalysis::analysisTime(const boost::posix_time::ptime & theTime)
{
  itsAnalysisTime = theTime;
}


} // namespace woml
