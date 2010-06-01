// ======================================================================
/*!
 * \brief woml::ColdFront
 */
// ======================================================================

#ifndef WOML_COLDFRONT_H
#define WOML_COLDFRONT_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class ColdFront : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlCurve(const CubicSplineCurve & theControlCurve);
  private:
	Envelope itsBoundedBy;
	CubicSplineCurve itsControlCurve;

  }; // class ColdFront

} // namespace woml

#endif // WOML_COLDFRONT_H
