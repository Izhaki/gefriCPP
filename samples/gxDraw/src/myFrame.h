#include "wx/frame.h"

#include "view/gxLightweightControl.h"
#include "view/gxLightweightSystem.h"
#include "view/elements/shapes/gxRectangle.h"
#include "view/elements/gxScaler.h"
#include "view/managers/gxZoomManager.h"
#include "view/elements/gxScroller.h"
#include "view/managers/gxScrollManager.h"
#include "view/elements/gxRuler.h"
#include "view/gxDivProvider.h"
#include "view/gxViewUnit.h"

#include "core/gxComposite.h"

class MyFrame : public wxFrame {

private:
  void Initialize();
  void CreateMenuBar();
  void Test();
  void InitGefri();
  
  gxLightweightControl *mLightweightControl;
  gxLightweightSystem *mLightweightSystem;
  gxRectangle *mDocument, *mFace, *mEyeL, *mEyeR, *Iris1, *Iris2, *mLeg;
  gxScaler *mZoom;
  gxZoomManager *mZoomManager;
  gxScroller *mScroller;
  gxScrollManager *mScrollManager;

  gxViewUnit    *mViewUnit;
  gxDivProvider *mDivProvider;
  gxRuler       *mRulerH;
public:
  MyFrame(wxWindow   *parent,
          wxWindowID id,
          const      wxString& title,
          const      wxPoint& pos = wxDefaultPosition,
          const      wxSize& size = wxDefaultSize,
          long       style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

  ~MyFrame();
  DECLARE_EVENT_TABLE()

  void OnClose(wxCloseEvent &e);

  void OnQuit(wxCommandEvent &e);
  void OnAction1(wxCommandEvent &e);
  void OnAction2(wxCommandEvent &e);
  void OnAction3(wxCommandEvent &e);
  void OnAction4(wxCommandEvent &e);	
  
  void OnZoomIn(wxCommandEvent &e);
  void OnZoomOut(wxCommandEvent &e);
  void OnZoomInHorz(wxCommandEvent &e);
  void OnZoomOutHorz(wxCommandEvent &e);
};
