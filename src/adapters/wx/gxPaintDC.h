#ifndef gxPaintDC_wx_h
#define gxPaintDC_wx_h

#include <wx/dcbuffer.h>
#include "core/geometry/gxGeometry.h"
#include <wx/log.h>

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
    long x, y, w, h;
    wxAutoBufferedPaintDC::GetClippingBox(&x, &y, &w, &h);
    return gxRect(x, y, w, h);
  }
  
  void SetClippingRegion(const gxRect& rect)
  {
    DoSetClippingRegion(rect.X, rect.Y, rect.width, rect.height);
  }

  void DrawRectangle(gxPix aX, gxPix aY, gxPix width, gxPix height)
        { DoDrawRectangle(aX, aY, width, height); }
  void DrawRectangle(const gxPoint& aPoint, const gxSize& aSize)
        { DoDrawRectangle(aPoint.X, aPoint.Y, aSize.X, aSize.Y); }
  void DrawRectangle(const gxRect& rect)
    { DoDrawRectangle(rect.X, rect.Y, rect.width, rect.height); }
};

#endif // gxPaintDC_wx_h