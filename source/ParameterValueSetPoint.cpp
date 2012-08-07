// ======================================================================
/*!
 * \brief class woml::ParameterValueSetPoint
 */
// ======================================================================

#include "ParameterValueSetPoint.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void ParameterValueSetPoint::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the parameter values
 */
// ----------------------------------------------------------------------

void ParameterValueSetPoint::param(GeophysicalParameterValueSet * theParameterValueSet)
{
  itsParameterValueSet.reset(theParameterValueSet);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

boost::shared_ptr<GeophysicalParameterValueSet>
ParameterValueSetPoint::parameters() const
{
  return itsParameterValueSet;
}

} // namespace woml
