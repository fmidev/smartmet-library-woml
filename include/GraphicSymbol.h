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
  typedef std::list<std::string> URIList;

  class GraphicSymbol : public MeteorologicalSymbol
  {
  public:
	GraphicSymbol();
	void scaleFactor(double theFactor);
	void addURI(const std::string & theURI);

	double scaleFactor() const;
	const URIList & URIs() const;

  private:
	URIList itsURIs;
	double itsScaleFactor;

  }; // class GraphicSymbol
} // namespace woml

#endif // WOML_GRAPHICSYMBOL_H
