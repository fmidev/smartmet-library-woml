// ======================================================================
/*!
 * \brief woml::MeteorologicalAnalysis
 *
 * 		  Note: Should inherit MeteorologicalAnalysis and WeatherForecast
 *				from new parent; all members and behaviour are equal!
 */
// ======================================================================

#pragma once

#include "DataSource.h"
#include "Envelope.h"
#include "Feature.h"
#include "InfoText.h"
#include "MeteorologicalObject.h"
#include "Point.h"
#include "TargetRegion.h"
#include <macgyver/DateTime.h>
#include <boost/ptr_container/ptr_list.hpp>

typedef std::multimap<std::string, std::string> MeteorologicalAnalysisInfo;

namespace woml
{
class MeteorologicalAnalysis : public MeteorologicalObject
{
 public:
  MeteorologicalAnalysis();
  void addFeature(Feature* theFeature, bool timeSynchronized = false);
  void envelope(const std::optional<Envelope>& theEnvelope);
  void validTime(const Fmi::TimePeriod& thePeriod);
  const Fmi::TimePeriod& validTime() const;
  void creator(const std::string& theCreator);
  const std::string& creator() const;
  void creationTime(const Fmi::DateTime& theTime);
  const Fmi::DateTime& creationTime() const;
  void latestModificationTime(const std::optional<Fmi::DateTime>& theTime);
  const std::optional<Fmi::DateTime>& latestModificationTime() const;
  void analysisTime(const Fmi::DateTime& theTime);
  const Fmi::DateTime& analysisTime() const;
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
  std::optional<Envelope> itsBoundedBy;
  Fmi::TimePeriod itsValidTime;
  std::string itsCreator;
  Fmi::DateTime itsCreationTime;
  std::optional<Fmi::DateTime> itsLatestModificationTime;
  Fmi::DateTime itsAnalysisTime;
  TargetRegionList itsTargetRegions;
  //	MeteorologicalAnalysisInfo itsShortInfos;
  //	MeteorologicalAnalysisInfo itsLongInfos;

  DataSource itsDataSource;

};  // class MeteorologicalAnalysis
}  // namespace woml
