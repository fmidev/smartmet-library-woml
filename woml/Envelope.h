// ======================================================================
/*!
 * \brief woml::Envelope
 */
// ======================================================================

#ifndef WOML_ENVELOPE_H
#define WOML_ENVELOPE_H

#include "Point.h"
#include <string>

namespace woml
{
class Envelope
{
 public:
  Envelope();
  Envelope(const boost::optional<Point>& theRect,
           std::string theSrsName,
           std::string theSrsDimension);
  Envelope(const boost::optional<Rect>& theRect,
           std::string theSrsName,
           std::string theSrsDimension);
  bool bounded() const;
  const boost::optional<Point>& point() const;
  const boost::optional<Point> lowerCorner() const;
  const boost::optional<Point> upperCorner() const;
  const std::string& srsName() const;
  const std::string& srsDimension() const;

 private:
  bool itsBounded;
  boost::optional<Point> itsPoint;
  boost::optional<Rect> itsRect;
  std::string itsSrsName;
  std::string itsSrsDimension;

};  // class Envelope
}  // namespace woml

#endif  // WOML_ENVELOPE_H
