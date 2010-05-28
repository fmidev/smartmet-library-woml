// ======================================================================
/*!
 * \brief woml::Envelope
 */
// ======================================================================

#include "Envelope.h"
#include <cassert>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

Envelope::Envelope()
  : itsBounded(false)
  , itsLowerCorner(0,0)
  , itsUpperCorner(0,0)
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Envelope::Envelope(const Point & theLowerCorner,
				   const Point & theUpperCorner)
  : itsBounded(true)
  , itsLowerCorner(theLowerCorner)
  , itsUpperCorner(theUpperCorner)
{ }

// ----------------------------------------------------------------------
/*!
 * \brief True if envelope is bounded
 */
//  ----------------------------------------------------------------------

bool Envelope::bounded() const
{
  return itsBounded;
}

// ----------------------------------------------------------------------
/*!
 * \brief Lower corner accessor18

 */
// ----------------------------------------------------------------------

const Point & Envelope::lowerCorner() const
{
  assert(itsBounded);
  return itsLowerCorner;
}

// ----------------------------------------------------------------------
/*!
 * \brief upper corner accessor
 */
// ----------------------------------------------------------------------

const Point & Envelope::upperCorner() const
{
  assert(itsBounded);
  return itsUpperCorner;
}

} // namespace woml
