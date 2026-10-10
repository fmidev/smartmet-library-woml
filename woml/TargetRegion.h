// ======================================================================
/*!
 * \brief woml::TargetRegion
 */
// ======================================================================

#pragma once

#include "Envelope.h"
#include <list>
#include <string>

namespace woml
{
class TargetRegion
{
 public:
  TargetRegion();

  void envelope(const std::optional<Envelope>& theEnvelope);
  const std::optional<Envelope>& envelope() const;

  using regionIdList = std::list<std::pair<std::string, std::string> >;
  void addRegionId(const std::string& theScheme, const std::string& theRegionId);
  using RegionIds_const_iterator = regionIdList::const_iterator;
  RegionIds_const_iterator RegionIds_begin() const;
  RegionIds_const_iterator RegionIds_end() const;

  using localizedNameList = std::list<std::pair<std::string, std::string> >;
  void addLocalizedName(const std::string& theLanguage, const std::string& theLocalizedName);
  using LocalizedNames_const_iterator = localizedNameList::const_iterator;
  LocalizedNames_const_iterator LocalizedNames_begin() const;
  LocalizedNames_const_iterator LocalizedNames_end() const;

 private:
  std::optional<Envelope> itsBoundedBy;
  regionIdList itsRegionIds;
  localizedNameList itsLocalizedNames;

};  // class TargetRegion
}  // namespace woml
