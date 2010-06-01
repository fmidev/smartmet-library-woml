// ======================================================================
/*!
 * \brief woml::WarmFront
 */
// ======================================================================

#ifndef WOML_WARMFRONT_H
#define WOML_WARMFRONT_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class WarmFront : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlCurve(const CubicSplineCurve & theControlCurve);
  private:
	Envelope itsBoundedBy;
	CubicSplineCurve itsControlCurve;

  }; // class WarmFront

} // namespace woml

#endif // WOML_WARMFRONT_H
