// ======================================================================
/*!
 * \brief woml::MeteorologicalObject
 */
// ======================================================================

#include "MeteorologicalObject.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <set>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

MeteorologicalObject::MeteorologicalObject() : itsTimeSynchronizedFeatureMembers() {}
// ----------------------------------------------------------------------
/*!
 * \brief Add a time synchronized feature member
 */
// ----------------------------------------------------------------------

void MeteorologicalObject::addTimeSynchronizedFeature(ParameterTimeSeriesPoint *theFeature)
{
  if (theFeature)
    itsTimeSynchronizedFeatureMembers.push_back(theFeature);
  else
    throw std::runtime_error(
        "addTimeSynchronizedFeature: the feature is not a ParameterTimeSeriesPoint object");
}

// ----------------------------------------------------------------------
/*!
 * \brief Synchronize time series feature members
 */
// ----------------------------------------------------------------------

void MeteorologicalObject::synchronize()
{
  // Syncronize the time series feature members (ParameterTimeSeriesPoint derived objects)
  // to have common time instants by copying the values from the preceeding time instants
  // to the missing time instants (if any)
  //
  // SurfaceWeather and SurfaceVisibility are rendered synchronized in frontier

  std::list<ParameterTimeSeriesPoint *>::iterator ppbeg = itsTimeSynchronizedFeatureMembers.begin();
  std::list<ParameterTimeSeriesPoint *>::iterator ppend = itsTimeSynchronizedFeatureMembers.end();
  std::list<ParameterTimeSeriesPoint *>::iterator itpp;

  std::list<woml::TimeSeriesSlot>::const_iterator tsbeg, tsend, itts, pitts;

  std::set<boost::posix_time::ptime> ti;

  // Get all time instants

  for (itpp = ppbeg; (itpp != ppend); itpp++)
  {
    const std::list<TimeSeriesSlot> &ts = (*itpp)->timeseries();

    tsbeg = ts.begin();
    tsend = ts.end();

    if (tsbeg == tsend)
      // No data, nothing to do
      //
      return;

    // for (itts = tsbeg; (itts != tsend); itts++) printf("> Sync add
    // %s\n",to_iso_string(itts->validTime()).c_str());
    for (itts = tsbeg; (itts != tsend); itts++)
      ti.insert(itts->validTime());
  }

  // Add missing time instants

  for (bool missing = true; missing;)
  {
    missing = false;
    std::set<boost::posix_time::ptime>::iterator tibeg = ti.begin(), tiend = ti.end(), itti;

    for (itpp = ppbeg, itti = tibeg; (itpp != ppend); itpp++)
    {
      const std::list<TimeSeriesSlot> &ts = (*itpp)->timeseries();

      tsbeg = ts.begin();
      tsend = ts.end();

      for (itts = pitts = tsbeg, itti = tibeg; ((itti != tiend) && (!missing)); itts++)
        if ((itts == tsend) || (itts->validTime() > *itti))
        {
          // TimeSeriesSlot is expected to contain only one ParameterValueSet
          //
          // printf("> Sync itts=%s add itti=%s\n",(itts == tsend) ? "<end>":
          // to_iso_string(itts->validTime()).c_str(),to_iso_string(*itti).c_str());
          GeophysicalParameterValueSet *pvs =
              new GeophysicalParameterValueSet(**(pitts->values().begin()));
          (*itpp)->add(boost::optional<boost::posix_time::ptime>(*itti), pvs);

          missing = true;
        }
        else
        {
          itti++;
          pitts = itts;
        }

      // Sort the time serie if a time instant was added

      if (missing) (*itpp)->sort();
    }
  }
}

}  // namespace woml
