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
  wxRect rect = GetRect();
  return gxRect(rect.x, rect.y, rect.width, rect.height);
}


void gxLightweightControl::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  gxPaintDC dc(this);
  
  # if defined(__WXMSW__)
    // In MSW the clip area upon the dc creation is (0,0,0,0). So fix this
    // by setting an absolute clip region that has origins (0,0) and the size
    // equal to that of the control
    wxRect clip(GetSize()); 
    dc.DestroyClippingRegion();
    dc.SetClippingRegion(clip);
  #endif 

  // Get the damaged areas and put in a gxRect vector.
  gxRects damagedRects;
  wxRegionIterator upd(GetUpdateRegion()); 
  while (upd)
  {
    wxRect rect = upd.GetRect();
    gxRect damagedRect(rect.x, rect.y, rect.width, rect.height);
    damagedRects.push_back(damagedRect);
    upd ++ ;
  }

  // Temporal: Draw chess board
  dc.SetPen(wxPen(*wxTRANSPARENT_PEN));
  wxSize size = GetSize();
  int boxSize = 40;
  for (int x = 0; x <= (int)(size.GetWidth() / boxSize); x++)
  {
    for (int y = 0; y <= (int)(size.GetHeight() / boxSize); y++)
    {
      if ( (x + y) % 2 == 0)
        dc.SetBrush(wxBrush(wxColor(240,240,240)));
      else
        dc.SetBrush(wxBrush(wxColor(255,255,255)));
      dc.DrawRectangle(x * boxSize, y * boxSize, boxSize, boxSize);     
    }
  }
  dc.SetBrush(wxBrush(_T("white"), wxSOLID));
  dc.SetPen(*wxBLACK_PEN);
  
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

void gxLightweightControl::RefreshRect(const gxRect& aRect, bool eraseBackground)
{
  wxRect rect(aRect.x, aRect.y, aRect.width, aRect.height);
  wxControl::RefreshRect(rect, eraseBackground);
}
