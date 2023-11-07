// ======================================================================
/*!
 * \brief woml::NumericalModelRun
 */
// ======================================================================

#pragma once

#include <macgyver/DateTime.h>
#include <string>

namespace woml
{
class NumericalModelRun
{
 public:
  NumericalModelRun(const std::string& theName,
                    const std::string& theSpecifier,
                    const Fmi::DateTime& theAnalysisTime)
      : itsName(theName), itsSpecifier(theSpecifier), itsAnalysisTime(theAnalysisTime)
  {
  }

  const std::string& name() const { return itsName; }
  const std::string& specifier() const { return itsSpecifier; }
  const Fmi::DateTime& analysisTime() const { return itsAnalysisTime; }

 private:
  NumericalModelRun();
  std::string itsName;
  std::string itsSpecifier;
  Fmi::DateTime itsAnalysisTime;

};  // NumericalModelRun
}  // namespace woml
