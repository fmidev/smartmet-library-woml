// ======================================================================
/*!
 * \brief woml::Feature
 */
// ======================================================================

#pragma once

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

typedef std::multimap<std::string, std::string> MeteorologicalObjectInfo;

namespace woml
{
class FeatureVisitor;

class Feature
{
 public:
  virtual ~Feature() {}
  Feature(const std::string &theClassNameExt = "");
  virtual void visit(FeatureVisitor& theVisitor) const {}
  void creationTime(const boost::posix_time::ptime& theTime);
  void validTime(const boost::optional<boost::posix_time::ptime>& theTime);
  const boost::optional<boost::posix_time::ptime>& validTime() const;
  void latestModificationTime(const boost::optional<boost::posix_time::ptime>& theTime);
  const boost::optional<boost::posix_time::ptime>& latestModificationTime() const;
  void addShortInfo(const std::string& theLanguage, const std::string& theShortInfo);
  void addShortInfos(const MeteorologicalObjectInfo& theShortInfos);
  const std::string& text(const std::string& theLanguage) const;
  const std::string& classNameExt() const { return itsClassNameExt; }

  protected:
  std::string itsClassNameExt;

 private:
  boost::posix_time::ptime itsCreationTime;
  boost::optional<boost::posix_time::ptime> itsValidTime;
  boost::optional<boost::posix_time::ptime> itslatestModificationTime;
  MeteorologicalObjectInfo itsShortInfos;

};  // class Feature

}  // namespace woml
