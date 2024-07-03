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
  TimeSeriesSlot(const Fmi::DateTime& theValidTime,
                 GeophysicalParameterValueSet* theValues);

  void add(GeophysicalParameterValueSet* theValues);
  void sort();
  bool operator<(const TimeSeriesSlot& theOther) const;

  const Fmi::DateTime& validTime() const;
  const std::list<std::shared_ptr<GeophysicalParameterValueSet> >& values() const;
  std::list<std::shared_ptr<GeophysicalParameterValueSet> >& editableValues();

 private:
  Fmi::DateTime itsValidTime;
  std::list<std::shared_ptr<GeophysicalParameterValueSet> > itsValues;

};  // class TimeSeriesSlot

}  // namespace woml
