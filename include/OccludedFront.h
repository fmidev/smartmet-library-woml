// ======================================================================
/*!
 * \brief woml::OccludedFront
 */
// ======================================================================

#ifndef WOML_OCCLUDEDFRONT_H
#define WOML_OCCLUDEDFRONT_H

#include "AbstractLineObject.h"

namespace woml
{
  class OccludedFront : public AbstractLineObject
  {
  public:
	virtual void visit(FeatureVisitor & theVisitor) const;

	void stationary(bool theStationary);
	bool stationary() const;

  private:
	bool itsStationary;

  }; // class OccludedFront

} // namespace woml

#endif // WOML_OCCLUDEDFRONT_H
