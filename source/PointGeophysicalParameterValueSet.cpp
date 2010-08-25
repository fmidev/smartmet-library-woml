// ======================================================================
/*!
 * \brief class woml::PointGeophysicalParameterValueSet
 */
// ======================================================================

#include "PointGeophysicalParameterValueSet.h"
#include "GeophysicalParameterValueSet.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

PointGeophysicalParameterValueSet::PointGeophysicalParameterValueSet()
  : itsBoundedBy()
  , itsPoint(0,0)
  , itsPriority(0)
  , itsParameterValueSet()
{ }


// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void PointGeophysicalParameterValueSet::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void PointGeophysicalParameterValueSet::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the coordinate for the symbol
 */
// ----------------------------------------------------------------------

void PointGeophysicalParameterValueSet::point(const Point & thePoint)
{
  itsPoint = thePoint;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the priority
 */
// ----------------------------------------------------------------------

void PointGeophysicalParameterValueSet::priority(int thePriority)
{
  itsPriority = thePriority;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the symbol
 */
// ----------------------------------------------------------------------

void PointGeophysicalParameterValueSet::param(GeophysicalParameterValueSet * theParameterValueSet)
{
  itsParameterValueSet.reset(theParameterValueSet);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the coordinate
 */
// ----------------------------------------------------------------------

const Point & PointGeophysicalParameterValueSet::point() const
{
  return itsPoint;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

boost::shared_ptr<GeophysicalParameterValueSet>
PointGeophysicalParameterValueSet::parameters() const
{
  return itsParameterValueSet;
}

} // namespace woml
