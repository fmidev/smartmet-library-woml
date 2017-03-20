// ======================================================================
/*!
 * \brief woml::MeteorologicalObject
 */
// ======================================================================

#pragma once

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

