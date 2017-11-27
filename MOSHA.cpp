#include "MOSHA.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "wx/bmpbuttn.h"

BEGIN_EVENT_TABLE(MOSHA, wxWindow)
	EVT_PAINT(MOSHA::OnPaint)
	EVT_CHAR(MOSHA::OnChar)
	EVT_BUTTON(1001, MOSHA::ClickStart)
	
END_EVENT_TABLE()

int ganti = 0;
int r;

MOSHA::MOSHA(wxFrame *parent) : wxWindow(parent, wxID_ANY){
	this->SetBackgroundColour(wxColour(*wxWHITE));
	panel = new wxPanel(this, wxID_ANY,wxPoint(10,455),wxSize(700,500));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->LoadbuttonWindowBitmap();
	if (ganti == 0) {
//		this->LoadStartButton();
		wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
		start = new wxBitmap(image);
		wxBitmapButton* startbutton = new wxBitmapButton(panel, 1001,image,wxDefaultPosition,
			wxDefaultSize, wxBU_AUTODRAW);
		this->LoadMenuBitmap();
		if (r == 13) {
			ganti = 1;
			delete menu;
			delete start;
			Refresh();
		}
	}
	if (ganti == 1) {
		
	}
}


MOSHA::~MOSHA()
{
	delete menu;
	delete start;
	delete buttonWindow;
}

void MOSHA::LoadMenuBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\menu awal.png");
	wxMessageOutputDebug().Printf("Gambarnya di %s", fileLocation);

	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\menu awal.png"), wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image);
}

void MOSHA::LoadStartButton() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\start button.png");
	wxMessageOutputDebug().Printf("Gambarnya di %s", fileLocation);

//	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
//	start = new wxBitmap(image);
//	wxBitmap bitmap(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
//	wxBitmapButton* startbutton = new wxBitmapButton(panel, wxID_OK, bitmap, wxPoint(108, 526),
//		wxSize(286,101), wxBU_AUTODRAW);
}

void MOSHA::ClickStart(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("di klik di start");
}

void MOSHA::LoadbuttonWindowBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxMessageOutputDebug().Printf("Gambarnya di %s", fileLocation);

	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\button window.png"), wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);
}
//D:\ITS SMT 3\PBO (C)\FP\moshasampah
void MOSHA::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	if (buttonWindow != nullptr) {
		pdc.DrawBitmap(*buttonWindow, wxPoint(0,455),true);
		if (ganti == 0) {
			pdc.DrawBitmap(*menu, wxPoint(0,0), true);
//			pdc.DrawBitmap(*start, wxPoint(108,526), true);
		}
	}
	
}

void MOSHA::OnChar(wxKeyEvent &event) {
	r = event.GetKeyCode();
	wxMessageOutputDebug().Printf("Keyboard diteken, Keycode = %d", r);
}
