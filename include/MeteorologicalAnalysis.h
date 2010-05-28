// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_ANALYSIS_H
#define WOML_METEOROLOGICAL_ANALYSIS_H

#include "Feature.h"
#include "GeographicRegion.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <list>

namespace woml
{
  class MeteorologicalAnalysis
  {
  public:
	
  private:

	std::list<FeaturePtr> featureMembers;
	boost::posix_time::time_period validTime;
	boost::posix_time::ptime creationTime;
	boost::posix_time::ptime latestModificationTime;
	boost::posix_time::ptime analysisTime;

  }; // class MeteorologicalAnalysis
} // namespace woml

#endif // WOML_METEOROLOGICAL_ANALYSIS_H



