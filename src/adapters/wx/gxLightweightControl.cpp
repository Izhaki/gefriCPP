// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "core/gxPaintDC.h"
#include "gxLightweightControl.h"

IMPLEMENT_DYNAMIC_CLASS(gxLightweightControl, wxControl)

DEFINE_EVENT_TYPE(wxEVT_VALIDATION_REQUEST)

BEGIN_EVENT_TABLE(gxLightweightControl, wxControl)
  EVT_PAINT(gxLightweightControl::OnPaint)
  EVT_MOTION(gxLightweightControl::OnMouseMove)
  EVT_LEFT_DOWN(gxLightweightControl::OnLeftMouseBtnDown)
  EVT_SCROLLWIN(gxLightweightControl::OnScroll)

  EVT_CUSTOM(wxEVT_VALIDATION_REQUEST, wxID_ANY, gxLightweightControl::OnValidationRequest)
END_EVENT_TABLE()

void gxLightweightControl::Init()
{
  mLightweightSystem = NULL;

  // For wxAutoBufferedPaintDC to work
  SetBackgroundStyle(wxBG_STYLE_CUSTOM);

  // Start with the scrollbars hidden
  SetScrollbar(wxHORIZONTAL, 0,1000, 1000);
  SetScrollbar(wxVERTICAL, 0,1000, 1000);
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

gxSize gxLightweightControl::GetTextSize(std::string aText)
{
  int w, h;
  GetTextExtent(wxString(aText.c_str(), wxConvUTF8), &w, &h);
  return gxSize(w, h);
}

void gxLightweightControl::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  
  gxPaintDC dc(this);

  // What will be the clip region - a union between all damaged regions.
  gxRect clipRect;

  // Get the damaged areas and put in a gxRects vector.
  gxRects damagedRects;
  wxRegionIterator upd(GetUpdateRegion()); 
  while (upd)
  {
    wxRect rect = upd.GetRect();
    gxRect damagedRect(rect.x, rect.y, rect.width, rect.height);
    // Union the damaged recangle with the clip region
    clipRect.Union(damagedRect);
    damagedRects.push_back(damagedRect);
    upd ++ ;
  }
  
  // Set an absolute clip area (to the union between all damaged areas).
  dc.DestroyClippingRegion();
  dc.SetClippingRegion(clipRect);

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

void gxLightweightControl::OnScroll(wxScrollWinEvent& event)
{
  // The position of the scroll bar returns to 0 on MSW, we need to set the
  // position ourselves.
  if (event.GetOrientation() == wxVERTICAL)
    SetScrollPos(wxVERTICAL, event.GetPosition());
  else
    SetScrollPos(wxHORIZONTAL, event.GetPosition());
  
  if (mLightweightSystem)
  {
    mLightweightSystem->OnScroll(event.GetOrientation() == wxVERTICAL, event.GetPosition());
  }
  event.Skip();
}

void gxLightweightControl::QueueValidation()
{
  wxCommandEvent event( wxEVT_VALIDATION_REQUEST, GetId() );
  event.SetEventObject( this );
  GetEventHandler()->AddPendingEvent(event);
}

void gxLightweightControl::OnValidationRequest(wxEvent& event)
{
  if (mLightweightSystem)
    mLightweightSystem->OnValidationRequest();
}

