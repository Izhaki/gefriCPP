#ifndef gxLightweightControl_wx_h
#define gxLightweightControl_wx_h

#include <wx/control.h>
#include "view/gxLightweightSystem.h"

static const long LightweightControlStyle = wxNO_BORDER;// | wxVSCROLL;// | wxALWAYS_SHOW_SB; //| wxNO_FULL_REPAINT_ON_RESIZE | wxTRANSPARENT_WINDOW; // , //0x00000020L, //| wxCLIP_SIBLINGS, //| 0x00000020L, //0x00000008L

/**
  * @brief A system-depandent control with which the lightweight system
  * communicates.
  *
  * This control communicates with gxLightweightSystem, forwarding system events
  * (paint, mouse) to it, but also receiving Refresh requests from it.
 */
class gxLightweightControl: public wxControl
{
public: 
  DECLARE_DYNAMIC_CLASS(gxLightweightControl);

  gxLightweightControl() { Init(); }
  gxLightweightControl(wxWindow *parent, wxWindowID id,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = LightweightControlStyle,
    const wxValidator& validator = wxDefaultValidator,
    const wxString& name = wxControlNameStr) 
      : wxControl(parent, id, pos, size, style, validator, name) { Init(); }

  ~gxLightweightControl();

  void SetLightweightSystem(gxLightweightSystem* aLightweightSystem);
  void UnsetLightweightSystem();

  gxRect GetBounds() const;

  // Event Handlers
  void OnPaint(wxPaintEvent& event);
  void OnMouseMove(wxMouseEvent& event);
  void OnLeftMouseBtnDown(wxMouseEvent& event); 
  void OnScroll(wxScrollWinEvent& event);

  void RefreshRect(const gxRect& aRect, bool eraseBackground = true);

  DECLARE_EVENT_TABLE();
protected:
  // common part of all ctors
  void Init();

  gxLightweightSystem* mLightweightSystem;
};

#endif // gxLightweightControl_wx_h