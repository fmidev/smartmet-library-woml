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
#include <map>
#include <string>

namespace woml
{
  class FeatureVisitor;

  class ColdFront : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;

  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;

  }; // class ColdFront

} // namespace woml

#endif // WOML_COLDFRONT_H
