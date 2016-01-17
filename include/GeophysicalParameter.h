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

#include <string>

namespace woml
{
class GeophysicalParameter
{
 public:
  GeophysicalParameter(const std::string& theName, int theNumber)
      : itsName(theName), itsNumber(theNumber)
  {
  }

  GeophysicalParameter() : itsName(""), itsNumber(-1) {}
  const std::string& name() const { return itsName; }
  int number() const { return itsNumber; }
 private:
  std::string itsName;
  int itsNumber;

};  // class GeophysicalParameter
}  // namespace woml

#endif  // WOML_GEOPHYSICALPARAMETER_H
