// ======================================================================
/*!
 * \brief woml::GraphicSymbol
 */
// ======================================================================

#include "GraphicSymbol.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

GraphicSymbol::GraphicSymbol()
  : itsURIs()
  , itsScaleFactor(1.0)
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the scale factor
 */
// ----------------------------------------------------------------------

void GraphicSymbol::scaleFactor(double theFactor)
{
  itsScaleFactor = theFactor;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add an image source
 */
// ----------------------------------------------------------------------

void GraphicSymbol::addURI(const std::string & theURI)
{
  itsURIs.push_back(theURI);
}

// ----------------------------------------------------------------------
/*!
 * \brief Get the scale factor
 */
// ----------------------------------------------------------------------

double GraphicSymbol::scaleFactor() const
{
  return itsScaleFactor;
}

// ----------------------------------------------------------------------
/*!
 * \brief Get the URI list
 */
// ----------------------------------------------------------------------

const URIList & GraphicSymbol::URIs() const
{
  return itsURIs;
}


} // namespace woml
