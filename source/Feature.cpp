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
  : itsValidTime(boost::posix_time::ptime(boost::posix_time::not_a_date_time),
				 boost::posix_time::ptime(boost::posix_time::not_a_date_time))
{
}

// ----------------------------------------------------------------------
/*
 * \brief Set the valid time
 */
// ----------------------------------------------------------------------

void Feature::validTime(const boost::posix_time::time_period & theTime)
{
  itsValidTime = theTime;
}

// ----------------------------------------------------------------------
/*
 * \brief Get the valid time
 */
// ----------------------------------------------------------------------

const boost::posix_time::time_period & Feature::validTime() const
{
  return itsValidTime;
}

} // namespace woml
