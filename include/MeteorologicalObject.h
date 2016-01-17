// ======================================================================
/*!
 * \brief woml::MeteorologicalObject
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_OBJECT_H
#define WOML_METEOROLOGICAL_OBJECT_H

#include "ParameterTimeSeriesPoint.h"

namespace woml
{
class MeteorologicalObject
{
 public:
  MeteorologicalObject();

  void addTimeSynchronizedFeature(ParameterTimeSeriesPoint *theFeature);
  void synchronize();

 private:
  std::list<ParameterTimeSeriesPoint *> itsTimeSynchronizedFeatureMembers;

};  // class MeteorologicalObject
}  // namespace woml

#endif  // WOML_METEOROLOGICAL_OBJECT_H
