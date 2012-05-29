// ======================================================================
/*!
 * \brief woml::AbstractLineObject
 */
// ======================================================================

#ifndef WOML_ABSTRACTLINEOBJECT_H
#define WOML_ABSTRACTLINEOBJECT_H

#include "Feature.h"
#include "FeatureVisitor.h"
#include "Envelope.h"
#include "CubicSplineCurve.h"
#include <string>

#define AbstractLineObjectDerivedClass(c) \
  class c : public AbstractLineObject { \
    public: \
      c() : AbstractLineObject() {} \
      virtual void visit(FeatureVisitor & theVisitor) const { theVisitor.visit(*this); } \
  }

namespace woml
{
  class AbstractLineObject : public Feature
  {
  public:
	virtual ~AbstractLineObject() {}
	virtual void visit(FeatureVisitor & theVisitor) const = 0;

	void orientation(const boost::optional<std::string> & theOrientation);
	const std::string & orientation() const;

	void envelope(const boost::optional<Envelope> & theEnvelope);

	void controlCurve(const CubicSplineCurve & theControlCurve);
	const CubicSplineCurve & controlCurve() const;

	void connectStartPoint(const std::string & theName);
	void connectEndPoint(const std::string & theName);

  protected:
	boost::optional<std::string> itsOrientation;
	boost::optional<Envelope> itsBoundedBy;
	CubicSplineCurve itsControlCurve;
	std::string itsStartPointConnectsTo;
	std::string itsEndPointConnectsTo;

  }; // class AbstractLineObject

  AbstractLineObjectDerivedClass(ColdAdvection);
  AbstractLineObjectDerivedClass(ColdFront);
  AbstractLineObjectDerivedClass(Ridge);
  AbstractLineObjectDerivedClass(Trough);
  AbstractLineObjectDerivedClass(UpperTrough);
  AbstractLineObjectDerivedClass(WarmAdvection);
  AbstractLineObjectDerivedClass(WarmFront);

} // namespace woml

#endif // WOML_ABSTRACTLINEOBJECT_H
