#include "MOSHA.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

BEGIN_EVENT_TABLE(MOSHA, wxWindow)
	EVT_PAINT(MOSHA::OnPaint)
	EVT_CHAR(MOSHA::OnChar)
END_EVENT_TABLE()

int ganti = 0;
int r;

MOSHA::MOSHA(wxFrame *parent) : wxWindow(parent, wxID_ANY){
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->LoadbuttonWindowBitmap();
	if (ganti == 0) {
		this->LoadStartButton();
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

	wxImage image(wxT("E:\\Kuliah\\SEM 3\\PBO\\FP\\MOSHA\\menu awal.png"), wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image);
}

void MOSHA::LoadStartButton() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\start button.png");
	wxMessageOutputDebug().Printf("Gambarnya di %s", fileLocation);

	wxImage image(wxT("E:\\Kuliah\\SEM 3\\PBO\\FP\\MOSHA\\start button.png"), wxBITMAP_TYPE_PNG);
	start = new wxBitmap(image);
}

void MOSHA::LoadbuttonWindowBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxMessageOutputDebug().Printf("Gambarnya di %s", fileLocation);

	wxImage image(wxT("E:\\Kuliah\\SEM 3\\PBO\\FP\\MOSHA\\button window.png"), wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);
}
void MOSHA::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);
	if (buttonWindow != nullptr) {
		pdc.DrawBitmap(*buttonWindow, wxPoint(0,506),true);
		if (ganti == 0) {
			pdc.DrawBitmap(*menu, wxPoint(0,0), true);
			pdc.DrawBitmap(*start, wxPoint(108,603), true);
		}
	}
	
}

void MOSHA::OnChar(wxKeyEvent &event) {
	r = event.GetKeyCode();
	wxMessageOutputDebug().Printf("Keyboard diteken, Keycode = %d", r);
}
