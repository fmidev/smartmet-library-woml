// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValue
 */
// ======================================================================

#ifndef WOML_GEOPHYSICALPARAMETERVALUE_H
#define WOML_GEOPHYSICALPARAMETERVALUE_H

#include "GeophysicalParameter.h"
#include "MeasureValue.h"
#include "Elevation.h"
#include <boost/shared_ptr.hpp>

namespace woml
{
  class GeophysicalParameterValue
  {
  public:
	GeophysicalParameterValue(const GeophysicalParameter & theParam,
							  const MeasureValue * theValue,
							  const Elevation & theElevation);

	bool operator < (const GeophysicalParameterValue & theOther) const;

	const GeophysicalParameter & parameter() const { return itsParameter; }
	const MeasureValue * value() const { return itsValue.get(); }
	const Elevation & elevation() const { return itsElevation; }

  private:
	GeophysicalParameterValue();

	const GeophysicalParameter itsParameter;
	const boost::shared_ptr<const MeasureValue> itsValue;
	const Elevation itsElevation;
	
  }; // class GeophysicalParamterValue

} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETERVALUE_H
