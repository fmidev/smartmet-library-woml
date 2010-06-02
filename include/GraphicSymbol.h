// ======================================================================
/*!
 * \brief woml::GraphicSymbol
 */
// ======================================================================

#ifndef WOML_GRAPHICSYMBOL_H
#define WOML_GRAPHICSYMBOL_H

#include "MeteorologicalSymbol.h"
#include <list>
#include <string>

namespace woml
{
  class GraphicSymbol : public MeteorologicalSymbol
  {
  public:
	GraphicSymbol();
	void scaleFactor(double theFactor);
	void addImage(const std::string & theImage);

  private:
	std::list<std::string> itsImages;
	double itsScaleFactor;

  }; // class GraphicSymbol
} // namespace woml

#endif // WOML_GRAPHICSYMBOL_H
