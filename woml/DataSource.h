// ======================================================================
/*!
 * \brief woml::DataSource
 */
// ======================================================================

#pragma once

#include "NumericalModelRun.h"
#include <optional>

namespace woml
{
class DataSource
{
 public:
  void numericalModelRun(const std::optional<NumericalModelRun>& theRun)
  {
    itsNumericalModelRun = theRun;
  }

  const std::optional<NumericalModelRun>& numericalModelRun() const
  {
    return itsNumericalModelRun;
  }

 private:
  std::optional<NumericalModelRun> itsNumericalModelRun;

};  // class DataSource
}  // namespace woml
