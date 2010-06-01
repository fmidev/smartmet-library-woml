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
#include <map>
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
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;
	double itsWindStrength;

  }; // class Jet

} // namespace woml

#endif // WOML_JET_H
