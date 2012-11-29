// ======================================================================
/*!
 * \brief woml:GeophysicalParameterValue
 */
// ======================================================================

#include "GeophysicalParameterValue.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

GeophysicalParameterValue::GeophysicalParameterValue(const GeophysicalParameter & theParam,
													 const MeasureValue * theValue,
													 const Elevation & theElevation)
	: itsParameter(theParam)
	, itsValue(theValue)
	, itsElevation(theElevation)
	, itsFlagBits(0)
  {
  }

// ----------------------------------------------------------------------
/*!
 * \brief Operator <
 */
// ----------------------------------------------------------------------

bool GeophysicalParameterValue::operator < (const GeophysicalParameterValue & theOther) const
{
	boost::optional<NumericalSingleValueMeasure> itsBoundedUpper = (itsElevation.bounded() ? itsElevation.upperLimit() : NumericalSingleValueMeasure());
	const boost::optional<NumericalSingleValueMeasure> & itsUpperLimit = (itsElevation.bounded() ? itsBoundedUpper : itsElevation.value());

	boost::optional<NumericalSingleValueMeasure> theBoundedUpper = (theOther.elevation().bounded() ? theOther.elevation().upperLimit() : NumericalSingleValueMeasure());
	const boost::optional<NumericalSingleValueMeasure> & theUpperLimit = (theOther.elevation().bounded() ? theBoundedUpper : theOther.elevation().value());

	if (!itsUpperLimit)
		return false;
	else  if (!theUpperLimit)
		return true;

	// Sort to descending elevation

	return (itsUpperLimit->numericValue() > theUpperLimit->numericValue());
}

} // namespace woml
