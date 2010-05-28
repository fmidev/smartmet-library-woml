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
	Envelope();
	Envelope(const Point & theLowerCorner, const Point & theUpperCorner);
	bool bounded() const;
	const Point & lowerCorner() const;
	const Point & upperCorner() const;

  private:

	bool itsBounded;
	Point itsLowerCorner;
	Point itsUpperCorner;

  }; // class Envelope
} // namespace woml

#endif // WOML_ENVELOPE_H
