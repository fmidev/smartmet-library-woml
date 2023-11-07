// ======================================================================
/*!
 * \brief class woml::ParameterTimeSeriesPoint
 */
// ======================================================================

#include "ParameterTimeSeriesPoint.h"
#include "FeatureVisitor.h"
#include "TimeSeriesSlot.h"

#include <macgyver/DateTime.h>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

ParameterTimeSeriesPoint::ParameterTimeSeriesPoint(const std::string& theClassNameExt)
    : Feature(theClassNameExt),
      itsTimePeriod(Fmi::DateTime(boost::posix_time::not_a_date_time),
                    Fmi::DateTime(boost::posix_time::not_a_date_time)),
      itsTimeSeriesSlots()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the time period
 */
// ----------------------------------------------------------------------

void ParameterTimeSeriesPoint::timePeriod(const boost::posix_time::time_period& theTimePeriod)
{
  itsTimePeriod = theTimePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the time period
 */
// ----------------------------------------------------------------------

const boost::posix_time::time_period& ParameterTimeSeriesPoint::timePeriod() const
{
  return itsTimePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a new time instant or new parameter values to an existing time instant
 */
// ----------------------------------------------------------------------

void ParameterTimeSeriesPoint::add(const boost::optional<Fmi::DateTime>& theValidTime,
                                   GeophysicalParameterValueSet* theValues)
{
  std::list<TimeSeriesSlot>::iterator it = itsTimeSeriesSlots.begin();

  for (; (it != itsTimeSeriesSlots.end()); it++)
    if (it->validTime() == *theValidTime)
    {
      it->add(theValues);
      return;
    }

  itsTimeSeriesSlots.push_back(TimeSeriesSlot(*theValidTime, theValues));
}

// ----------------------------------------------------------------------
/*!
 * \brief Sort the time series (ascending) and elevations (descending)
 * 		  within times serie's parameter values
 */
// ----------------------------------------------------------------------

void ParameterTimeSeriesPoint::sort()
{
  itsTimeSeriesSlots.sort();

  std::list<TimeSeriesSlot>::iterator it = itsTimeSeriesSlots.begin();

  for (; (it != itsTimeSeriesSlots.end()); it++)
    it->sort();
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the time series
 */
// ----------------------------------------------------------------------

const std::list<TimeSeriesSlot>& ParameterTimeSeriesPoint::timeseries() const
{
  return itsTimeSeriesSlots;
}

}  // namespace woml
