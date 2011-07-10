#include "view/gxDcPainter.h"
#include <wx/log.h>

gxDcPainter::gxDcPainter(gxPaintDC *aDc, gxRects const &aDamagedRects)
{
  mDc = aDc;
  mDamagedRects = aDamagedRects;
}

gxRect gxDcPainter::GetClipRect()
{
  long x, y, w, h;
  mDc->GetClippingBox(&x, &y, &w, &h);
  return gxRect(x, y, w, h);
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


