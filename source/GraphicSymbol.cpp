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
  : itsImages()
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

void GraphicSymbol::addImage(const std::string & theImage)
{
  itsImages.push_back(theImage);
}


} // namespace woml
