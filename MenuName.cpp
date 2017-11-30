#include "MenuName.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

BEGIN_EVENT_TABLE(MenuName, wxWindow)
EVT_PAINT(MenuName::OnPaint)
EVT_BUTTON(1001, MenuName::ClickOK)
END_EVENT_TABLE()

MenuName::MenuName(ImageFrame * parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	LoadAllBitmap();

	NameEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(70, 555), wxSize(100, 35),wxTE_CENTRE | wxTE_RICH);
	NameEntry->SetBackgroundColour(wxColor(*wxYELLOW));
//	NameEntry->SetDefaultStyle(wxTextAttr(wxColor(*wxGREEN), wxColor(*wxBLUE)));

	wxBitmapButton* OKbutton = new wxBitmapButton(this, 1001, *OK, wxPoint(200,570), wxDefaultSize, wxBU_AUTODRAW);
}

MenuName::~MenuName()
{
}

void MenuName::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*menu, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
}

void MenuName::ClickOK(wxCommandEvent & event)
{
	wxString TempName = NameEntry->GetValue();
	wxString anu = wxT("Welcome Hero ") + TempName;
	if (TempName.empty())
	{
		wxMessageBox(wxT("Username must not empty!"), wxT("Warning!"), wxICON_WARNING);
	}
	else {
		wxMessageBox(anu, wxT("Welcome"), wxICON_INFORMATION);
		parentFrame->ShowMap();
	}
	delete menu, buttonWindow, OK;
	
}

void MenuName::LoadAllBitmap()
{
	this->LoadMenuBitmap();
	this->LoadbuttonWindowBitmap();
}

void MenuName::LoadMenuBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString loclogo = wxFileName(fileLocation).GetPath() + wxT("\\menu awal.png");
	wxImage image(loclogo, wxBITMAP_TYPE_PNG);
	menu = new wxBitmap(image);
}

void MenuName::LoadbuttonWindowBitmap()
{
	wxString locwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image(locwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);

	wxString locstart = wxFileName(fileLocation).GetPath() + wxT("\\status button.png");
	wxImage image1(locstart, wxBITMAP_TYPE_PNG);
	OK = new wxBitmap(image1);
}
