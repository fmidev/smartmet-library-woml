// ======================================================================
/*!
 * \brief woml::DataSource
 */
// ======================================================================

#ifndef WOML_DATASOURCE_H
#define WOML_DATASOURCE_H

#include "NumericalModelRun.h"
#include <boost/optional.hpp>

namespace woml
{
  class DataSource
  {
  public:

	void numericalModelRun(const NumericalModelRun & theRun)
	{ itsNumericalModelRun = theRun; }

	const boost::optional<NumericalModelRun> & numericalModelRun() const
	{ return itsNumericalModelRun; }
	
  private:

	boost::optional<NumericalModelRun> itsNumericalModelRun;

  }; // class DataSource
}

#endif // WOML_DATASOURCE_H
