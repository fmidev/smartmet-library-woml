// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValueSet
 */
// ======================================================================

#include "GeophysicalParameterValueSet.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

GeophysicalParameterValueSet::GeophysicalParameterValueSet()
  : itsElevation(0)
  , itsSingleValues()
  , itsValueRanges()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the elevation
 */
// ----------------------------------------------------------------------

void
GeophysicalParameterValueSet::elevation(double theElevation)
{
  itsElevation = theElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a parameter value
 */
// ----------------------------------------------------------------------

void
GeophysicalParameterValueSet::add(const GeophysicalParameterValue & theValue)
{
  itsSingleValues.push_back(theValue);
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a parameter range
 */
// ----------------------------------------------------------------------

void
GeophysicalParameterValueSet::add(const GeophysicalParameterValueRange & theRange)
{
  itsValueRanges.push_back(theRange);
}


} // namespace woml
