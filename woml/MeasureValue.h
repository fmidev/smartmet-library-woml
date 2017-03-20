// ======================================================================
/*!
 * \brief woml::MeasureValue
 */
// ======================================================================

#pragma once

#include <string>
#include <boost/optional.hpp>

namespace woml
{
class MeasureValue
{
 public:
  virtual ~MeasureValue() {}
  virtual const std::string& value() const = 0;
  virtual const std::string& unit() const = 0;

};  // class MeasureValue

class CategoryValueMeasure : public MeasureValue
{
 public:
  CategoryValueMeasure();
  CategoryValueMeasure(const std::string& theCategory, const std::string& theCodebase);

  const std::string& value() const;  // <==> category
  const std::string& unit() const;   // <==> codebase
  const std::string& category() const;
  const std::string& codebase() const;

  void groupNumber(unsigned int group);
  unsigned int groupNumber() const;

 private:
  std::string itsCategory;
  std::string itsCodebase;
  unsigned int itsGroupNumber;

};  // class CategoryValueMeasure

class FlowDirectionMeasure : public MeasureValue
{
 public:
  FlowDirectionMeasure();
  FlowDirectionMeasure(const std::string& theCompassPoint, const std::string& theDirectionVector);

  const std::string& value() const;  // <==> compassPoint
  const std::string& unit() const;   // <==> ""
  const std::string& compassPoint() const;
  const std::string& directionVector() const;

 private:
  std::string itsCompassPoint;
  std::string itsDirectionVector;
  std::string itsUnit;

};  // class FlowDirectionMeasure

class NumericalSingleValueMeasure : public MeasureValue
{
 public:
  NumericalSingleValueMeasure();
  NumericalSingleValueMeasure(double theValue,
                              const std::string& theStringValue,
                              const std::string& theUnit);

  const std::string& value() const;
  const std::string& unit() const;
  double numericValue() const;

 private:
  double itsValue;
  std::string itsStringValue;
  std::string itsUnit;

};  // class NumericalSingleValueMeasure

class NumericalValueRangeMeasure : public MeasureValue
{
 public:
  NumericalValueRangeMeasure();
  NumericalValueRangeMeasure(const NumericalSingleValueMeasure& theLowerLimit,
                             const NumericalSingleValueMeasure& theUpperLimit);

  const std::string& value() const;
  const std::string& unit() const;

  const NumericalSingleValueMeasure& lowerLimit() const;
  const NumericalSingleValueMeasure& upperLimit() const;

 private:
  NumericalSingleValueMeasure itsLowerLimit;
  NumericalSingleValueMeasure itsUpperLimit;
  std::string itsStringValue;

};  // class NumericalValueRangeMeasure
}  // namespace woml

