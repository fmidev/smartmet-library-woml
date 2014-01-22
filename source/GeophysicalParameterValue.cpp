// ======================================================================
/*!
 * \brief woml:GeophysicalParameterValue
 */
// ======================================================================

#include "GeophysicalParameterValue.h"

#include <stdexcept>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

GeophysicalParameterValue::GeophysicalParameterValue(const GeophysicalParameter & theParam,
													 MeasureValue * theValue,
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

// ----------------------------------------------------------------------
/*!
 * \brief Keep track of tallest label elevation
 */
// ----------------------------------------------------------------------

void GeophysicalParameterValue::labelElevation(const Elevation & theLabelElevation)
{
	const woml::Elevation & e = theLabelElevation;
	boost::optional<woml::NumericalSingleValueMeasure> itsBoundedLo = (e.bounded() ? e.lowerLimit() : woml::NumericalSingleValueMeasure());
	const boost::optional<woml::NumericalSingleValueMeasure> & itsLoLimit = (e.bounded() ? itsBoundedLo : e.value());
	boost::optional<woml::NumericalSingleValueMeasure> itsBoundedHi = (e.bounded() ? e.upperLimit() : woml::NumericalSingleValueMeasure());
	const boost::optional<woml::NumericalSingleValueMeasure> & itsHiLimit = (e.bounded() ? itsBoundedHi : e.value());

	if ((!itsLoLimit) || (!itsHiLimit))
		throw std::runtime_error("addLabelElevation: Elevation range not set");

	// The label elevation stores scaled px range values (svg y -axis grows downwards; lo > hi)

	if (
		(!itsLabelElevation) ||
		(
		 (itsLoLimit->numericValue() - itsHiLimit->numericValue()) >
		 (itsLabelElevation->lowerLimit()->numericValue() - itsLabelElevation->upperLimit()->numericValue())
		)
	   )
		itsLabelElevation = theLabelElevation;
}

} // namespace woml
