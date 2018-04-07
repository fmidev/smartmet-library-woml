// ======================================================================
/*!
 * \brief woml::ParameterValueSetPoint
 */
// ======================================================================

#pragma once

#include "AbstractPointObject.h"
#include "FeatureVisitor.h"
#include "GeophysicalParameterValueSet.h"
#include <boost/shared_ptr.hpp>

namespace woml
{
class ParameterValueSetPoint : public AbstractPointObject
{
 public:
  void visit(FeatureVisitor& theVisitor) const;

  void param(GeophysicalParameterValueSet* theParameterValueSet);
  boost::shared_ptr<GeophysicalParameterValueSet> parameters() const;

 private:
  boost::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

};  // class ParameterValueSetPoint

}  // namespace woml
