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
	virtual void visit(FeatureVisitor & visitor) const;

  private:
	Envelope boundedBy;
	std::map<std::string,std::string> shortInfo;
	std::map<std::string,std::string> longInfo;
	CubicSplineCurve controlCurve;

  }; // class CloudAreaBorder

} // namespace woml

#endif // WOML_CLOUDAREABORDER_H
