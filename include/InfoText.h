// ======================================================================
/*!
 * \brief woml::InfoText
 */
// ======================================================================

#ifndef WOML_INFOTEXT_H
#define WOML_INFOTEXT_H

#include "Feature.h"
#include "FeatureVisitor.h"
#include <map>

namespace woml
{
  class InfoText : public Feature
  {
  public:
	InfoText(const std::string & theName,const MeteorologicalObjectInfo & theLangTexts);

	virtual void visit(FeatureVisitor & theVisitor) const;

	const std::string & name() const;

  private:

	std::string itsName;

  }; // class InfoText

} // namespace woml

#endif // WOML_INFOTEXT_H
