// ======================================================================
/*!
 * \brief woml::Envelope
 */
// ======================================================================

#ifndef WOML_ENVELOPE_H
#define WOML_ENVELOPE_H

#include "Point.h"

namespace woml
{
  class Envelope
  {
  public:

	Envelope(const Point & p1, const Point & p2)
	  : lowerCorner(p1)
	  , upperCorner(p2)
	{ }

	Point lowerCorner;
	Point upperCorner;

  private:
	Envelope();

  }; // class Envelope
} // namespace woml

#endif // WOML_ENVELOPE_H
