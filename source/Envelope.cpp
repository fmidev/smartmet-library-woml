// ======================================================================
/*!
 * \brief woml::Envelope
 */
// ======================================================================

#include "Envelope.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Envelope::Envelope(const Point & theLowerCorner, const Point & theUpperCorner)
  : itsLowerCorner(theLowerCorner)
  , itsUpperCorner(theUpperCorner)
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Lower corner accessor18

 */
// ----------------------------------------------------------------------

const Point & Envelope::lowerCorner() const
{
  return itsLowerCorner;
}

// ----------------------------------------------------------------------
/*!
 * \brief upper corner accessor
 */
// ----------------------------------------------------------------------

const Point & Envelope::upperCorner() const
{
  return itsUpperCorner;
}

} // namespace woml
