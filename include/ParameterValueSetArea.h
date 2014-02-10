// ======================================================================
/*!
 * \brief woml::ParameterValueSetArea
 */
// ======================================================================

#ifndef WOML_PARAMETERVALUESETAREA_H
#define WOML_PARAMETERVALUESETAREA__H

#include "AbstractSurfaceObject.h"
#include "GeophysicalParameterValueSet.h"
#include "Feature.h"
#include <boost/ptr_container/ptr_list.hpp>

namespace woml
{
  class FeatureVisitor;

  class ParameterValueSetArea : public AbstractSurfaceObject
  {
  public:
	ParameterValueSetArea();

	virtual void visit(FeatureVisitor & theVisitor) const;

	void param(GeophysicalParameterValueSet * theParameterValueSet);
	boost::shared_ptr<GeophysicalParameterValueSet> parameters() const;

	void innerArea(ParameterValueSetArea * theArea);

  private:
	boost::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

	boost::ptr_list<ParameterValueSetArea> itsInnerArea;

  }; // class ParameterValueSetArea

} // namespace woml

#endif // WOML_PARAMETERVALUESETAREA__H
