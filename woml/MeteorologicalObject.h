// ======================================================================
/*!
 * \brief woml::MeteorologicalObject
 */
// ======================================================================

#pragma once

#include <list>

namespace woml
{
class ParameterTimeSeriesPoint;

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
