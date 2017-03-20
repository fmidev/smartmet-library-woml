// ======================================================================
/*!
 * \brief woml::NumericalModelRun
 */
// ======================================================================

#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace woml
{
class NumericalModelRun
{
 public:
  NumericalModelRun(const std::string& theName,
                    const std::string& theSpecifier,
                    const boost::posix_time::ptime& theAnalysisTime)
      : itsName(theName), itsSpecifier(theSpecifier), itsAnalysisTime(theAnalysisTime)
  {
  }

  const std::string& name() const { return itsName; }
  const std::string& specifier() const { return itsSpecifier; }
  const boost::posix_time::ptime& analysisTime() const { return itsAnalysisTime; }
 private:
  NumericalModelRun();
  std::string itsName;
  std::string itsSpecifier;
  boost::posix_time::ptime itsAnalysisTime;

};  // NumericalModelRun
}

