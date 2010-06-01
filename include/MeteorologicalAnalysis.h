// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_ANALYSIS_H
#define WOML_METEOROLOGICAL_ANALYSIS_H

#include "Feature.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace woml
{
  class MeteorologicalAnalysis
  {
  public:
	MeteorologicalAnalysis();
	void addFeature(Feature * theFeature);
	void validTime(const boost::posix_time::time_period & thePeriod);
	void creationTime(const boost::posix_time::ptime & theTime);
	void latestModificationTime(const boost::posix_time::ptime & theTime);
	void analysisTime(const boost::posix_time::ptime & theTime);


  private:

	boost::ptr_list<Feature> itsFeatureMembers;
	boost::posix_time::time_period itsValidTime;
	boost::posix_time::ptime itsCreationTime;
	boost::posix_time::ptime itsLatestModificationTime;

	// This part is different from WeatherForecast
	boost::posix_time::ptime itsAnalysisTime;

  }; // class MeteorologicalAnalysis
} // namespace woml

#endif // WOML_METEOROLOGICAL_ANALYSIS_H



