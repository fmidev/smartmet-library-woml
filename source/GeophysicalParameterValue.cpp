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
													 double theValue)
	: itsParameter(theParam)
	, itsValue(theValue)
  {
  }


} // namespace woml
