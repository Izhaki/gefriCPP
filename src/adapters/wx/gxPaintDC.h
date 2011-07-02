#ifndef gxPaintDC_wx_h
#define gxPaintDC_wx_h

#include <wx/dcclient.h>
#include "core/geometry/gxGeometry.h"

/**
 * @brief A wrapper to a system's DC using wxPaintDC
 */
class gxPaintDC: public wxPaintDC
{
public:
  gxPaintDC(wxWindow *win)
    : wxPaintDC(win) {}
  void SetClippingRegion(const gxRect& rect)
    { DoSetClippingRegion(rect.x, rect.y, rect.width, rect.height); }

  void DrawRectangle(gxCoord x, gxCoord y, gxCoord width, gxCoord height)
        { DoDrawRectangle(x, y, width, height); }
  void DrawRectangle(const gxPoint& pt, const gxSize& sz)
        { DoDrawRectangle(pt.x, pt.y, sz.x, sz.y); }
  void DrawRectangle(const gxRect& rect)
    { DoDrawRectangle(rect.x, rect.y, rect.width, rect.height); }
};

#endif // gxPaintDC_wx_h