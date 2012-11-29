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
	void elevation(const Elevation & theElevation) { itsElevation = theElevation; }
	const Elevation & elevation() const { return itsElevation; }

	// For some externally defined t/f flags
	//
	void addFlags(unsigned int theFlagBits) { itsFlagBits |= theFlagBits; }
	unsigned int getFlags() const { return itsFlagBits; }

  private:
	GeophysicalParameterValue();

	const GeophysicalParameter itsParameter;
	const boost::shared_ptr<const MeasureValue> itsValue;
	Elevation itsElevation;

	unsigned int itsFlagBits;
	
  }; // class GeophysicalParamterValue

} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETERVALUE_H
