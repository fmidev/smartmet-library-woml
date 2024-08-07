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

  typedef std::list<std::pair<std::string, std::string> > regionIdList;
  void addRegionId(const std::string& theScheme, const std::string& theRegionId);
  typedef regionIdList::const_iterator RegionIds_const_iterator;
  RegionIds_const_iterator RegionIds_begin() const;
  RegionIds_const_iterator RegionIds_end() const;

  typedef std::list<std::pair<std::string, std::string> > localizedNameList;
  void addLocalizedName(const std::string& theLanguage, const std::string& theLocalizedName);
  typedef localizedNameList::const_iterator LocalizedNames_const_iterator;
  LocalizedNames_const_iterator LocalizedNames_begin() const;
  LocalizedNames_const_iterator LocalizedNames_end() const;

 private:
  std::optional<Envelope> itsBoundedBy;
  regionIdList itsRegionIds;
  localizedNameList itsLocalizedNames;

};  // class TargetRegion
}  // namespace woml
