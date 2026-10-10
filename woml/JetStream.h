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

  typedef std::list<std::pair<int, NumericalSingleValueMeasure> > maximumWindSpeedList;
  void maximumWindSpeed(const int segmentIndex,
                        const NumericalSingleValueMeasure& theMaximumWindSpeed);
  typedef maximumWindSpeedList::const_iterator MaximumWindSpeeds_const_iterator;
  MaximumWindSpeeds_const_iterator MaximumWindSpeeds_begin() const;
  MaximumWindSpeeds_const_iterator MaximumWindSpeeds_end() const;

 private:
  maximumWindSpeedList itsMaximumWindSpeeds;

};  // class JetStream

}  // namespace woml
