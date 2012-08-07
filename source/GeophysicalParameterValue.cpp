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
  {
  }

} // namespace woml
