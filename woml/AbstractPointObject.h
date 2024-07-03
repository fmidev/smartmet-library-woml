// ======================================================================
/*!
 * \brief woml::AbstractPointObject
 */
// ======================================================================

#pragma once

#include "Envelope.h"
#include "Feature.h"
#include "Point.h"
#include <string>

namespace woml
{
class AbstractPointObject : public Feature
{
 public:
  virtual ~AbstractPointObject() {}
  void envelope(const std::optional<Envelope>& theEnvelope);
  void point(const std::optional<Point>& thePoint);
  const std::optional<Point>& point() const;

 protected:
  std::optional<Envelope> itsBoundedBy;
  std::optional<Point> itsPoint;

};  // class AbstractPointObject

}  // namespace woml
