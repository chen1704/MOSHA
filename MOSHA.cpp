#include "MOSHA.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "wx/bmpbuttn.h"

BEGIN_EVENT_TABLE(MOSHA, wxWindow)
EVT_PAINT(MOSHA::OnPaint)
EVT_CHAR(MOSHA::OnChar)
EVT_BUTTON(1001, MOSHA::ClickStart)
END_EVENT_TABLE()

MOSHA::MOSHA(wxFrame *parent) : wxWindow(parent, wxID_ANY) {
	this->state = 0;
	this->SetBackgroundColour(wxColour(*wxWHITE));
	panel = new wxPanel(this, 1001, wxPoint(100, 520), wxSize(300, 110));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->LoadMenuBitmap();
	this->LoadbuttonWindowBitmap();

	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
	start = new wxBitmap(image);
	wxBitmapButton* startbutton = new wxBitmapButton(panel, 1001, image, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);


}


MOSHA::~MOSHA()
{
	delete menu;
	delete start;
	delete buttonWindow;
}

void MOSHA::LoadMenuBitmap() {
	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\menu awal.png"), wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image);
}

void MOSHA::LoadMapButton() {
	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\MAP - FIX.png"), wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);
}

void MOSHA::LoadStartButton() {
		//	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
	//	start = new wxBitmap(image);
	//	wxBitmap bitmap(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\start button.png"), wxBITMAP_TYPE_PNG);
	//	wxBitmapButton* startbutton = new wxBitmapButton(panel, wxID_OK, bitmap, wxPoint(108, 526),
	//		wxSize(286,101), wxBU_AUTODRAW);
}

void MOSHA::ClickStart(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("di klik di start");
	this->state = 1;
	Refresh();
	this->LoadMapButton();

}

void MOSHA::LoadbuttonWindowBitmap() {
	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\button window.png"), wxBITMAP_TYPE_PNG);
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
	}
//	wxMessageOutputDebug().Printf("Halo");


}


void MOSHA::OnChar(wxKeyEvent &event) {
	wxMessageOutputDebug().Printf("Keyboard diteken, Keycode = %d", event.GetKeyCode());
}
