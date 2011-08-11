#include "view/gxViewUnit.h"
#include <sstream>

gxString gxViewUnit::GetLabelOfPixel(const int aPixel)
{
  return GetLabelOfUnit(PixelToUnit(aPixel));
}

gxString gxViewUnit::GetLabelOfUnit(const int aUnit)
{
  return gxString::Format(_T("%i"), aUnit); 
}


int gxPixelUnit::PixelToUnit(const int aPixel)
{
  return aPixel;
}

int gxPixelUnit::UnitToPixel(const int aUnit)
{
  return aUnit;
}


int gxRationalViewUnit::PixelToUnit(const int aPixel)
{
  return (int)(aPixel * mPixelsPerUnit);
}

int gxRationalViewUnit::UnitToPixel(const int aUnit)
{
  return (int)(aUnit / mPixelsPerUnit);
}