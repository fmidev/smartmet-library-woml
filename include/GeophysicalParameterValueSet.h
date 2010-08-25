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
  typedef std::list<GeophysicalParameterValue> GeophysicalParameterValueList;
  typedef std::list<GeophysicalParameterValueRange> GeophysicalParameterValueRangeList;

  class GeophysicalParameterValueSet
  {
  public:
	GeophysicalParameterValueSet();
	void elevation(double theElevation);
	void add(const GeophysicalParameterValue & theSingleValue);
	void add(const GeophysicalParameterValueRange & theValueRange);

	const GeophysicalParameterValueList & values() const;
	const GeophysicalParameterValueRangeList & ranges() const;

  private:

	double itsElevation;
	GeophysicalParameterValueList itsSingleValues;
	GeophysicalParameterValueRangeList itsValueRanges;

  }; // class GeophysicalParameterValueSet

} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETERVALUESET_H
