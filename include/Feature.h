// ======================================================================
/*!
 * \brief woml::Feature
 */
// ======================================================================

#ifndef WOML_FEATURE_H
#define WOML_FEATURE_H

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/shared_ptr.hpp>

namespace woml
{
  class FeatureVisitor;

  class Feature
  {
  public:
	virtual ~Feature() {}
	Feature();
	virtual void visit(FeatureVisitor & theVisitor) const = 0;
	void validTime(const boost::posix_time::time_period & theTime);
	const boost::posix_time::time_period & validTime() const;

  private:

	boost::posix_time::time_period itsValidTime;

  }; // class Feature

} // namespace woml

#endif // WOML_FEATURE_H
