// ======================================================================
/*!
 * \brief woml::Trough
 */
// ======================================================================

#ifndef WOML_TROUGH_H
#define WOML_TROUGH_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <map>
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class Trough : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;

  }; // class Trough

} // namespace woml

#endif // WOML_TROUGH_H
