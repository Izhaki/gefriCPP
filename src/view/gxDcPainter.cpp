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
  gxRect transformedRect(aRect);
  Transform(transformedRect);

  // Get the cliping rect
  gxRect clipRect = GetClipRect();

  // If the rect is not within the clip rect return false
  if (!clipRect.Intersects(transformedRect))
    return false;

  
  // If the rect intersects with any of the damaged rects return true
  for( unsigned int i = 0; i < mDamagedRects.size(); i++)
  {
    if (mDamagedRects[i].Intersects(transformedRect))
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
  gxRect rect(x, y, w, h);
  Transform(rect);
  mDc->DrawRectangle(rect);
}

void gxDcPainter::DrawLine(int x1, int y1, int x2, int y2, bool isHorizontal)
{
  gxPoint from = isHorizontal ? gxPoint(x1, y1) : gxPoint(y1, x1);
  gxPoint to = isHorizontal ? gxPoint(x2, y2) : gxPoint(y2, x2);
  Transform(from);
  Transform(to);
  mDc->DrawLine(from.x, from.y, to.x, to.y);
}

void gxDcPainter::DrawText(std::string aText, int x, int y)
{
  gxPoint p(x, y);
  Transform(p);
  mDc->DrawText(wxString(aText.c_str(), wxConvUTF8), p.x , p.y);
}

void gxDcPainter::DrawText(std::string aText, int x, int y, int aPadX, int aPadY, bool isHorizontal)
{
  gxPoint p = isHorizontal ? gxPoint(x, y) : gxPoint(y, x);

  Transform(p);
  
  p.x = p.x + aPadX;
  p.y = p.y + aPadY;

  if (isHorizontal)
  {
    mDc->DrawText(wxString(aText.c_str(), wxConvUTF8), p.x , p.y);
  } else {
    // Text rotation is done with the top left point as origion,
    // so make the old top right the new top left
    p.y = p.y + GetTextSize(aText).x;
    mDc->DrawRotatedText(wxString(aText.c_str(), wxConvUTF8), p.x, p.y, 90);
  }
}

void gxDcPainter::DrawRotatedText(std::string aText, int x, int y, double aAngle)
{
  gxPoint p(x, y);
  Transform(p);
  mDc->DrawRotatedText(wxString(aText.c_str(), wxConvUTF8), p.x + 3, p.y, aAngle);
}

gxSize gxDcPainter::GetTextSize(std::string aText)
{
  wxSize size = mDc->GetTextExtent(wxString(aText.c_str(), wxConvUTF8));
  return gxSize(size.x, size.y);
}

