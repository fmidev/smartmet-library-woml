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
  : itsElevation()
  , itsValues()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the elevation
 */
// ----------------------------------------------------------------------

void
GeophysicalParameterValueSet::elevation(const boost::optional<Elevation> & theElevation)
{
  itsElevation = theElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the elevation
 */
// ----------------------------------------------------------------------

const boost::optional<Elevation> & GeophysicalParameterValueSet::elevation() const
{
  return itsElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a parameter value
 */
// ----------------------------------------------------------------------

void
GeophysicalParameterValueSet::add(const GeophysicalParameterValue & theValue)
{
  itsValues.push_back(theValue);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the values
 */
// ----------------------------------------------------------------------

const GeophysicalParameterValueList &
GeophysicalParameterValueSet::values() const
{
  return itsValues;
}

} // namespace woml
