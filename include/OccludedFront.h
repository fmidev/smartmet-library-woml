// ======================================================================
/*!
 * \brief woml::OccludedFront
 */
// ======================================================================

#ifndef WOML_OCCLUDEDFRONT_H
#define WOML_OCCLUDEDFRONT_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class OccludedFront : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlCurve(const CubicSplineCurve & theControlCurve);
	void connectStartPoint(const std::string & theName);
	void connectEndPoint(const std::string & theName);

	const CubicSplineCurve & controlCurve() const;

  private:
	Envelope itsBoundedBy;
	CubicSplineCurve itsControlCurve;
	std::string itsStartPointConnectsTo;
	std::string itsEndPointConnectsTo;
	bool itsStationary; // TODO

  }; // class OccludedFront

} // namespace woml

#endif // WOML_OCCLUDEDFRONT_H
