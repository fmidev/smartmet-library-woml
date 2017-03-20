// ======================================================================
/*!
 * \brief woml::DataSource
 */
// ======================================================================

#pragma once

#include "NumericalModelRun.h"
#include <boost/optional.hpp>

namespace woml
{
class DataSource
{
 public:
  void numericalModelRun(const boost::optional<NumericalModelRun>& theRun)
  {
    itsNumericalModelRun = theRun;
  }

  const boost::optional<NumericalModelRun>& numericalModelRun() const
  {
    return itsNumericalModelRun;
  }

 private:
  boost::optional<NumericalModelRun> itsNumericalModelRun;

};  // class DataSource
}

