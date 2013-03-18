#include "myFrame.h"
#include <wx/toolbar.h>
#include <wx/statusbr.h>
#include <wx/sizer.h>
#include <wx/menu.h> //wxMenuBar

#include <wx/log.h>

#include "core/gxLog.h"
#include "core/geometry/gxGeometry.h"

enum
{
  wxID_ACTION1 = 200,
  wxID_ACTION2,
  wxID_ACTION3,
  wxID_HIDE_FACE,
  wxID_SHOW_FACE,
  wxID_ZOOM_INS,
  wxID_ZOOM_OUTS,
  wxID_ZOOM_IN_VERT,
  wxID_ZOOM_OUT_VERT
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_CLOSE(MyFrame::OnClose)

  EVT_MENU(wxID_EXIT, MyFrame::OnQuit)
  EVT_MENU(wxID_ACTION1, MyFrame::OnMoveFace)
  EVT_MENU(wxID_ACTION2, MyFrame::OnAction2)
  EVT_MENU(wxID_ACTION3, MyFrame::OnAction3)
  EVT_MENU(wxID_HIDE_FACE, MyFrame::OnHideFace)
  EVT_MENU(wxID_SHOW_FACE, MyFrame::OnShowFace)

  EVT_MENU(wxID_ZOOM_INS, MyFrame::OnZoomIn)
  EVT_MENU(wxID_ZOOM_OUTS, MyFrame::OnZoomOut)
  EVT_MENU(wxID_ZOOM_IN_VERT, MyFrame::OnZoomInHorz)
  EVT_MENU(wxID_ZOOM_OUT_VERT, MyFrame::OnZoomOutHorz)  
END_EVENT_TABLE()


void MyFrame::Test()
{
  wxLogDebug( "Test" );
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
//    delete mScroller;
//    delete mRulerH;
//    delete mDivProvider;
//    delete mViewUnit;
    
//    Will be deleted by parent
//    delete mFace;
    
//    delete mScrollManager;
//    delete mZoom;

//    delete mDocument;
    delete mLightweightSystem;
    delete mLightweightControl;
    
    delete mScrollManager;
    delete mZoomManager;
}

void MyFrame::InitGefri()
{
    mLightweightControl = new gxLightweightControl(this, wxID_HIGHEST + 1, wxPoint(10,10), wxSize(500,500), LightweightControlStyle | wxHSCROLL | wxVSCROLL);
    mLightweightSystem = new gxLightweightSystem(mLightweightControl);

    mDocument = new gxRectangle(gxRect( 50, 50, 400, 480 ));
    
    // Scoll Manager and scroller
    mScrollManager = new gxScrollManager();
    mLightweightSystem->SetScrollManager(mScrollManager);
    mScroller = new gxScroller( mScrollManager );
    mDocument->Add( mScroller );

    // Zoom manager and scaler
    mZoomManager = new gxZoomManager();
    mZoom = new gxScaler(mZoomManager);
    mScroller->Add(mZoom);
    
    // Layers
    mLayers          = new gxLayers();
    mConnectionLayer = new gxLayer();
    mPrimaryLayer    = new gxLayer();
    
    mLayers->Add( mPrimaryLayer );
    mLayers->Add( mConnectionLayer );
    
    mZoom->Add( mLayers );
    
    CreateFaceAndRuller();
//    CreateBoxLayout();
//    CreateBorderLayout();
    
    mLightweightSystem->SetContents(mDocument);
}

void MyFrame::CreateFaceAndRuller()
{
    gxViewUnit    *mViewUnit;
    gxDivProvider *mDivProvider;
    gxRuler       *mRulerH;

    
    gxLineConnection *mCon;
    
    gxRectAnchor *mFaceAnchor;
    gxRectAnchor *mRulerAnchor;
    
    
    // Face
    mFace = new gxRectangle( gxRect( 40, 40, 100, 100 ) );
    //mLeg = new gxRectangle(gxRect(410, 10, 10, 10));
    mPrimaryLayer->Add(mFace);
    
    // Ruler
    mViewUnit = new gxPixelUnit();
    mDivProvider = new gxDivProvider(mViewUnit);
    mRulerH = new gxRuler(gxRect(0, 0, 140, 20), mDivProvider);
    //mRulerH = new gxRuler(gxRect(0, 0, 20, 480),  mDivProvider, mViewUnit);
    mRulerH->SetZoomManager( mZoomManager );
    mRulerH->SetScrollManager( mScrollManager );
    mPrimaryLayer->Add( mRulerH );
    
    // Add the anchors
    mFaceAnchor = new gxRectAnchor();
    mFace->Add( mFaceAnchor );
    mRulerAnchor = new gxRectAnchor();
    mRulerH->Add( mRulerAnchor );
    
    // Add Connection
    mCon = new gxLineConnection();
    mCon->SetDestinationAnchor( mFaceAnchor );
    mCon->SetSourceAnchor( mRulerAnchor );
    mConnectionLayer->Add( mCon );
}

void MyFrame::CreateBoxLayout()
{
    // Layout related figures
    gxRectangle *mHBox, *mF1, *mF2, *mF3;
    gxBoxLayout *mLayout;
        
    mHBox   = new gxRectangle( gxRect( 0, 300, 480, 100 ) );
    
    mLayout = new gxBoxLayout( gxDistribute::Equal,
                              gxStretch::None,
                              gxAlign::Middle,
                              true );
    
    mHBox->SetLayout( mLayout );
    
    mF1     = new gxRectangle( gxRect( 0, 0, 10, 10 ) );
    mF2     = new gxRectangle();
    mF3     = new gxRectangle();
    
    //    mLayout->SetRect( mF1, gxRect( 0, 0, 10, 10 ) );
    mLayout->Add( mF1 );
    mLayout->SetRect( mF2, gxRect( 30, 30, 20, 20 ) );
    mLayout->SetRect( mF3, gxRect( 130, 30, 30, 30 ) );
    
    mLayout->SetFlex( mF1, 1 );
    //    mLayout->SetFlex( mF2, 1 );
    //    mLayout->SetFlex( mF3, 6 );
    
    mLayout->SetPercent( mF3, 70 );
    
    
    mHBox->Add( mF1 );
    mHBox->Add( mF2 );
    mHBox->Add( mF3 );
    
    mPrimaryLayer->Add( mHBox );
}

void MyFrame::CreateBorderLayout()
{
    gxRectangle *mContainer, *mCenter, *mNorth, *mSouth, *mWest, *mEast;
    gxBorderLayout *mBorderLayout;
    
    mContainer = new gxRectangle( gxRect( 10, 300, 460, 100 ) );
    mBorderLayout = new gxBorderLayout( false );
    mContainer->SetLayout( mBorderLayout );
    
    mNorth  = new gxRectangle( gxSize( 50,20 ) );
    mCenter = new gxRectangle();
    mSouth  = new gxRectangle( gxSize( 50,20 ) );
    mWest   = new gxRectangle( gxSize( 50,20 ) );
    mEast   = new gxRectangle( gxSize( 50,20 ) );
    
    mBorderLayout->SetRegion( mNorth,  gxRegion::North );
    mBorderLayout->SetRegion( mCenter, gxRegion::Center );
    mBorderLayout->SetRegion( mSouth,  gxRegion::South );
    mBorderLayout->SetRegion( mWest,   gxRegion::West );
    mBorderLayout->SetRegion( mEast,   gxRegion::East );
    
    mContainer->Add( mNorth );
    mContainer->Add( mCenter );
    mContainer->Add( mSouth );
    mContainer->Add( mWest );
    mContainer->Add( mEast );
    
    mPrimaryLayer->Add( mContainer );
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

void MyFrame::OnMoveFace(wxCommandEvent &e)
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
//  mEyeL->Add(Iris1);
//  mEyeL->Add(Iris2);

  mFace->Add(mEyeL);
  mFace->Add(mEyeR);
}

void MyFrame::OnAction3(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mFace->Remove(mEyeL);
  mFace->Remove(mEyeR);
  delete mEyeL;
  delete mEyeR;
  mEyeL = NULL;
  mEyeR = NULL;
}

void MyFrame::OnHideFace(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mFace->Hide();
}

void MyFrame::OnShowFace(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mFace->Show();
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

void MyFrame::OnZoomInHorz(wxCommandEvent &e)
{
  wxUnusedVar(e);
  mZoomManager->MultiplyZoom(2, 1);
}

void MyFrame::OnZoomOutHorz(wxCommandEvent &e)
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
  actionsMenu->Append(wxID_HIDE_FACE, wxT("Hide Face\tCtrl-4"));
  actionsMenu->Append(wxID_SHOW_FACE, wxT("Show Face\tCtrl-5"));
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

