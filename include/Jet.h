// ======================================================================
/*!
 * \brief woml::Jet
 */
// ======================================================================

#ifndef WOML_JET_H
#define WOML_JET_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class Jet : public Feature
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
	double itsWindStrength; // TODO

  }; // class Jet

} // namespace woml

#endif // WOML_JET_H
