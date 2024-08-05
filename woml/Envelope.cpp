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

Envelope::Envelope() : itsBounded(false), itsPoint(), itsRect(), itsSrsName(), itsSrsDimension() {}
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Envelope::Envelope(const std::optional<Point>& thePoint,
                   std::string theSrsName,
                   std::string theSrsDimension)
    : itsBounded(false),
      itsPoint(thePoint),
      itsRect(),
      itsSrsName(theSrsName),
      itsSrsDimension(theSrsDimension)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

Envelope::Envelope(const std::optional<Rect>& theRect,
                   std::string theSrsName,
                   std::string theSrsDimension)
    : itsBounded(theRect ? true : false),
      itsPoint(),
      itsRect(theRect),
      itsSrsName(theSrsName),
      itsSrsDimension(theSrsDimension)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief True if envelope is bounded
 */
//  ----------------------------------------------------------------------

bool Envelope::bounded() const { return itsBounded; }
// ----------------------------------------------------------------------
/*!
 * \brief Point accessor
 */
// ----------------------------------------------------------------------

const std::optional<Point>& Envelope::point() const { return itsPoint; }
// ----------------------------------------------------------------------
/*!
 * \brief Lower corner accessor
 */
// ----------------------------------------------------------------------

const std::optional<Point> Envelope::lowerCorner() const
{
  std::optional<Point> lc;

  if (itsRect) lc = itsRect->lowerCorner();

  return lc;
}

// ----------------------------------------------------------------------
/*!
 * \brief Upper corner accessor
 */
// ----------------------------------------------------------------------

const std::optional<Point> Envelope::upperCorner() const
{
  std::optional<Point> uc;

  if (itsRect) uc = itsRect->upperCorner();

  return uc;
}

}  // namespace woml
