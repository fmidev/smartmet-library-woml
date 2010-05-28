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
  class WarmFront : public Feature;
  {
  public:
  private:
	Envelope boundedBy;
	std::map<std::string,std::string> shortInfo;
	std::map<std::string,std::string> longInfo;
	CubicSplineCurve controlCurve;

  }; // class WarmFront

} // namespace woml

#endif // WOML_WARMFRONT_H
