// ======================================================================
/*!
 * \brief woml::ParameterValueSetPoint
 */
// ======================================================================

#ifndef WOML_PARAMETERVALUESETPOINT_H
#define WOML_PARAMETERVALUESETPOINT_H

#include "AbstractPointObject.h"
#include "GeophysicalParameterValueSet.h"
#include "FeatureVisitor.h"
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

#endif  // WOML_PARAMETERVALUESETPOINT_H
