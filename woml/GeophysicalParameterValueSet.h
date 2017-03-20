// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValueSet
 */
// ======================================================================

#pragma once

#include "GeophysicalParameterValue.h"
#include "Elevation.h"
#include <list>

namespace woml
{
typedef std::list<GeophysicalParameterValue> GeophysicalParameterValueList;

class GeophysicalParameterValueSet
{
 public:
  GeophysicalParameterValueSet();

  void elevation(const boost::optional<Elevation>& theElevation);
  const boost::optional<Elevation>& elevation() const;

  void add(const GeophysicalParameterValue& theValue);
  void sort();
  const GeophysicalParameterValueList& values() const;
  GeophysicalParameterValueList& editableValues();

 private:
  boost::optional<Elevation> itsElevation;
  GeophysicalParameterValueList itsValues;

};  // class GeophysicalParameterValueSet

}  // namespace woml

