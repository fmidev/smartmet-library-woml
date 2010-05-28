// ======================================================================
/*!
 * \brief WomlParser
 */
// ======================================================================

#ifndef WOML_PARSER_H
#define WOML_PARSER_H

#include "Weather.h"
#include <boost/filesystem/path.hpp>

namespace woml
{
  class Woml;

  Weather parse(const boost::filesystem::path & thePath);

} // namespace woml

#endif // WOML_PARSER_H
