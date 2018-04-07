// ======================================================================
/*!
 * \brief woml::TimeSeriesSlot
 */
// ======================================================================

#pragma once

#include "Feature.h"
#include <boost/ptr_container/ptr_list.hpp>
#include <list>

namespace woml
{
class FeatureVisitor;
class GeophysicalParameterValueSet;

class TimeSeriesSlot
{
 public:
  TimeSeriesSlot(const boost::posix_time::ptime& theValidTime,
                 GeophysicalParameterValueSet* theValues);

  void add(GeophysicalParameterValueSet* theValues);
  void sort();
  bool operator<(const TimeSeriesSlot& theOther) const;

  const boost::posix_time::ptime& validTime() const;
  const std::list<boost::shared_ptr<GeophysicalParameterValueSet> >& values() const;
  std::list<boost::shared_ptr<GeophysicalParameterValueSet> >& editableValues();

 private:
  boost::posix_time::ptime itsValidTime;
  std::list<boost::shared_ptr<GeophysicalParameterValueSet> > itsValues;

};  // class TimeSeriesSlot

}  // namespace woml
