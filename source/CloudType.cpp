// ======================================================================
/*!
 * \brief woml::CloudType
 */
// ======================================================================

#include "CloudType.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Convert cloud type name to enum
 */
// ----------------------------------------------------------------------

CloudType parseCloudType(const std::string & theName)
{
  if(theName == "CI")
	return CI;
  else if(theName == "CC")
	return CC;
  else if(theName == "CS")
	return CS;
  else if(theName == "AC")
	return AC;
  else if(theName == "AS")
	return AS;
  else if(theName == "NS")
	return NS;
  else if(theName == "SC")
	return SC;
  else if(theName == "ST")
	return ST;
  else if(theName == "CU")
	return CU;
  else if(theName == "CB")
	return CB;
  else return UNKNOWN;
}

} // namespace woml
