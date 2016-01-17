// ======================================================================
/*!
 * \brief woml::MeteorologicalSymbol
 */
// ======================================================================

#ifndef WOML_METEOROLOGICAL_SYMBOL_H
#define WOML_METEOROLOGICAL_SYMBOL_H

#include <list>
#include <string>

namespace woml
{
class MeteorologicalSymbol
{
 public:
  MeteorologicalSymbol();

  typedef std::list<std::pair<std::string, std::pair<std::string, std::string> > >
      definitionReferenceList;
  void addDefinitionReference(const std::string& theScheme,
                              const std::string& theDefinitionReference);
  typedef definitionReferenceList::const_iterator DefinitionReferences_const_iterator;
  DefinitionReferences_const_iterator DefinitionReferences_begin() const;
  DefinitionReferences_const_iterator DefinitionReferences_end() const;
  static std::string symbolDefinition(const DefinitionReferences_const_iterator& it,
                                      std::string& theSymbolCode);

  typedef std::list<std::pair<std::string, std::string> > localizedSymbolNameList;
  void addLocalizedSymbolName(const std::string& theLanguage,
                              const std::string& theLocalizedSymbolName);
  typedef localizedSymbolNameList::const_iterator LocalizedSymbolNames_const_iterator;
  LocalizedSymbolNames_const_iterator LocalizedSymbolNames_begin() const;
  LocalizedSymbolNames_const_iterator LocalizedSymbolNames_end() const;

 private:
  definitionReferenceList itsDefinitionReferences;
  localizedSymbolNameList itsLocalizedSymbolNames;

};  // class MeteorologicalSymbol
}  // namespace woml

#endif  // WOML_METEOROLOGICAL_SYMBOL_H
