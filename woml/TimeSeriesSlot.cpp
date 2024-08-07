// ======================================================================
/*!
 * \brief class woml::TimeSeriesSlot
 */
// ======================================================================

#include "TimeSeriesSlot.h"
#include "GeophysicalParameterValueSet.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

TimeSeriesSlot::TimeSeriesSlot(const Fmi::DateTime& theValidTime,
                               GeophysicalParameterValueSet* theValues)
    : itsValidTime(theValidTime), itsValues()
{
  itsValues.push_back(std::shared_ptr<GeophysicalParameterValueSet>(theValues));
}

// ----------------------------------------------------------------------
/*!
 * \brief Add parameter values
 */
// ----------------------------------------------------------------------

void TimeSeriesSlot::add(GeophysicalParameterValueSet* theValues)
{
  itsValues.push_back(std::shared_ptr<GeophysicalParameterValueSet>(theValues));
}

// ----------------------------------------------------------------------
/*!
 * \brief Sort the parameter values based on descending elevation
 */
// ----------------------------------------------------------------------

void TimeSeriesSlot::sort()
{
  std::list<std::shared_ptr<GeophysicalParameterValueSet> >::iterator it = itsValues.begin();

  for (; (it != itsValues.end()); it++)
    (*it)->sort();
}

// ----------------------------------------------------------------------
/*!
 * \brief Operator <
 */
// ----------------------------------------------------------------------

bool TimeSeriesSlot::operator<(const TimeSeriesSlot& theOther) const
{
  // Sort to ascending time

  return (itsValidTime < theOther.itsValidTime);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the validtime
 */
// ----------------------------------------------------------------------

const Fmi::DateTime& TimeSeriesSlot::validTime() const { return itsValidTime; }
// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

const std::list<std::shared_ptr<GeophysicalParameterValueSet> >& TimeSeriesSlot::values() const
{
  return itsValues;
}

std::list<std::shared_ptr<GeophysicalParameterValueSet> >& TimeSeriesSlot::editableValues()
{
  return itsValues;
}

}  // namespace woml
