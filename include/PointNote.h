// ======================================================================
/*!
 * \brief woml::PointNote
 */
// ======================================================================

#ifndef WOML_POINTNOTE_H
#define WOML_POINTNOTE_H

#include "CubicSplineCurve.h"
#include "Envelope.h"
#include "Feature.h"
#include "Point.h"
#include <boost/scoped_ptr.hpp>
#include <map>

namespace woml
{
  class FeatureVisitor;

  class PointNote : public Feature
  {
  public:
	PointNote();
	virtual void visit(FeatureVisitor & theVisitor) const;
	void envelope(const Envelope & theEnvelope);
	void point(const Point & thePoint);
	void priority(int thePriority);
	void noteText(const std::string & theLanguage, const std::string & theText);
	// void symbol(Note * theSymbol);

  private:
	Envelope itsBoundedBy;
	Point itsPoint;
	int itsPriority;
	std::map<std::string,std::string> itsNoteText;

  }; // class PointNote

} // namespace woml

#endif // WOML_POINTNOTE_H
