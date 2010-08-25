// ======================================================================
/*!
 * \brief woml::PointGeophysicalParameterValueSet
 */
// ======================================================================

#ifndef WOML_POINTGEOPHYSICALPARAMETERVALUESET_H
#define WOML_POINTGEOPHYSICALPARAMETERVALUESET_H

#include "Envelope.h"
#include "Feature.h"
#include "Point.h"
#include <boost/shared_ptr.hpp>

namespace woml
{
  class FeatureVisitor;
  class GeophysicalParameterValueSet;

  class PointGeophysicalParameterValueSet : public Feature
  {
  public:
	PointGeophysicalParameterValueSet();
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void point(const Point & thePoint);
	void priority(int thePriority);
	void param(GeophysicalParameterValueSet * theParameterValueSet);

	const Point & point() const;
	boost::shared_ptr<GeophysicalParameterValueSet> parameters() const;

  private:
	Envelope itsBoundedBy;
	Point itsPoint;
	int itsPriority;
	boost::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

  }; // class PointGeophysicalParameterValueSet

} // namespace woml

#endif // WOML_POINTGEOPHYSICALPARAMETERVALUESET_H
