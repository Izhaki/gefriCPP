#include "view/gxDcPainter.h"
#include <wx/log.h>
#include "core/gxLog.h"

gxDcPainter::gxDcPainter(gxPaintDC *aDc, gxRects const &aDamagedRects)
{
  mDc = aDc;
  mDamagedRects = aDamagedRects;
}

gxRect gxDcPainter::GetClipRect() const
{
  return mDc->GetClippingBox();
}

bool gxDcPainter::NeedsPainting(gxRect const &aRect)
{
  // Transform the rect
  gxRect iTransformedRect(aRect);
  Transform(iTransformedRect);

  // Get the cliping rect
  gxRect iClipRect = GetClipRect();

  // If the rect is not within the clip rect return false
  if (!iClipRect.Intersects(iTransformedRect))
    return false;

  
  // If the rect intersects with any of the damaged rects return true
  for( unsigned int i = 0; i < mDamagedRects.size(); i++)
  {
    if (mDamagedRects[i].Intersects(iTransformedRect))
      return true;
  }

  return false;
}

void gxDcPainter::IntersectClipArea(gxRect const &aRect)
{
  mDc->SetClippingRegion(aRect);
}

void gxDcPainter::SetAbsoluteClipArea(gxRect const &aRect)
{
  mDc->DestroyClippingRegion();
  mDc->SetClippingRegion(aRect);
}

void gxDcPainter::DrawRectangle(int x, int y, int w, int h)
{
  gxRect iRect(x, y, w, h);
  Transform(iRect);
  mDc->DrawRectangle(iRect);
}

void gxDcPainter::DrawRectangle(gxRect const &aRect)
{
  gxRect iRect(aRect);
  Transform(iRect);
  mDc->DrawRectangle(iRect);
}

void gxDcPainter::DrawLine(int x1, int y1, int x2, int y2, bool isHorizontal)
{
  gxPoint iFrom = isHorizontal ? gxPoint(x1, y1) : gxPoint(y1, x1);
  gxPoint iTo = isHorizontal ? gxPoint(x2, y2) : gxPoint(y2, x2);
  Transform(iFrom);
  Transform(iTo);
  mDc->DrawLine(iFrom.x, iFrom.y, iTo.x, iTo.y);
}

void gxDcPainter::DrawText(std::string aText, int x, int y)
{
  gxPoint iPoint(x, y);
  Transform(iPoint);
  mDc->DrawText(wxString(aText.c_str(), wxConvUTF8), iPoint.x , iPoint.y);
}

void gxDcPainter::DrawText(std::string aText, int x, int y, int aPadX, int aPadY, bool isHorizontal)
{
  gxPoint iPoint = isHorizontal ? gxPoint(x, y) : gxPoint(y, x);

  Transform(iPoint);
  
  iPoint.x = iPoint.x + aPadX;
  iPoint.y = iPoint.y + aPadY;

  if (isHorizontal)
  {
    mDc->DrawText(wxString(aText.c_str(), wxConvUTF8), iPoint.x , iPoint.y);
  } else {
    // Text rotation is done with the top left point as origion,
    // so make the old top right the new top left
    iPoint.y = iPoint.y + GetTextSize(aText).X;
    mDc->DrawRotatedText(wxString(aText.c_str(), wxConvUTF8), iPoint.x, iPoint.y, 90);
  }
}

void gxDcPainter::DrawRotatedText(std::string aText, int x, int y, double aAngle)
{
  gxPoint iPoint(x, y);
  Transform(iPoint);
  mDc->DrawRotatedText(wxString(aText.c_str(), wxConvUTF8), iPoint.x + 3, iPoint.y, aAngle);
}

gxSize gxDcPainter::GetTextSize(std::string aText)
{
  wxSize iSize = mDc->GetTextExtent(wxString(aText.c_str(), wxConvUTF8));
  return gxSize(iSize.x, iSize.y);
}

