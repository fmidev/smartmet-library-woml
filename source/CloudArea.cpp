// ======================================================================
/*!
 * \brief class woml::CloudArea
 */
// ======================================================================

#include "CloudArea.h"
#include "FeatureVisitor.h"

namespace woml
{

// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 */
// ----------------------------------------------------------------------

CloudArea::CloudArea()
  : AbstractSurfaceObject()
  , itsCloudType(UNKNOWN)
  , itsCloudTypeName("")
  , itsCloudCoverPercent()
  , itsCloudCoverEighths()
{
}

// ----------------------------------------------------------------------
/*!
 * \brief Visit handler
 */
// ----------------------------------------------------------------------

void CloudArea::visit(FeatureVisitor & theVisitor) const
{
  theVisitor.visit(*this);
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the cloud type
 */
// ----------------------------------------------------------------------

void CloudArea::cloudType(CloudType theCloudType,const std::string & theCloudTypeName)
{
  itsCloudType = theCloudType;
  itsCloudTypeName = theCloudTypeName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the cloud type
 */
// ----------------------------------------------------------------------

CloudType CloudArea::cloudType() const
{
  return itsCloudType;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the cloud type name
 */
// ----------------------------------------------------------------------

const std::string & CloudArea::cloudTypeName() const
{
  return itsCloudTypeName;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the cloud cover percent
 */
// ----------------------------------------------------------------------

void CloudArea::cloudCoverPercent(const boost::optional<double> & theCloudCoverPercent)
{
  itsCloudCoverPercent = theCloudCoverPercent;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the cloud cover percent
 */
// ----------------------------------------------------------------------

const boost::optional<double> & CloudArea::cloudCoverPercent() const
{
  return itsCloudCoverPercent;
}

// ----------------------------------------------------------------------
/*!
 * \brief Set the cloud cover eighths
 */
// ----------------------------------------------------------------------

void CloudArea::cloudCoverEighths(const std::string & theCloudCoverEighths)
{
  itsCloudCoverEighths = theCloudCoverEighths;
}

// ----------------------------------------------------------------------
/*!
 * \brief Return the cloud cover eighths
 */
// ----------------------------------------------------------------------

const std::string & CloudArea::cloudCoverEighths() const
{
  return itsCloudCoverEighths;
}

} // namespace woml
