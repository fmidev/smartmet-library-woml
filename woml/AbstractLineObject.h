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

// c is the class name, it cannot be parenthesized
// NOLINTBEGIN(bugprone-macro-parentheses)
#define AbstractLineObjectDerivedClass(c)                                             \
  class c : public AbstractLineObject                                                 \
  {                                                                                   \
   public:                                                                            \
    c() : AbstractLineObject() {}                                                     \
    virtual void visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); } \
  }
// NOLINTEND(bugprone-macro-parentheses)

namespace woml
{
class AbstractLineObject : public Feature
{
 public:
  ~AbstractLineObject() override {}
  void visit(FeatureVisitor& theVisitor) const override = 0;

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
