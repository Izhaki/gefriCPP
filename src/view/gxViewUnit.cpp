#include "view/gxViewUnit.h"
#include <sstream>

std::string gxViewUnit::GetLabelOfPixel(const int aPixel)
{
  return GetLabelOfUnit(PixelToUnit(aPixel));
}

std::string gxViewUnit::GetLabelOfUnit(const int aUnit)
{
  std::string result;
  std::stringstream out;
  out << aUnit;
  result = out.str();
  return result; 
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