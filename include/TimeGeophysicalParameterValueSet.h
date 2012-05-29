// ======================================================================
/*!
 * \brief woml::TimeGeophysicalParameterValueSet
 */
// ======================================================================

#ifndef WOML_TIMEGEOPHYSICALPARAMETERVALUESET_H
#define WOML_TIMEGEOPHYSICALPARAMETERVALUESET_H

#include "Envelope.h"
#include "Feature.h"
#include <boost/shared_ptr.hpp>

namespace woml
{
  class FeatureVisitor;
  class GeophysicalParameterValueSet;

  typedef struct { int b; int e; } TimePeriod;

  class TimeGeophysicalParameterValueSet : public Feature
  {
  public:
	TimeGeophysicalParameterValueSet();
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void timePeriod(const TimePeriod & theTimePeriod);
	void param(GeophysicalParameterValueSet * theParameterValueSet);

	const TimePeriod & timePeriod() const;
	boost::shared_ptr<GeophysicalParameterValueSet> parameters() const;

  private:
	Envelope itsBoundedBy;
	TimePeriod itsTimePeriod;
	int itsPriority;
	boost::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

  }; // class TimeGeophysicalParameterValueSet

} // namespace woml

#endif // WOML_TIMEGEOPHYSICALPARAMETERVALUESET_H
