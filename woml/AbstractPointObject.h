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
  void envelope(const boost::optional<Envelope>& theEnvelope);
  void point(const boost::optional<Point>& thePoint);
  const boost::optional<Point>& point() const;

 protected:
  boost::optional<Envelope> itsBoundedBy;
  boost::optional<Point> itsPoint;

};  // class AbstractPointObject

}  // namespace woml
