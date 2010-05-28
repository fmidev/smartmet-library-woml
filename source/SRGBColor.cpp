// ======================================================================
/*!
 * \brief woml::SRGBColor
 */
// ======================================================================

#include "SRGBColor.h"
#include <cassert>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

SRGBColor::SRGBColor(int theRed, int theGreen, int theBlue, int theAlpha)
  : itsRed(theRed)
  , itsGreen(theGreen)
  , itsBlue(theBlue)
  , itsAlpha(theAlpha)
{
  assert(itsRed >= 0 && itsRed <= 255);
  assert(itsGreen >= 0 && itsGreen <= 255);
  assert(itsBlue >= 0 && itsBlue <= 255);
  assert(itsAlpha >= 0 && itsAlpha <= 255);
}

// ----------------------------------------------------------------------
/*!
 * \brief Red accessor
 */
// ----------------------------------------------------------------------

int SRGBColor::red() const
{
  return itsRed;
}

// ----------------------------------------------------------------------
/*!
 * \brief Green accessor
 */
// ----------------------------------------------------------------------

int SRGBColor::green() const
{
  return itsGreen;
}

// ----------------------------------------------------------------------
/*!
 * \brief Blue accessor
 */
// ----------------------------------------------------------------------

int SRGBColor::blue() const
{
  return itsBlue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Alpha accessor
 */
// ----------------------------------------------------------------------

int SRGBColor::alpha() const
{
  return itsAlpha;
}

} // namespace woml
