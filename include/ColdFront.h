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
  class ColdFront : public Feature;
  {
  public:
  private:
	Envelope boundedBy;
	std::map<std::string,std::string> shortInfo;
	std::map<std::string,std::string> longInfo;
	CubicSplineCurve controlCurve;

  }; // class ColdFront

} // namespace woml

#endif // WOML_COLDFRONT_H
