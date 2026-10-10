// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValueSet
 */
// ======================================================================

#pragma once

#include "Elevation.h"
#include "GeophysicalParameterValue.h"
#include <list>

namespace woml
{
using GeophysicalParameterValueList = std::list<GeophysicalParameterValue>;

class GeophysicalParameterValueSet
{
 public:
  GeophysicalParameterValueSet();

  void elevation(const std::optional<Elevation>& theElevation);
  const std::optional<Elevation>& elevation() const;

  void add(const GeophysicalParameterValue& theValue);
  void sort();
  const GeophysicalParameterValueList& values() const;
  GeophysicalParameterValueList& editableValues();

 private:
  std::optional<Elevation> itsElevation;
  GeophysicalParameterValueList itsValues;

};  // class GeophysicalParameterValueSet

}  // namespace woml
