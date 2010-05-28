// ======================================================================
/*!
 * \brief woml::FontSymbol
 */
// ======================================================================

#include "FontSymbol.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

FontSymbol::FontSymbol(const std::string & theFontName,
					   int theSymbolIndex,
					   const SRGBColor & theColor)
  : itsFontName(theFontName)
  , itsSymbolIndex(theSymbolIndex)
  , itsColor(theColor)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Font accessor
 */
// ----------------------------------------------------------------------

const std::string & FontSymbol::fontName() const
{
  return itsFontName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Symbol index accessor
 */
// ----------------------------------------------------------------------

int FontSymbol::symbolIndex() const
{
  return itsSymbolIndex;
}

// ----------------------------------------------------------------------
/*!
 * \brief Color accessor
 */
// ----------------------------------------------------------------------

const SRGBColor & FontSymbol::color() const
{
  return itsColor;
}

} // namespace woml
