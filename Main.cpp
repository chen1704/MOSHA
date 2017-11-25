#include "wx\wx.h"
#include "ImageFrame.h"

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)
DECLARE_APP(MyApp)

bool MyApp::OnInit() {
	ImageFrame *frame = new ImageFrame("MOSHA");
	frame->Show(true);

	return true;
}