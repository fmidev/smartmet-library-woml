// ======================================================================
/*!
 * \brief class woml::PointNote
 */
// ======================================================================

#include "PointNote.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

PointNote::PointNote()
  : itsBoundedBy()
  , itsPoint(0,0)
  , itsPriority(0)
  , itsNoteText()
{ }


// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void PointNote::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the envelope
 */
// ----------------------------------------------------------------------

void PointNote::envelope(const Envelope & theEnvelope)
{
  itsBoundedBy = theEnvelope;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the coordinate for the symbol
 */
// ----------------------------------------------------------------------

void PointNote::point(const Point & thePoint)
{
  itsPoint = thePoint;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the priority
 */
// ----------------------------------------------------------------------

void PointNote::priority(int thePriority)
{
  itsPriority = thePriority;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a note text
 */
// ----------------------------------------------------------------------

  void PointNote::noteText(const std::string & theLanguage,
						   const std::string & theText)
{
  itsNoteText[theLanguage] = theText;
}

} // namespace woml
