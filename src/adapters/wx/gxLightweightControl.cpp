// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "core/gxPaintDC.h"
#include "gxLightweightControl.h"

IMPLEMENT_DYNAMIC_CLASS(gxLightweightControl, wxControl);

BEGIN_EVENT_TABLE(gxLightweightControl, wxControl)
  EVT_PAINT(gxLightweightControl::OnPaint)
  EVT_MOTION(gxLightweightControl::OnMouseMove)
  EVT_LEFT_DOWN(gxLightweightControl::OnLeftMouseBtnDown)
END_EVENT_TABLE()

void gxLightweightControl::Init()
{
  mLightweightSystem = NULL;
}

gxLightweightControl::~gxLightweightControl()
{
  UnsetLightweightSystem();
}

void gxLightweightControl::SetLightweightSystem(gxLightweightSystem* aLightweightSystem)
{
  mLightweightSystem = aLightweightSystem;
}

void gxLightweightControl::UnsetLightweightSystem()
{
  mLightweightSystem = NULL;
}

gxRect gxLightweightControl::GetBounds() const
{
  return (gxRect)GetRect();
}


void gxLightweightControl::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  gxPaintDC dc(this);

  // Get the damaged areas and put in a gxRect vector.
  gxRects damagedRects;
  wxRegionIterator upd(GetUpdateRegion()); 
  while (upd)
  {
    gxRect damagedRect(upd.GetRect());
    damagedRects.push_back(damagedRect);
    upd ++ ;
  }

  // Temporal: Draw a rectangle so we can see the Control.
  wxSize size = GetSize();
  dc.DrawRectangle(0, 0, size.GetWidth(), size.GetHeight());

  // Delegate paint duties to the lightweight system.
  if (mLightweightSystem)
  {
    mLightweightSystem->Paint(&dc, damagedRects);
  }
}

void gxLightweightControl::OnMouseMove(wxMouseEvent& event)
{
}

void gxLightweightControl::OnLeftMouseBtnDown(wxMouseEvent& event)
{
}
