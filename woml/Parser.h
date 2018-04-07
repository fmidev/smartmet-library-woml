// ======================================================================
/*!
 * \brief WomlParser
 */
// ======================================================================

#pragma once

#include "Weather.h"
#include <boost/filesystem/path.hpp>

namespace woml
{
class Woml;

Weather parse(const boost::filesystem::path& thePath,
              woml::documentType docType,
              bool strict = true);

}  // namespace woml
