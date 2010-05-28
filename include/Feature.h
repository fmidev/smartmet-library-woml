// ======================================================================
/*!
 * \brief woml::Feature
 */
// ======================================================================

#ifndef WOML_FEATURE_H
#define WOML_FEATURE_H

#include <boost/shared_ptr.hpp>

namespace woml
{
  class FeatureVisitor;

  class Feature
  {
  public:
	virtual ~Feature() {}
	virtual void visit(FeatureVisitor & theVisitor) const = 0;

  private:

  }; // class Feature

  typedef boost::shared_ptr<Feature> FeaturePtr;

} // namespace woml

#endif // WOML_FEATURE_H
