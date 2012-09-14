// ======================================================================
/*!
 * \brief woml::MeasureValue
 */
// ======================================================================

#include "MeasureValue.h"
#include <boost/lexical_cast.hpp>

namespace woml
{

// ===== CategoryValueMeasure =====
//
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

CategoryValueMeasure::CategoryValueMeasure()
  : itsCategory("")
  , itsCodebase("")
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

CategoryValueMeasure::CategoryValueMeasure(const std::string & theCategory,
										   const std::string & theCodebase)
  : itsCategory(theCategory)
  , itsCodebase(theCodebase)
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Category accessor
 */
// ----------------------------------------------------------------------

const std::string & CategoryValueMeasure::category() const
{
  return itsCategory;
}

// ----------------------------------------------------------------------
/*!
 * \brief Value accessor
 */
// ----------------------------------------------------------------------

const std::string & CategoryValueMeasure::value() const
{
  return category();
}

// ----------------------------------------------------------------------
/*!
 * \brief Codebase accessor
 */
// ----------------------------------------------------------------------

const std::string & CategoryValueMeasure::codebase() const
{
  return itsCodebase;
}

// ----------------------------------------------------------------------
/*!
 * \brief Unit accessor
 */
// ----------------------------------------------------------------------

const std::string & CategoryValueMeasure::unit() const
{
  return codebase();
}

// ===== FlowDirectionMeasure =====
//
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

FlowDirectionMeasure::FlowDirectionMeasure()
  : itsCompassPoint("")
  , itsDirectionVector("")
  , itsUnit("")
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

FlowDirectionMeasure::FlowDirectionMeasure(const std::string & theCompassPoint,const std::string & theDirectionVector)
  : itsCompassPoint(theCompassPoint)
  , itsDirectionVector(theDirectionVector)
  , itsUnit("")
{ }

// ----------------------------------------------------------------------
/*!
 * \brief CompassPoint accessor
 */
// ----------------------------------------------------------------------

const std::string & FlowDirectionMeasure::compassPoint() const
{
  return itsCompassPoint;
}

// ----------------------------------------------------------------------
/*!
 * \brief DirectionVector accessor
 */
// ----------------------------------------------------------------------

const std::string & FlowDirectionMeasure::directionVector() const
{
  return itsDirectionVector;
}

// ----------------------------------------------------------------------
/*!
 * \brief Value accessor
 */
// ----------------------------------------------------------------------

const std::string & FlowDirectionMeasure::value() const
{
  return compassPoint();
}

// ----------------------------------------------------------------------
/*!
 * \brief Unit accessor
 */
// ----------------------------------------------------------------------

const std::string & FlowDirectionMeasure::unit() const
{
  return itsUnit;
}

// ===== NumericalSingleValueMeasure =====
//
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

NumericalSingleValueMeasure::NumericalSingleValueMeasure()
  : itsValue(0.0)
  , itsStringValue("")
  , itsUnit("")
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

NumericalSingleValueMeasure::NumericalSingleValueMeasure(double theValue,const std::string & theStringValue,const std::string & theUnit)
  : itsValue(theValue)
  , itsStringValue(theStringValue)
  , itsUnit(theUnit)
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Numeric value accessor
 */
// ----------------------------------------------------------------------

double NumericalSingleValueMeasure::numericValue() const
{
  return itsValue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Value accessor
 */
// ----------------------------------------------------------------------

const std::string & NumericalSingleValueMeasure::value() const
{
  return itsStringValue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Unit accessor
 */
// ----------------------------------------------------------------------

const std::string & NumericalSingleValueMeasure::unit() const
{
  return itsUnit;
}

// ===== NumericalValueRangeMeasure =====
//
// ----------------------------------------------------------------------
/*!
 * \brief Default constructor
 */
// ----------------------------------------------------------------------

NumericalValueRangeMeasure::NumericalValueRangeMeasure()
  : itsLowerLimit(NumericalSingleValueMeasure())
  , itsUpperLimit(NumericalSingleValueMeasure())
  , itsStringValue("")
{ }

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

NumericalValueRangeMeasure::NumericalValueRangeMeasure(const NumericalSingleValueMeasure & theLowerLimit,
													   const NumericalSingleValueMeasure & theUpperLimit)
  : itsLowerLimit(theLowerLimit)
  , itsUpperLimit(theUpperLimit)
{
	itsStringValue = itsLowerLimit.value() + " " + itsUpperLimit.value();
}

// ----------------------------------------------------------------------
/*!
 * \brief Value accessor
 */
// ----------------------------------------------------------------------

const std::string & NumericalValueRangeMeasure::value() const
{
  return itsStringValue;
}

// ----------------------------------------------------------------------
/*!
 * \brief Unit accessor
 */
// ----------------------------------------------------------------------

const std::string & NumericalValueRangeMeasure::unit() const
{
  return itsLowerLimit.unit();
}

// ----------------------------------------------------------------------
/*!
 * \brief Lower limit accessor
 */
// ----------------------------------------------------------------------

const NumericalSingleValueMeasure & NumericalValueRangeMeasure::lowerLimit() const
{
  return itsLowerLimit;
}

// ----------------------------------------------------------------------
/*!
 * \brief Upper limit accessor
 */
// ----------------------------------------------------------------------

const NumericalSingleValueMeasure & NumericalValueRangeMeasure::upperLimit() const
{
  return itsUpperLimit;
}

} // namespace woml
