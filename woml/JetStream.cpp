// ======================================================================
/*!
 * \brief class woml::JetStream
 */
// ======================================================================

#include "JetStream.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void JetStream::visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); }
// ----------------------------------------------------------------------
/*!
 * \brief Set the maximum wind speed
 */
// ----------------------------------------------------------------------

void JetStream::maximumWindSpeed(const int segmentIndex,
                                 const NumericalSingleValueMeasure& theMaximumWindSpeed)
{
  itsMaximumWindSpeeds.push_back(std::make_pair(segmentIndex, theMaximumWindSpeed));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the maximum wind speeds
 */
// ----------------------------------------------------------------------

JetStream::MaximumWindSpeeds_const_iterator JetStream::MaximumWindSpeeds_begin() const
{
  return itsMaximumWindSpeeds.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the maximum wind speeds
 */
// ----------------------------------------------------------------------

JetStream::MaximumWindSpeeds_const_iterator JetStream::MaximumWindSpeeds_end() const
{
  return itsMaximumWindSpeeds.end();
}

}  // namespace woml
