#include "myFrame.h"
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/sizer.h>
#include <wx/menu.h> //wxMenuBar

#include <wx/log.h>

#include "core/geometry/gxGeometry.h"

enum
{
  wxID_ACTION1 = 200,
  wxID_ACTION2,
  wxID_ACTION3,
  wxID_ACTION4,
  wxID_ZOOM_INS,
  wxID_ZOOM_OUTS,
  wxID_ZOOM_IN_VERT,
  wxID_ZOOM_OUT_VERT
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_CLOSE(MyFrame::OnClose)

  EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
  EVT_MENU(wxID_ACTION1, MyFrame::OnAction1)
  EVT_MENU(wxID_ACTION2, MyFrame::OnAction2)
  EVT_MENU(wxID_ACTION3, MyFrame::OnAction3)
  EVT_MENU(wxID_ACTION4, MyFrame::OnAction4)
  
  EVT_MENU(wxID_ZOOM_INS, MyFrame::OnZoomIn)
  EVT_MENU(wxID_ZOOM_OUTS, MyFrame::OnZoomOut)
  EVT_MENU(wxID_ZOOM_IN_VERT, MyFrame::OnZoomInVert)
  EVT_MENU(wxID_ZOOM_OUT_VERT, MyFrame::OnZoomOutVert)  
END_EVENT_TABLE()


void MyFrame::Test()
{
  wxLogDebug(_T("Test"));
}

MyFrame::MyFrame(wxWindow* parent,
                     wxWindowID id,
                     const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style)
                    : wxFrame(parent, id, title, pos, size, style)
{
  Initialize();
}

MyFrame::~MyFrame()
{
}

void MyFrame::InitGefri()
{
  mLightweightControl = new gxLightweightControl(this, wxID_HIGHEST + 1, wxPoint(10,10), wxSize(500,500), LightweightControlStyle | wxHSCROLL);
  mLightweightSystem = new gxLightweightSystem(mLightweightControl);

  mDocument = new gxRectangle(gxRect(10, 10, 480, 480));
  
  mZoomManager = new gxZoomManager();
  mZoom = new gxScaler(mZoomManager);
  
  mScrollManager = new gxScrollManager();
  mLightweightSystem->SetScrollManager(mScrollManager);
  
  mFace = new gxRectangle(gxRect(40, 40, 100, 100));
  //mLeg = new gxRectangle(gxRect(410, 10, 10, 10));
  
  mZoom->AddChild(mFace);
  
  mScroller = new gxScroller(mScrollManager);
  mDocument->AddChild(mScroller);
  mScroller->AddChild(mZoom);
  
  //mZoom->AddChild(mLeg);

  mLightweightSystem->SetContents(mDocument);
}

void MyFrame::Initialize()
{
  Test();
  wxBoxSizer *sz = new wxBoxSizer(wxVERTICAL);
  SetSizer(sz);


  //Create a status bar 
  wxStatusBar* statusBar = new wxStatusBar(this, wxID_ANY);
  statusBar->SetFieldsCount(1);
  SetStatusBar(statusBar);
  GetStatusBar()->SetStatusText(wxT("Ready"));

  //Create a menu bar
  CreateMenuBar();

  InitGefri();
  
  sz->Add(mLightweightControl, 1, wxEXPAND | wxALL);

  sz->Layout();
}

void MyFrame::OnClose(wxCloseEvent &e)
{
  e.Skip();
}


void MyFrame::OnQuit(wxCommandEvent &e)

{
  wxUnusedVar(e);
  Close();
}

void MyFrame::OnAction1(wxCommandEvent &e)
{
  wxUnusedVar(e);
  gxRect newBounds = gxRect(120, 120, 100, 100);
  mFace->SetBounds(newBounds);
}

void MyFrame::OnAction2(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mEyeL = new gxRectangle(gxRect(10, 10, 20, 20));
  mEyeR = new gxRectangle(gxRect(90, 10, 20, 20));

//  Iris1 = new gxRectangle(gxRect(3, 3, 2, 2));
//  Iris2 = new gxRectangle(gxRect(7, 7, 2, 2));
//  mEyeL->AddChild(Iris1);
//  mEyeL->AddChild(Iris2);

  mFace->AddChild(mEyeL);
  mFace->AddChild(mEyeR);
}

void MyFrame::OnAction3(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mFace->RemoveChild(mEyeL);
  mFace->RemoveChild(mEyeR);
  delete mEyeL;
  delete mEyeR;
  mEyeL = NULL;
  mEyeR = NULL;
}

void MyFrame::OnAction4(wxCommandEvent &e)
{
  wxUnusedVar(e);
}


void MyFrame::OnZoomIn(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mZoomManager->MultiplyZoom(2);
}

void MyFrame::OnZoomOut(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mZoomManager->MultiplyZoom(0.5);
}

void MyFrame::OnZoomInVert(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mZoomManager->MultiplyZoom(2, 1);
}

void MyFrame::OnZoomOutVert(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mZoomManager->MultiplyZoom(0.5, 1);
}


void MyFrame::CreateMenuBar()
{
  wxMenuBar *mb = new wxMenuBar();

  //File Menu
  wxMenu *menu = new wxMenu();

  menu->Append(wxID_EXIT);

  mb->Append(menu, wxT("&File"));

  //Actions Menu
  wxMenu *actionsMenu = new wxMenu();
  actionsMenu->Append(wxID_ACTION1, wxT("Move Face\tCtrl-1"), wxT("Move the face\n" ));
  actionsMenu->Append(wxID_ACTION2, wxT("Add Eyes\tCtrl-2"));
  actionsMenu->Append(wxID_ACTION3, wxT("Remove Eyes\tCtrl-3"));
  actionsMenu->Append(wxID_ACTION4, wxT("Unused\tCtrl-4"));
  mb->Append(actionsMenu, wxT("&Actions"));

  //Zoom Menu
  wxMenu *zoomMenu = new wxMenu();
  zoomMenu->Append(wxID_ZOOM_INS, wxT("Zoom In\t+" ));
  zoomMenu->Append(wxID_ZOOM_OUTS, wxT("Zoom Out\t-"));
  zoomMenu->Append(wxID_ZOOM_IN_VERT, wxT("Zoom In Vertically\tt"));
  zoomMenu->Append(wxID_ZOOM_OUT_VERT, wxT("Zoom In Horizontally\tr"));
  mb->Append(zoomMenu, wxT("&Zoom"));

  SetMenuBar(mb);
}

