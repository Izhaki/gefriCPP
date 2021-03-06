#include <wx/wx.h>
#include "myFrame.h"

// application class
class MyApp : public wxApp
{
  public:
  // function called at the application initialization
  virtual bool OnInit();
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // create a new frame and set it as the top most application window
    wxFrame* frame = new MyFrame(NULL,
                                wxID_ANY,
                                wxT("gxDraw"),
                                wxDefaultPosition,
                                wxSize(800, 600),
                                wxDEFAULT_FRAME_STYLE | wxCLIP_CHILDREN);

	frame->Show(TRUE);
	SetTopWindow(frame);

	// enter the application's main loop
  return true;
}