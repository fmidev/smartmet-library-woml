// ======================================================================
/*!
 * \brief woml::ParameterTimeSeriesPoint
 */
// ======================================================================

#pragma once

#include "Feature.h"
#include "FeatureVisitor.h"
#include "GeophysicalParameterValueSet.h"
#include "TimeSeriesSlot.h"

#define ParameterTimeSeriesPointDerivedClass(c)                                    \
  class c : public ParameterTimeSeriesPoint                                        \
  {                                                                                \
   public:                                                                         \
    c(const std::string& classNameExt) : ParameterTimeSeriesPoint(classNameExt) {} \
    void visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); }      \
    const char* className() const { return #c; }                                   \
  }

namespace woml
{
class FeatureVisitor;

class ParameterTimeSeriesPoint : public Feature
{
 public:
  ParameterTimeSeriesPoint(const std::string& theClassNameExt);
  virtual ~ParameterTimeSeriesPoint() {}

  void timePeriod(const boost::posix_time::time_period& theTimePeriod);
  const boost::posix_time::time_period& timePeriod() const;

  void add(const boost::optional<Fmi::DateTime>& validTime,
           GeophysicalParameterValueSet* values);
  void sort();
  const std::list<TimeSeriesSlot>& timeseries() const;

 private:
  boost::posix_time::time_period itsTimePeriod;
  std::list<TimeSeriesSlot> itsTimeSeriesSlots;

};  // class ParameterTimeSeriesPoint

ParameterTimeSeriesPointDerivedClass(CloudLayers);
ParameterTimeSeriesPointDerivedClass(Contrails);
ParameterTimeSeriesPointDerivedClass(Icing);
ParameterTimeSeriesPointDerivedClass(Turbulence);
ParameterTimeSeriesPointDerivedClass(MigratoryBirds);
ParameterTimeSeriesPointDerivedClass(SurfaceVisibility);
ParameterTimeSeriesPointDerivedClass(SurfaceWeather);
ParameterTimeSeriesPointDerivedClass(Winds);
ParameterTimeSeriesPointDerivedClass(ZeroTolerance);

}  // namespace woml
