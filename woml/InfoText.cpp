// ======================================================================
/*!
 * \brief class woml::InfoText
 */
// ======================================================================

#include "InfoText.h"
#include "FeatureVisitor.h"

namespace woml
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

InfoText::InfoText(const std::string& theName, const MeteorologicalObjectInfo& theLangTexts)
    : itsName(theName)
{
  addShortInfos(theLangTexts);
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void InfoText::visit(FeatureVisitor& theVisitor) const { theVisitor.visit(*this); }
// ----------------------------------------------------------------------
/*!
 * \brief Name accessor
 */
// ----------------------------------------------------------------------

const std::string& InfoText::name() const { return itsName; }
}  // namespace woml
