// ======================================================================
/*!
 * \brief woml:Feature
 */
// ======================================================================

#include "Feature.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Feature::Feature()
  : itsValidTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time))
{
}

// ----------------------------------------------------------------------
/*
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void Feature::validTime(const boost::posix_time::ptime & theTime)
{
  itsValidTime = theTime;
}

// ----------------------------------------------------------------------
/*
 * \brief Get the valid time
 */
// ----------------------------------------------------------------------

const boost::posix_time::ptime & Feature::validTime() const
{
  return itsValidTime;
}

} // namespace woml
