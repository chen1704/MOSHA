#include "MOSHA.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "wx/bmpbuttn.h"

BEGIN_EVENT_TABLE(MOSHA, wxWindow)
EVT_PAINT(MOSHA::OnPaint)
EVT_CHAR(MOSHA::OnChar)
EVT_BUTTON(1001, MOSHA::ClickStart)
END_EVENT_TABLE()

MOSHA::MOSHA(ImageFrame *parent) : wxWindow(parent, wxID_ANY), parentFrame(parent) 
{
	this->state = 0;
	this->SetBackgroundColour(wxColour(*wxWHITE));
//	panel = new wxPanel(this, 1001, wxPoint(100, 520), wxSize(300, 110),wxBG_STYLE_TRANSPARENT);
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	LoadAllBitmap();

	wxBitmapButton* startbutton = new wxBitmapButton(this, 1001, *start, wxPoint(100,520), wxDefaultSize, wxBU_AUTODRAW);


}


MOSHA::~MOSHA()
{
	delete menu;
	delete start;
	delete buttonWindow;
	
}

void MOSHA::LoadAllBitmap()
{
	this->LoadMenuBitmap();
	this->LoadbuttonWindowBitmap();
	this->LoadStartButton();
}

void MOSHA::LoadMenuBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString loclogo = wxFileName(fileLocation).GetPath() + wxT("\\menu awal.png");
	wxImage image(loclogo, wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image);
}

void MOSHA::LoadMapButton() {
	wxString locmenu = wxFileName(fileLocation).GetPath() + wxT("\\MAP - FIX.png");
	wxImage image(locmenu, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);
}

void MOSHA::LoadStartButton() {
	wxString locstart = wxFileName(fileLocation).GetPath() + wxT("\\start button.png");
	wxImage image(locstart, wxBITMAP_TYPE_PNG);
	start = new wxBitmap(image);
}

void MOSHA::ClickStart(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("di klik di start");
//	this->state = 1;
//	Refresh();
//	this->LoadMapButton();
	parentFrame->ShowMap();

}

void MOSHA::LoadbuttonWindowBitmap() {
	wxString locwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image(locwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);
}


//D:\ITS SMT 3\PBO (C)\FP\moshasampah
void MOSHA::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);

	if (this->state == 0) {
		pdc.DrawBitmap(*menu, wxPoint(0, 0), true);
		pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	}
	else if (this->state == 1) {
		pdc.DrawBitmap(*map, wxPoint(0, 0), true);
		pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	}
//	wxMessageOutputDebug().Printf("Halo");


}


void MOSHA::OnChar(wxKeyEvent &event) {
	wxMessageOutputDebug().Printf("Keyboard diteken, Keycode = %d", event.GetKeyCode());
}

