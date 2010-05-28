// ======================================================================
/*!
 * \brief woml::SRGBColor
 */
// ======================================================================

#ifndef WOML_SRGBCOLOR_H
#define WOML_SRGBCOLOR_H

namespace woml
{
  class SRGBColor
  {
  public:
	SRGBColor(int theRed, int theGreen, int theBlue, int theAlpha);
	int red() const;
	int green() const;
	int blue() const;
	int alpha() const;

  private:
	SRGBColor();

	int itsRed;		// all 0-255 inclusive
	int itsGreen;
	int itsBlue;
	int itsAlpha;

  }; // class SRGBColor
} // namespace woml

#endif // WOML_SRGBCOLOR_H
