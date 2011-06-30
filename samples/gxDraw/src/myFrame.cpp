#include "myFrame.h"
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/sizer.h>
#include <wx/menu.h> //wxMenuBar

#include <wx/log.h>

#include "core/gxRect.h"

enum
{
  wxID_ACTION1 = 200,
  wxID_ACTION2,
  wxID_ACTION3,
  wxID_ACTION4
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_CLOSE(MyFrame::OnClose)

  EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
  EVT_MENU(wxID_ACTION1, MyFrame::OnAction1)
  EVT_MENU(wxID_ACTION2, MyFrame::OnAction2)
  EVT_MENU(wxID_ACTION3, MyFrame::OnAction3)
  EVT_MENU(wxID_ACTION4, MyFrame::OnAction4)
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
  mLightweightControl = new gxLightweightControl(this, wxID_HIGHEST + 1, wxPoint(10,10), wxSize(500,500));
  mLightweightSystem = new gxLightweightSystem(mLightweightControl);

  mBody = new gxRectangle(gxRect(10, 10, 480, 480));
  mFace = new gxRectangle(gxRect(20, 10, 100, 100));
  mLeg = new gxRectangle(gxRect(410, 10, 10, 10));
  mBody->AddChild(mFace);
  mBody->AddChild(mLeg);
  mLightweightSystem->SetContents(mBody);
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
  gxRect newBounds = gxRect(130, 120, 100, 100);
  mFace->SetBounds(newBounds);
}

void MyFrame::OnAction2(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mEyeL = new gxRectangle(gxRect(10, 20, 20, 20));
  mEyeR = new gxRectangle(gxRect(90, 20, 20, 20));

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

  SetMenuBar(mb);
}

