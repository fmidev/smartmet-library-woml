// ======================================================================
/*!
 * \brief woml::CloudType
 */
// ======================================================================

#ifndef WOML_CLOUDTYPE_H
#define WOML_CLOUDTYPE_H

#include <string>

namespace woml
{
  enum CloudType
	{
	  CI,
	  CC,
	  CS,
	  AC,
	  AS,
	  NS,
	  SC,
	  ST,
	  CU,
	  CB,
	  UNKNOWN
	};

  CloudType parseCloudType(const std::string & theName);

} // namespace woml

#endif // WOML_CLOUDTYPE_H
