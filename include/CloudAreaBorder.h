// ======================================================================
/*!
 * \brief woml::CloudAreaBorder
 */
// ======================================================================

#ifndef WOML_CLOUDAREABORDER_H
#define WOML_CLOUDAREABORDER_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class CloudAreaBorder : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlCurve(const CubicSplineCurve & theControlCurve);
	void connectStartPoint(const std::string & theName);
	void connectEndPoint(const std::string & theName);

  private:
	Envelope itsBoundedBy;
	CubicSplineCurve itsControlCurve;
	std::string itsStartPointConnectsTo;
	std::string itsEndPointConnectsTo;

  }; // class CloudAreaBorder

} // namespace woml

#endif // WOML_CLOUDAREABORDER_H
