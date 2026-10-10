// ======================================================================
/*!
 * \brief woml::InfoText
 */
// ======================================================================

#pragma once

#include "Feature.h"
#include "FeatureVisitor.h"
#include <map>

namespace woml
{
class InfoText : public Feature
{
 public:
  InfoText(const std::string& theName, const MeteorologicalObjectInfo& theLangTexts);

  void visit(FeatureVisitor& theVisitor) const override;

  const std::string& name() const;

 private:
  std::string itsName;

};  // class InfoText

}  // namespace woml
