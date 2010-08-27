// ======================================================================
/*!
 * \brief woml::NumericalModelRun
 */
// ======================================================================

#ifndef WOML_NUMERICALMODELRUN_H
#define WOML_NUMERICALMODELRUN_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace woml
{
  class NumericalModelRun
  {
  public:
	NumericalModelRun(const std::string & theName,
					  const boost::posix_time::ptime & theOriginTime)
	  : itsName(theName)
	  , itsOriginTime(theOriginTime)
	{
	}

	const std::string & name() const
	{ return itsName; }

	const boost::posix_time::ptime & originTime() const
	{ return itsOriginTime; }

  private:
	NumericalModelRun();
	std::string itsName;
	boost::posix_time::ptime itsOriginTime;

  }; // NumericalModelRun
}

#endif // WOML_NUMERICALMODELRUN_H
