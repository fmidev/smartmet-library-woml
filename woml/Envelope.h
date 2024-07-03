// ======================================================================
/*!
 * \brief woml::Envelope
 */
// ======================================================================

#pragma once

#include "Point.h"
#include <string>

namespace woml
{
class Envelope
{
 public:
  Envelope();
  Envelope(const std::optional<Point>& theRect,
           std::string theSrsName,
           std::string theSrsDimension);
  Envelope(const std::optional<Rect>& theRect,
           std::string theSrsName,
           std::string theSrsDimension);
  bool bounded() const;
  const std::optional<Point>& point() const;
  const std::optional<Point> lowerCorner() const;
  const std::optional<Point> upperCorner() const;
  const std::string& srsName() const;
  const std::string& srsDimension() const;

 private:
  bool itsBounded;
  std::optional<Point> itsPoint;
  std::optional<Rect> itsRect;
  std::string itsSrsName;
  std::string itsSrsDimension;

};  // class Envelope
}  // namespace woml
