// ======================================================================
/*!
 * \brief woml::AbstractLineObject
 */
// ======================================================================

#pragma once

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include "FeatureVisitor.h"
#include <string>

#define AbstractLineObjectDerivedClass(c)                                             \
  class c : public AbstractLineObject                                                 \
  {                                                                                   \
   public:                                                                            \
    c() : AbstractLineObject() {}                                                     \
    virtual void visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); } \
  }

namespace woml
{
class AbstractLineObject : public Feature
{
 public:
  virtual ~AbstractLineObject() {}
  virtual void visit(FeatureVisitor& theVisitor) const = 0;

  void orientation(const std::optional<std::string>& theOrientation);
  const std::string& orientation() const;

  void envelope(const std::optional<Envelope>& theEnvelope);

  void controlCurve(const CubicSplineCurve& theControlCurve);
  const CubicSplineCurve& controlCurve() const;

  void connectStartPoint(const std::string& theName);
  void connectEndPoint(const std::string& theName);

 protected:
  std::optional<std::string> itsOrientation;
  std::optional<Envelope> itsBoundedBy;
  CubicSplineCurve itsControlCurve;
  std::string itsStartPointConnectsTo;
  std::string itsEndPointConnectsTo;

};  // class AbstractLineObject

AbstractLineObjectDerivedClass(ColdAdvection);
AbstractLineObjectDerivedClass(ColdFront);
AbstractLineObjectDerivedClass(Ridge);
AbstractLineObjectDerivedClass(Trough);
AbstractLineObjectDerivedClass(UpperTrough);
AbstractLineObjectDerivedClass(WarmAdvection);
AbstractLineObjectDerivedClass(WarmFront);

}  // namespace woml
