#include "view/gxViewUnit.h"
#include <sstream>

gxString gxViewUnit::GetLabelOfPixel(const gxPix aPixel)
{
  return GetLabelOfUnit(PixelToUnit(aPixel));
}

gxString gxViewUnit::GetLabelOfUnit(const int aUnit)
{
  return gxString::Format(_T("%i"), aUnit); 
}


int gxPixelUnit::PixelToUnit(const gxPix aPixel)
{
  return aPixel;
}

gxPix gxPixelUnit::UnitToPixel(const int aUnit)
{
  return aUnit;
}


int gxRationalViewUnit::PixelToUnit(const gxPix aPixel)
{
  return gxFloor(aPixel * mPixelsPerUnit);
}

gxPix gxRationalViewUnit::UnitToPixel(const int aUnit)
{
  return gxFloor(aUnit / mPixelsPerUnit);
}