#include "MenuStart.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Resource.h"

BEGIN_EVENT_TABLE(MenuStart, wxWindow)
EVT_PAINT(MenuStart::OnPaint)
EVT_BUTTON(1001, MenuStart::ClickStart)
END_EVENT_TABLE()

MenuStart::MenuStart(ImageFrame * parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	LoadStartBitmap();

	//Load Bitmap" yang dipakai berulang kali
	rs = Resource::getInstance();
	rs->LoadResourceBitmap();
	rs->LoadMenuBitmap();
	rs->LoadHurufbesarBitmap();
	rs->LoadHurufkecilBitmap();
	
	wxBitmapButton* startbutton = new wxBitmapButton(this, 1001, *start, wxPoint(100, 520), wxDefaultSize, wxBORDER_NONE);
}

MenuStart::~MenuStart()
{
	delete start, menu;
}

void MenuStart::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*menu, wxPoint(0, 0),true);
	pdc.DrawBitmap(*rs->buttonWindow, wxPoint(0, 455), true);
}

void MenuStart::ClickStart(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("di klik di start");
	parentFrame->ShowName();
}

void MenuStart::LoadStartBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString locstart = wxFileName(fileLocation).GetPath() + wxT("\\start button.png");
	wxImage image(locstart, wxBITMAP_TYPE_PNG);
	start = new wxBitmap(image);

	wxString loclogo = wxFileName(fileLocation).GetPath() + wxT("\\menu awal.png");
	wxImage image1(loclogo, wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image1);
}
