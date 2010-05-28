// ======================================================================
/*!
 * \brief WOML parser code
 */
// ======================================================================

#include "Parser.h"
#include "Weather.h"

#include <libxml++/libxml++.h>
#include <libxml++/parsers/textreader.h>

#include <stdexcept>

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Parse a WOML file
 */
// ----------------------------------------------------------------------

Weather parse(const boost::filesystem::path & thePath)
{
  xmlpp::TextReader reader(thePath.file_string());

  Weather weather;

  while(reader.read())
	{
	  std::string name = reader.get_name();
	  if(name == "metobj:WeatherForecast")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  // TODO
		}
	  else if(name == "metobj:meteorologicalanalysis")
		{
		  if(!weather.empty())
			throw std::runtime_error("Multiple meteorological objects in " + thePath.file_string());
		  // TODO
		}
	  else
		throw std::runtime_error("Unexpected tag <"
								 + name
								 + " at top level of "
								 + thePath.file_string());

	}

  return weather;
}



} // namespace woml
