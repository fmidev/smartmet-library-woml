// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 *
 * 		  Note: Should inherit MeteorologicalAnalysis and WeatherForecast
 *				from new parent; all members and behaviour are equal!
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_ANALYSIS_H
#define WOML_METEOROLOGICAL_ANALYSIS_H

#include "DataSource.h"
#include "Envelope.h"
#include "Feature.h"
#include "Point.h"
#include "TargetRegion.h"
#include "InfoText.h"
#include "MeteorologicalObject.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/ptr_container/ptr_list.hpp>

typedef std::multimap<std::string, std::string> MeteorologicalAnalysisInfo;

namespace woml
{
class MeteorologicalAnalysis : public MeteorologicalObject
{
 public:
  MeteorologicalAnalysis();
  void addFeature(Feature* theFeature, bool timeSynchronized = false);
  void envelope(const boost::optional<Envelope>& theEnvelope);
  void validTime(const boost::posix_time::time_period& thePeriod);
  const boost::posix_time::time_period& validTime() const;
  void creator(const std::string& theCreator);
  const std::string& creator() const;
  void creationTime(const boost::posix_time::ptime& theTime);
  const boost::posix_time::ptime& creationTime() const;
  void latestModificationTime(const boost::optional<boost::posix_time::ptime>& theTime);
  const boost::optional<boost::posix_time::ptime>& latestModificationTime() const;
  void analysisTime(const boost::posix_time::ptime& theTime);
  const boost::posix_time::ptime& analysisTime() const;
  //	void addShortInfo(const std::string & theLanguage,const std::string & theShortInfo);
  void addShortInfos(const MeteorologicalAnalysisInfo& theShortInfos);
  //	void addLongInfo(const std::string & theLanguage,const std::string & theLongInfo);
  void addLongInfos(const MeteorologicalAnalysisInfo& theLongInfos);

  typedef std::list<TargetRegion> TargetRegionList;
  void addTargetRegion(const TargetRegion& theTargetRegion);
  typedef TargetRegionList::const_iterator TargetRegions_const_iterator;
  TargetRegions_const_iterator TargetRegions_begin() const;
  TargetRegions_const_iterator TargetRegions_end() const;

  void dataSource(const DataSource& theSource);
  const DataSource& dataSource() const;

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
  boost::posix_time::ptime itsAnalysisTime;
  TargetRegionList itsTargetRegions;
  //	MeteorologicalAnalysisInfo itsShortInfos;
  //	MeteorologicalAnalysisInfo itsLongInfos;

  DataSource itsDataSource;

};  // class MeteorologicalAnalysis
}  // namespace woml

#endif  // WOML_METEOROLOGICAL_ANALYSIS_H
