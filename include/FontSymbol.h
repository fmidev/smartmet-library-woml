// ======================================================================
/*!
 * \brief woml::FontSymbol
 */
// ======================================================================

#ifndef WOML_FONTSYMBOL_H
#define WOML_FONTSYMBOL_H

#include "MeteorologicalSymbol.h"
#include "SRGBColor.h"
#include <string>

namespace woml
{
  class FontSymbol : public MeteorologicalSymbol
  {
  public:
	FontSymbol(const std::string & theFontName,
			   int theSymbolIndex,
			   const SRGBColor & theColor);

	const std::string & fontName() const;
	int symbolIndex() const;
	const SRGBColor & color() const;

  private:
	FontSymbol();
	std::string itsFontName;
	int itsSymbolIndex;
	SRGBColor itsColor;


  }; // class FontSymbol
} // namespace woml

#endif // WOML_FONTSYMBOL_H
