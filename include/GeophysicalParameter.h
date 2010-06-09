// ======================================================================
/*!
 * \brief woml::GeophysicalParameter
 *
 * \note We intentionally disregard the schema, and expect to find
 *       a reference to a fmi parameter number schema. If we do not,
 *       the parameter number is set to -1.
 */
// ======================================================================

#ifndef WOML_GEOPHYSICALPARAMETER_H
#define WOML_GEOPHYSICALPARAMETER_H

namespace woml
{
  class GeophysicalParameter
  {
  public:
	GeophysicalParameter(int theNumber) : itsNumber(theNumber) {}
	GeophysicalParameter() : itsNumber(-1) {}
	int number() const { return itsNumber; }

  private:
	int itsNumber;

  }; // class GeophysicalParameter
} // namespace woml

#endif // WOML_GEOPHYSICALPARAMETER_H
