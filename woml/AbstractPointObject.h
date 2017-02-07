// ======================================================================
/*!
 * \brief woml::AbstractPointObject
 */
// ======================================================================

#ifndef WOML_ABSTRACTPOINTOBJECT_H
#define WOML_ABSTRACTPOINTOBJECT_H

#include "Feature.h"
#include "Envelope.h"
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

#endif  // WOML_ABSTRACTPOINTOBJECT_H
