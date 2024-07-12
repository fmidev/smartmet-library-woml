// ======================================================================
/*!
 * \brief woml::ParameterValueSetPoint
 */
// ======================================================================

#pragma once

#include "AbstractPointObject.h"
#include "FeatureVisitor.h"
#include "GeophysicalParameterValueSet.h"
#include <memory>

namespace woml
{
class ParameterValueSetPoint : public AbstractPointObject
{
 public:
  void visit(FeatureVisitor& theVisitor) const;

  void param(GeophysicalParameterValueSet* theParameterValueSet);
  std::shared_ptr<GeophysicalParameterValueSet> parameters() const;

 private:
  std::shared_ptr<GeophysicalParameterValueSet> itsParameterValueSet;

};  // class ParameterValueSetPoint

}  // namespace woml
