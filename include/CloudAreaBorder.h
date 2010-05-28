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
#include <map>
#include <string>

namespace woml
{
  class CloudAreaBorder : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;

  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;

  }; // class CloudAreaBorder

} // namespace woml

#endif // WOML_CLOUDAREABORDER_H
