#ifndef gxPaintDC_wx_h
#define gxPaintDC_wx_h

#include <wx/dcbuffer.h>
#include "core/geometry/gxGeometry.h"

/**
 * @brief A wrapper to a system's DC using wxAutoBufferedPaintDC
 */
class gxPaintDC: public wxAutoBufferedPaintDC
{
public:
  gxPaintDC(wxWindow *win)
    : wxAutoBufferedPaintDC(win) {}
  
  gxRect GetClippingBox() const
  {
    wxCoord x, y, w, h;
    wxAutoBufferedPaintDC::GetClippingBox(&x, &y, &w, &h);
    return gxRect(x, y, w, h);
  }
  
  void SetClippingRegion(const gxRect& rect)
  {
    //DoSetClippingRegion(rect.X, rect.Y, rect.width, rect.height);
    wxAutoBufferedPaintDC::SetClippingRegion(rect.X, rect.Y, rect.width, rect.height);
  }

  void DrawRectangle(gxPix aX, gxPix aY, gxPix width, gxPix height)
        { wxAutoBufferedPaintDC::DrawRectangle(aX, aY, width, height); }
  void DrawRectangle(const gxPoint& aPoint, const gxSize& aSize)
        { wxAutoBufferedPaintDC::DrawRectangle(aPoint.X, aPoint.Y, aSize.X, aSize.Y); }
  void DrawRectangle(const gxRect& rect)
    { wxAutoBufferedPaintDC::DrawRectangle(rect.X, rect.Y, rect.width, rect.height); }
};

#endif // gxPaintDC_wx_h