// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValue
 */
// ======================================================================

#ifndef WOML_GEOPHYSICALPARAMETERVALUE_H
#define WOML_GEOPHYSICALPARAMETERVALUE_H

#include "GeophysicalParameter.h"

namespace woml
{
  class GeophysicalParameterValue
  {
  public:
	GeophysicalParameterValue(const GeophysicalParameter & theParam,
							  double theValue);

	const GeophysicalParameter & parameter() const { return itsParameter; }
	double value() const { return itsValue; }

  private:

	GeophysicalParameterValue();
	GeophysicalParameter itsParameter;
	double itsValue;
	
  }; // class GeophysicalParamterValue

} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETERVALUE_H
