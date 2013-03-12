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
#include "View/Elements/Structural/Anchors/gxRectAnchor.h"
#include "View/Connections/gxLineConnection.h"
#include "View/Elements/Structural/Layers/gxLayers.h"
#include "View/Elements/Structural/Layers/gxLayer.h"
#include "View/Layouts/gxBoxLayout.h"
#include "View/Layouts/gxBorderLayout.h"

#include "core/gxComposite.h"

class MyFrame : public wxFrame {

private:
    void Initialize();
    void CreateMenuBar();
    void Test();
    
    void InitGefri();
    void CreateFaceAndRuller();
    void CreateBoxLayout();    
    void CreateBorderLayout();
  
    gxLightweightControl *mLightweightControl;
    gxLightweightSystem  *mLightweightSystem;
    gxRectangle      *mDocument, *mFace, *mEyeL, *mEyeR, *Iris1, *Iris2, *mLeg;
    gxScaler         *mZoom;
    gxZoomManager    *mZoomManager;
    gxScroller       *mScroller;
    gxScrollManager  *mScrollManager;
    
    gxLayers* mLayers;
    gxLayer*  mConnectionLayer;
    gxLayer*  mPrimaryLayer;
    
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
  void OnMoveFace(wxCommandEvent &e);
  void OnAction2(wxCommandEvent &e);
  void OnAction3(wxCommandEvent &e);
  void OnHideFace(wxCommandEvent &e);
  void OnShowFace(wxCommandEvent &e);
  
  void OnZoomIn(wxCommandEvent &e);
  void OnZoomOut(wxCommandEvent &e);
  void OnZoomInHorz(wxCommandEvent &e);
  void OnZoomOutHorz(wxCommandEvent &e);
};
