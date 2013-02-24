#include "wx/frame.h"

#include "View/gxLightweightControl.h"
#include "View/gxLightweightSystem.h"
#include "View/Elements/Visual/shapes/gxRectangle.h"
#include "View/Elements/Visual/shapes/gxLine.h"
#include "View/Elements/Structural/gxScaler.h"
#include "View/Managers/gxZoomManager.h"
#include "View/Elements/Structural/gxScroller.h"
#include "View/Managers/gxScrollManager.h"
#include "View/Elements/Visual/gxRuler.h"
#include "View/DivProvider/gxDivProvider.h"
#include "View/DivProvider/gxViewUnit.h"
#include "View/Connections/gxBoxAnchor.h"
#include "View/Connections/gxLineConnection.h"

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
    gxLineConnection *mCon;
    
    gxBoxAnchor *mFaceAnchor;

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
  void OnHideFace(wxCommandEvent &e);
  void OnShowFace(wxCommandEvent &e);
  
  void OnZoomIn(wxCommandEvent &e);
  void OnZoomOut(wxCommandEvent &e);
  void OnZoomInHorz(wxCommandEvent &e);
  void OnZoomOutHorz(wxCommandEvent &e);
};
