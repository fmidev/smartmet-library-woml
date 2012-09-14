// ======================================================================
/*!
 * \brief woml::TimeSeriesSlot
 */
// ======================================================================

#ifndef WOML_TIMESERIESSLOT_H
#define WOML_TIMESERIESSLOT_H

#include "Feature.h"
#include <list>
#include <boost/ptr_container/ptr_list.hpp>

namespace woml
{
  class FeatureVisitor;
  class GeophysicalParameterValueSet;

  class TimeSeriesSlot
  {
  public:
	TimeSeriesSlot(const boost::posix_time::ptime & theValidTime,GeophysicalParameterValueSet * theValues);

	void add(GeophysicalParameterValueSet * theValues);
	void sort();
	bool operator < (const TimeSeriesSlot & theOther) const;

	const boost::posix_time::ptime & validTime() const;
	const std::list<boost::shared_ptr<GeophysicalParameterValueSet> > & values() const;
	std::list<boost::shared_ptr<GeophysicalParameterValueSet> > & editableValues();

  private:
	boost::posix_time::ptime itsValidTime;
	std::list<boost::shared_ptr<GeophysicalParameterValueSet> > itsValues;

  }; // class TimeSeriesSlot

} // namespace woml

#endif // WOML_TIMESERIESSLOT_H
