#ifndef gxViewUnit_h
#define gxViewUnit_h

#include <string>

/**
 * @brief A class to convert between pixels and the unit used in the view.
 * 
 * Views can display data that relates to various units, like centimeters,
 * inches, or in some cases time (minutes:seconds:milliseconds), timecode,
 * bar:beats, and so on.
 * 
 * This class helps converting between a specific unit value to pixels
 * and vice-versa. It also in charge of providing the right label for a
 * unit.
 * 
 * Units can be broken down into 3 types:
 * - 1:1 units - like pixels, or in some cases samples.
 * - Rational units - if the DPI of the display is 2.5, the pixel-per-inch
 * ratio will be 2.5.
 * - Varying - some units might not have a fixed pixel-per-unit ratio.
 * For example, a bar:beat unit in a view based on samples, might have bars
 * of varying samples length (due to varying tempo).
 */
class gxViewUnit
{
public:
  /**
   * @brief Coverts from a pixel value to unit value.
   * @param aPixel The pixel value to convert.
   * @return The unit value of the provided pixel.
   */
  virtual int PixelToUnit(const int aPixel) = 0;

  /**
   * @brief Coverts from a unit value to pixel value.
   * @param aUnit The unit value to convert.
   * @return The unit value of the provided unit.
   */
  virtual int UnitToPixel(const int aUnit) = 0;
  
  /**
   * @brief Returns the label of a given pixel.
   * @param aPixel The pixel value.
   * @return The label for that pixel value.
   */
  virtual std::string GetLabelOfPixel(const int aPixel);

  /**
   * @brief Returns the label of a given unit.
   * @param aUnit The unit value.
   * @return The label for the given unit value.
   */
  virtual std::string GetLabelOfUnit(const int aUnit);
};

/**
 * @brief An implementation of pixels unit.
 */
class gxPixelUnit : public gxViewUnit
{
  virtual int PixelToUnit(const int aPixel);
  virtual int UnitToPixel(const int aUnit);
};

/**
 * @brief An implementation of view unit that has a fixed ratio between
 * pixels and units (other than 1:1).
 * 
 * Like centimeters, inches etc.
 */
class gxRationalViewUnit : public gxViewUnit
{
public:
  gxRationalViewUnit(double aPixelsPerUnit)
  : mPixelsPerUnit(aPixelsPerUnit)
  { }

  virtual int PixelToUnit(const int aPixel);
  virtual int UnitToPixel(const int aUnit);
protected:
  double mPixelsPerUnit;
};

#endif // gxViewUnit_h