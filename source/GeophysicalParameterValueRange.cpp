// ======================================================================
/*!
 * \brief woml:GeophysicalParameterValueRange
 */
// ======================================================================

#include "GeophysicalParameterValueRange.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueRange::GeophysicalParameterValueRange(const GeophysicalParameter & theParam,
															   double theLowerLimit,
															   double theUpperLimit)
	: itsParameter(theParam)
	, itsLowerLimit(theLowerLimit)
	, itsUpperLimit(theUpperLimit)
  {
  }


} // namespace woml
