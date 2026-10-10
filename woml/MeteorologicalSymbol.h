// ======================================================================
/*!
 * \brief woml::MeteorologicalSymbol
 */
// ======================================================================

#pragma once

#include <list>
#include <string>

namespace woml
{
class MeteorologicalSymbol
{
 public:
  MeteorologicalSymbol();

  using definitionReferenceList =
      std::list<std::pair<std::string, std::pair<std::string, std::string> > >;
  void addDefinitionReference(const std::string& theScheme,
                              const std::string& theDefinitionReference);
  using DefinitionReferences_const_iterator = definitionReferenceList::const_iterator;
  DefinitionReferences_const_iterator DefinitionReferences_begin() const;
  DefinitionReferences_const_iterator DefinitionReferences_end() const;
  static std::string symbolDefinition(const DefinitionReferences_const_iterator& it,
                                      std::string& theSymbolCode);

  using localizedSymbolNameList = std::list<std::pair<std::string, std::string> >;
  void addLocalizedSymbolName(const std::string& theLanguage,
                              const std::string& theLocalizedSymbolName);
  using LocalizedSymbolNames_const_iterator = localizedSymbolNameList::const_iterator;
  LocalizedSymbolNames_const_iterator LocalizedSymbolNames_begin() const;
  LocalizedSymbolNames_const_iterator LocalizedSymbolNames_end() const;

 private:
  definitionReferenceList itsDefinitionReferences;
  localizedSymbolNameList itsLocalizedSymbolNames;

};  // class MeteorologicalSymbol
}  // namespace woml
