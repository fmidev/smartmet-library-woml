// ======================================================================
/*!
 * \brief woml::TargetRegion
 */
// ======================================================================

#include "TargetRegion.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

TargetRegion::TargetRegion() : itsBoundedBy(), itsRegionIds(), itsLocalizedNames() {}
// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void TargetRegion::envelope(const std::optional<Envelope>& theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the envelope
 */
// ----------------------------------------------------------------------

const std::optional<Envelope>& TargetRegion::envelope() const { return itsBoundedBy; }
// ----------------------------------------------------------------------
/*!
 * \brief Add a region id
 */
// ----------------------------------------------------------------------

void TargetRegion::addRegionId(const std::string& theScheme, const std::string& theRegionId)
{
  if ((theScheme.length() > 0) && (theRegionId.length() > 0))
    itsRegionIds.push_back(std::make_pair(theScheme, theRegionId));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the region ids
 */
// ----------------------------------------------------------------------

TargetRegion::RegionIds_const_iterator TargetRegion::RegionIds_begin() const
{
  return itsRegionIds.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the region ids
 */
// ----------------------------------------------------------------------

TargetRegion::RegionIds_const_iterator TargetRegion::RegionIds_end() const
{
  return itsRegionIds.end();
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a localized name
 */
// ----------------------------------------------------------------------

void TargetRegion::addLocalizedName(const std::string& theLanguage,
                                    const std::string& theLocalizedName)
{
  if ((theLanguage.length() > 0) && (theLocalizedName.length() > 0))
    itsLocalizedNames.push_back(std::make_pair(theLanguage, theLocalizedName));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the localized names
 */
// ----------------------------------------------------------------------

TargetRegion::LocalizedNames_const_iterator TargetRegion::LocalizedNames_begin() const
{
  return itsLocalizedNames.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the localized names
 */
// ----------------------------------------------------------------------

TargetRegion::LocalizedNames_const_iterator TargetRegion::LocalizedNames_end() const
{
  return itsLocalizedNames.end();
}

}  // namespace woml
