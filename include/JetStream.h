// ======================================================================
/*!
 * \brief woml::JetStream
 */
// ======================================================================

#ifndef WOML_JETSTREAM_H
#define WOML_JETSTREAM_H

#include "AbstractLineObject.h"
#include "MeasureValue.h"
#include <list>

namespace woml
{
class JetStream : public AbstractLineObject
{
 public:
  virtual void visit(FeatureVisitor& theVisitor) const;

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

#endif  // WOML_JETSTREAM_H
