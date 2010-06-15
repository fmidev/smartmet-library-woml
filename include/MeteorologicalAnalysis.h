// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_ANALYSIS_H
#define WOML_METEOROLOGICAL_ANALYSIS_H

#include "Feature.h"
#include "Point.h"
#include "SharedConnectionPoints.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>

namespace woml
{
  class MeteorologicalAnalysis
  {
  public:
	MeteorologicalAnalysis();
	void addFeature(Feature * theFeature);
	void addConnectionPoint(const std::string & theName, const Point & thePoint);
	void addConnectionPoints(const std::map<std::string,Point> & thePoints);
	void validTime(const boost::posix_time::time_period & thePeriod);
	void creationTime(const boost::posix_time::ptime & theTime);
	void latestModificationTime(const boost::posix_time::ptime & theTime);
	void analysisTime(const boost::posix_time::ptime & theTime);

	typedef boost::ptr_list<Feature>::const_iterator const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

  private:

	boost::ptr_list<Feature> itsFeatureMembers;
	boost::posix_time::time_period itsValidTime;
	boost::posix_time::ptime itsCreationTime;
	boost::posix_time::ptime itsLatestModificationTime;
	boost::posix_time::ptime itsAnalysisTime;

	SharedConnectionPoints itsSharedConnectionPoints;

  }; // class MeteorologicalAnalysis
} // namespace woml

#endif // WOML_METEOROLOGICAL_ANALYSIS_H



