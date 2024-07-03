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

GeophysicalParameterValueSet::GeophysicalParameterValueSet() : itsElevation(), itsValues() {}
// ----------------------------------------------------------------------
/*!
 * \brief Set the elevation
 */
// ----------------------------------------------------------------------

void GeophysicalParameterValueSet::elevation(const std::optional<Elevation>& theElevation)
{
  itsElevation = theElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the elevation
 */
// ----------------------------------------------------------------------

const std::optional<Elevation>& GeophysicalParameterValueSet::elevation() const
{
  return itsElevation;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a parameter value
 */
// ----------------------------------------------------------------------

void GeophysicalParameterValueSet::add(const GeophysicalParameterValue& theValue)
{
  itsValues.push_back(theValue);
}

// ----------------------------------------------------------------------
/*!
 * \brief Sort the parameter values to have descending elevation
 */
// ----------------------------------------------------------------------

void GeophysicalParameterValueSet::sort() { itsValues.sort(); }
// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

const GeophysicalParameterValueList& GeophysicalParameterValueSet::values() const
{
  return itsValues;
}

GeophysicalParameterValueList& GeophysicalParameterValueSet::editableValues() { return itsValues; }
}  // namespace woml
