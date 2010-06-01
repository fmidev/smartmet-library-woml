// ======================================================================
/*!
 * \brief woml::SharedConnectionPoints
 */
// ======================================================================

#ifndef WOML_SHAREDCONNECTIONPOINTS_H
#define WOML_SHAREDCONNECTIONPOINTS_H

#include "Point.h"
#include <map>
#include <string>

namespace woml
{
  typedef std::map<std::string,Point> SharedConnectionPoints;

}

#endif // WOML_SHAREDCONNECTIONPOINTS_H

