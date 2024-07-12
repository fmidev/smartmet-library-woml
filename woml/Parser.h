// ======================================================================
/*!
 * \brief WomlParser
 */
// ======================================================================

#pragma once

#include "Weather.h"
#include <filesystem>

namespace woml
{
class Woml;

Weather parse(const std::filesystem::path& thePath,
              woml::documentType docType,
              bool strict = true);

}  // namespace woml
