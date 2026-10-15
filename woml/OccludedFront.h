// ======================================================================
/*!
 * \brief woml::OccludedFront
 */
// ======================================================================

#pragma once

#include "AbstractLineObject.h"

namespace woml
{
class OccludedFront : public AbstractLineObject
{
 public:
  void visit(FeatureVisitor& theVisitor) const override;

  void stationary(bool theStationary);
  bool stationary() const;

 private:
  bool itsStationary = false;

};  // class OccludedFront

}  // namespace woml
