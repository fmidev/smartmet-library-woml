// ======================================================================
/*!
 * \brief woml::MeteorologicalSymbol
 */
// ======================================================================

#include "MeteorologicalSymbol.h"
#include <boost/algorithm/string.hpp>
#include <stdexcept>
#include <vector>

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol::MeteorologicalSymbol() : itsDefinitionReferences(), itsLocalizedSymbolNames()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a definition reference
 */
// ----------------------------------------------------------------------

void MeteorologicalSymbol::addDefinitionReference(const std::string& theScheme,
                                                  const std::string& theDefinitionReference)
{
  // definitionReference: symbolTypeName@symbolCode
  //
  std::vector<std::string> cols;
  boost::split(cols, theDefinitionReference, boost::is_any_of("@"));

  if (cols.size() == 2)
  {
    boost::trim(cols[0]);
    boost::trim(cols[1]);
  }

  if ((cols.size() != 2) || (cols[0] == "") || (cols[1] == ""))
    throw std::runtime_error("Invalid definition reference: (" + theScheme + ") " +
                             theDefinitionReference);

  itsDefinitionReferences.push_back(make_pair(theScheme, make_pair(cols[0], cols[1])));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the definition references
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol::DefinitionReferences_const_iterator
MeteorologicalSymbol::DefinitionReferences_begin() const
{
  return itsDefinitionReferences.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the definition references
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol::DefinitionReferences_const_iterator
MeteorologicalSymbol::DefinitionReferences_end() const
{
  return itsDefinitionReferences.end();
}

// ----------------------------------------------------------------------
/*!
 * \brief Return symbol definition (class and code)
 */
// ----------------------------------------------------------------------

std::string MeteorologicalSymbol::symbolDefinition(const DefinitionReferences_const_iterator& it,
                                                   std::string& theSymbolCode)
{
  // definitionReference: symbolTypeName@symbolCode
  //

  std::pair<std::string, std::string> definitionReference(it->second);
  theSymbolCode = definitionReference.second;

  return definitionReference.first;
}

// ----------------------------------------------------------------------
/*!
 * \brief Add a localized symbol name
 */
// ----------------------------------------------------------------------

void MeteorologicalSymbol::addLocalizedSymbolName(const std::string& theLanguage,
                                                  const std::string& theLocalizedSymbolName)
{
  if ((theLanguage.length() > 0) && (theLocalizedSymbolName.length() > 0))
    itsLocalizedSymbolNames.push_back(make_pair(theLanguage, theLocalizedSymbolName));
}

// ----------------------------------------------------------------------
/*!
 * \brief Iterator over the localized symbol names
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol::LocalizedSymbolNames_const_iterator
MeteorologicalSymbol::LocalizedSymbolNames_begin() const
{
  return itsLocalizedSymbolNames.begin();
}

// ----------------------------------------------------------------------
/*!
 * \brief End iterator over the localized symbol names
 */
// ----------------------------------------------------------------------

MeteorologicalSymbol::LocalizedSymbolNames_const_iterator
MeteorologicalSymbol::LocalizedSymbolNames_end() const
{
  return itsLocalizedSymbolNames.end();
}

}  // namespace woml
