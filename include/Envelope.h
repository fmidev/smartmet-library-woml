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

	Envelope(const Point & theLowerCorner, const Point & theUpperCorner);
	const Point & lowerCorner() const;
	const Point & upperCorner() const;

  private:

	Envelope();
	Point itsLowerCorner;
	Point itsUpperCorner;

  }; // class Envelope
} // namespace woml

#endif // WOML_ENVELOPE_H
