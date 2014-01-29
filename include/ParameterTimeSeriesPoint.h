// ======================================================================
/*!
 * \brief woml::ParameterTimeSeriesPoint
 */
// ======================================================================

#ifndef WOML_PARAMETERTIMESERIESPOINT_H
#define WOML_PARAMETERTIMESERIESPOINT_H

#include "Feature.h"
#include "FeatureVisitor.h"
#include "TimeSeriesSlot.h"
#include "GeophysicalParameterValueSet.h"

#define ParameterTimeSeriesPointDerivedClass(c) \
  class c : public ParameterTimeSeriesPoint { \
    public: \
      c(const std::string & classNameExt) : ParameterTimeSeriesPoint(classNameExt) {} \
      void visit(FeatureVisitor & theVisitor) const { theVisitor.visit(*this); } \
      const char * className() const { return #c; } \
  }

namespace woml
{
  class FeatureVisitor;

  class ParameterTimeSeriesPoint : public Feature
  {
  public:
	ParameterTimeSeriesPoint(const std::string & theClassNameExt);
	virtual ~ParameterTimeSeriesPoint() {}

	const std::string & classNameExt() const;

	void timePeriod(const boost::posix_time::time_period & theTimePeriod);
	const boost::posix_time::time_period & timePeriod() const;

	void add(const boost::optional<boost::posix_time::ptime> & validTime,GeophysicalParameterValueSet * values);
	void sort();
	const std::list<TimeSeriesSlot> & timeseries() const;

  private:
	std::string itsClassNameExt;
	boost::posix_time::time_period itsTimePeriod;
	std::list<TimeSeriesSlot> itsTimeSeriesSlots;

  }; // class ParameterTimeSeriesPoint

  ParameterTimeSeriesPointDerivedClass(CloudLayers);
  ParameterTimeSeriesPointDerivedClass(Contrails);
  ParameterTimeSeriesPointDerivedClass(Icing);
  ParameterTimeSeriesPointDerivedClass(Turbulence);
  ParameterTimeSeriesPointDerivedClass(MigratoryBirds);
  ParameterTimeSeriesPointDerivedClass(SurfaceVisibility);
  ParameterTimeSeriesPointDerivedClass(SurfaceWeather);
  ParameterTimeSeriesPointDerivedClass(Winds);
  ParameterTimeSeriesPointDerivedClass(ZeroTolerance);

} // namespace woml

#endif // WOML_PARAMETERTIMESERIESPOINT_H
