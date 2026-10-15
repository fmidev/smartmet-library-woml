// ======================================================================
/*!
 * \brief woml::JetStream
 */
// ======================================================================

#pragma once

#include "AbstractLineObject.h"
#include "MeasureValue.h"
#include <list>

namespace woml
{
class JetStream : public AbstractLineObject
{
 public:
  void visit(FeatureVisitor& theVisitor) const override;

  using maximumWindSpeedList = std::list<std::pair<int, NumericalSingleValueMeasure> >;
  void maximumWindSpeed(int segmentIndex, const NumericalSingleValueMeasure& theMaximumWindSpeed);
  using MaximumWindSpeeds_const_iterator = maximumWindSpeedList::const_iterator;
  MaximumWindSpeeds_const_iterator MaximumWindSpeeds_begin() const;
  MaximumWindSpeeds_const_iterator MaximumWindSpeeds_end() const;

 private:
  maximumWindSpeedList itsMaximumWindSpeeds;

};  // class JetStream

}  // namespace woml
