// ======================================================================
/*!
 * \brief woml::ParameterValueSetArea
 */
// ======================================================================

#pragma once

#include <boost/ptr_container/ptr_list.hpp>
#include "AbstractSurfaceObject.h"
#include "Feature.h"
#include "GeophysicalParameterValueSet.h"

namespace woml
{
class FeatureVisitor;

class ParameterValueSetArea : public AbstractSurfaceObject
{
 public:
  ParameterValueSetArea();

  virtual void visit(FeatureVisitor& theVisitor) const;

  void param(GeophysicalParameterValueSet* theParameterValueSet);
  boost::shared_ptr<GeophysicalParameterValueSet> parameters() const;

  void innerArea(ParameterValueSetArea* theArea);

 private:
  boost::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

  boost::ptr_list<ParameterValueSetArea> itsInnerArea;

};  // class ParameterValueSetArea

}  // namespace woml
