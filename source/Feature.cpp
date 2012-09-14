// ======================================================================
/*!
 * \brief woml:Feature
 */
// ======================================================================

#include "Feature.h"
#include <boost/foreach.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Feature::Feature()
  : itsCreationTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time))
  , itsValidTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time))
  , itsShortInfos()
{
}

// ----------------------------------------------------------------------
/*
 * \brief Set the creation time
 */
// ----------------------------------------------------------------------

void Feature::creationTime(const boost::posix_time::ptime & theTime)
{
  itsCreationTime = theTime;
}

// ----------------------------------------------------------------------
/*
 * \brief Set the latest modification time
 */
// ----------------------------------------------------------------------

void Feature::latestModificationTime(const boost::optional<boost::posix_time::ptime> & theTime)
{
  itslatestModificationTime = theTime;
}

// ----------------------------------------------------------------------
/*
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void Feature::validTime(const boost::optional<boost::posix_time::ptime> & theTime)
{
  itsValidTime = theTime;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add short info
 */
// ----------------------------------------------------------------------

void Feature::addShortInfo(const std::string & theLanguage,const std::string & theShortInfo)
{
	if ((theLanguage.length() > 0) && (theShortInfo.length() > 0)) {
		// The locale string is used for case insensitive comparisons (only)
		//
		std::string lang(theLanguage);
		boost::to_lower(lang);

		itsShortInfos.insert(std::make_pair(lang,theShortInfo));
	}
}

// ----------------------------------------------------------------------
/*!
 * \brief Add short infos
 */
// ----------------------------------------------------------------------

void Feature::addShortInfos(const MeteorologicalObjectInfo & theShortInfos)
{
  BOOST_FOREACH(const MeteorologicalObjectInfo::value_type & shortInfo, theShortInfos)
	{
	  addShortInfo(shortInfo.first, shortInfo.second);
	}
}

// ----------------------------------------------------------------------
/*!
 * \brief Get short info
 */
// ----------------------------------------------------------------------

const std::string & Feature::text(const std::string & theLanguage) const
{
	MeteorologicalObjectInfo::const_iterator it = itsShortInfos.find(theLanguage);

	if (it == itsShortInfos.end())
		// First text is returned if the queried language is undefined
		//
		if (theLanguage.empty() && (itsShortInfos.size() > 0))
			it = itsShortInfos.begin();
		else
			return theLanguage;

	return it->second;
}

// ----------------------------------------------------------------------
/*
 * \brief Get the valid time
 */
// ----------------------------------------------------------------------

const boost::optional<boost::posix_time::ptime> & Feature::validTime() const
{
  return itsValidTime;
}

// ----------------------------------------------------------------------
/*
 * \brief Get the latest modification time
 */
// ----------------------------------------------------------------------

const boost::optional<boost::posix_time::ptime> & Feature::latestModificationTime() const
{
  return itslatestModificationTime;
}

} // namespace woml
