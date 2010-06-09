// ======================================================================
/*!
 * \brief woml::GeophysicalParameterValueSet
 */
// ======================================================================

#ifndef WOML_GEOPHYSICALPARAMETERVALUESET_H
#define WOML_GEOPHYSICALPARAMETERVALUESET_H

#include "GeophysicalParameterValue.h"
#include "GeophysicalParameterValueRange.h"
#include <list>

namespace woml
{
  class GeophysicalParameterValueSet
  {
  public:
	GeophysicalParameterValueSet();
	void elevation(double theElevation);
	void add(const GeophysicalParameterValue & theSingleValue);
	void add(const GeophysicalParameterValueRange & theValueRange);

  private:

	double itsElevation;
	std::list<GeophysicalParameterValue> itsSingleValues;
	std::list<GeophysicalParameterValueRange> itsValueRanges;

  }; // class GeophysicalParameterValueSet

} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETERVALUESET_H
