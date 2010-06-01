// ======================================================================
/*!
 * \brief woml::UpperTrough
 */
// ======================================================================

#ifndef WOML_UPPERTROUGH_H
#define WOML_UPPERTROUGH_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class UpperTrough : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void controlCurve(const CubicSplineCurve & theControlCurve);
	void connectStartPoint(const std::string & theName);
	void connectEndPoint(const std::string & theName);

  private:
	Envelope itsBoundedBy;
	CubicSplineCurve itsControlCurve;
	std::string itsStartPointConnectsTo;
	std::string itsEndPointConnectsTo;

  }; // class UpperTrough

} // namespace woml

#endif // WOML_UPPERTROUGH_H
// ======================================================================
/*!
 * \brief woml::UpperUpperTrough
 */
// ======================================================================

#ifndef WOML_UPPERUPPERTROUGH_H
#define WOML_UPPERUPPERTROUGH_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include <map>
#include <string>

namespace woml
{
  class Envelope;
  class FeatureVisitor;

  class UpperUpperTrough : public Feature
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
  private:
	Envelope itsBoundedBy;
	std::map<std::string,std::string> itsShortInfo;
	std::map<std::string,std::string> itsLongInfo;
	CubicSplineCurve itsControlCurve;

  }; // class UpperUpperTrough

} // namespace woml

#endif // WOML_UPPERUPPERTROUGH_H
