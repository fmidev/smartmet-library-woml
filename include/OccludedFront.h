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
#include <map>
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
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;
	bool itsStationary;

  }; // class OccludedFront

} // namespace woml

#endif // WOML_OCCLUDEDFRONT_H
