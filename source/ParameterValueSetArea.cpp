// ======================================================================
/*!
 * \brief class woml::ParameterValueSetArea
 */
// ======================================================================

#include "ParameterValueSetArea.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

ParameterValueSetArea::ParameterValueSetArea()
  : AbstractSurfaceObject()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void ParameterValueSetArea::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the parameter values
 */
// ----------------------------------------------------------------------

void ParameterValueSetArea::param(GeophysicalParameterValueSet * theParameterValueSet)
{
  itsParameterValueSet.reset(theParameterValueSet);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

boost::shared_ptr<GeophysicalParameterValueSet>
ParameterValueSetArea::parameters() const
{
  return itsParameterValueSet;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add an inner precipitation area
 */
// ----------------------------------------------------------------------

void ParameterValueSetArea::innerArea(ParameterValueSetArea * theArea)
{
  itsInnerArea.push_back(theArea);
}

} // namespace woml
