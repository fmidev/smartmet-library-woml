// ======================================================================
/*!
 * \brief woml::CloudType
 */
// ======================================================================

#pragma once

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

CloudType parseCloudType(const std::string& theName);

}  // namespace woml

