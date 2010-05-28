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
#include <map>
#include <string>

namespace woml
{
  class FeatureVisitor;

  class WarmFront : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;

  }; // class WarmFront

} // namespace woml

#endif // WOML_WARMFRONT_H
