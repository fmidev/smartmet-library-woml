// ======================================================================
/*!
 * \brief woml::Feature
 */
// ======================================================================

#pragma once

#include <map>
#include <macgyver/DateTime.h>
#include <optional>
#include <memory>

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
  void creationTime(const Fmi::DateTime& theTime);
  void validTime(const std::optional<Fmi::DateTime>& theTime);
  const std::optional<Fmi::DateTime>& validTime() const;
  void latestModificationTime(const std::optional<Fmi::DateTime>& theTime);
  const std::optional<Fmi::DateTime>& latestModificationTime() const;
  void addShortInfo(const std::string& theLanguage, const std::string& theShortInfo);
  void addShortInfos(const MeteorologicalObjectInfo& theShortInfos);
  const std::string& text(const std::string& theLanguage) const;
  const std::string& classNameExt() const { return itsClassNameExt; }

  protected:
  std::string itsClassNameExt;

 private:
  Fmi::DateTime itsCreationTime;
  std::optional<Fmi::DateTime> itsValidTime;
  std::optional<Fmi::DateTime> itslatestModificationTime;
  MeteorologicalObjectInfo itsShortInfos;

};  // class Feature

}  // namespace woml
