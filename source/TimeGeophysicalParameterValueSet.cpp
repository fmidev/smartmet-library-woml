// ======================================================================
/*!
 * \brief class woml::TimeGeophysicalParameterValueSet
 */
// ======================================================================

#include "TimeGeophysicalParameterValueSet.h"
#include "GeophysicalParameterValueSet.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

TimeGeophysicalParameterValueSet::TimeGeophysicalParameterValueSet()
  : itsBoundedBy()
  , itsParameterValueSet()
{
  itsTimePeriod.b = itsTimePeriod.e = 0;
}


// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void TimeGeophysicalParameterValueSet::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void TimeGeophysicalParameterValueSet::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the time for the value
 */
// ----------------------------------------------------------------------

void TimeGeophysicalParameterValueSet::timePeriod(const TimePeriod & theTimePeriod)
{
  itsTimePeriod = theTimePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the parameter values
 */
// ----------------------------------------------------------------------

void TimeGeophysicalParameterValueSet::param(GeophysicalParameterValueSet * theParameterValueSet)
{
  itsParameterValueSet.reset(theParameterValueSet);
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the time period
 */
// ----------------------------------------------------------------------

const TimePeriod & TimeGeophysicalParameterValueSet::timePeriod() const
{
  return itsTimePeriod;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the parameter values
 */
// ----------------------------------------------------------------------

boost::shared_ptr<GeophysicalParameterValueSet>
TimeGeophysicalParameterValueSet::parameters() const
{
  return itsParameterValueSet;
}

} // namespace woml
