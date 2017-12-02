#include "MenuStatus.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Hero.h"

BEGIN_EVENT_TABLE(MenuStatus, wxWindow)
EVT_PAINT(MenuStatus::OnPaint)
EVT_BUTTON(1001, MenuStatus::OnClickExit)
END_EVENT_TABLE()

MenuStatus::MenuStatus(ImageFrame *parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	LoadAllBitmap();

	mirai = Hero::getInstance();


	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(40, 630), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(165, 627), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(270, 628), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(380, 625), wxDefaultSize, wxBORDER_MASK);

	wxBitmapButton *buttonexit = new wxBitmapButton(this, 1001, *exit, wxPoint(398, 10),wxDefaultSize,wxBORDER_NONE);
}


MenuStatus::~MenuStatus()
{
	delete map, buttonWindow, chibi;
	delete bitmapstatus, bitmapbonds, bitmapinvent, bitmapskill;
	delete layoutstatus, exit, chibistatus;
	delete skillattack, skillshield, skillheal;
	delete txtattack, txtshield, txtheal;
//	delete convatt, convdef, convheal;

}

void MenuStatus::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*chibi, wxPoint(28, 488), true);
	pdc.DrawText(mirai->name, wxPoint(160, 480));
	pdc.DrawBitmap(*layoutstatus, wxPoint(56, 1));
	pdc.DrawBitmap(*chibistatus, wxPoint(96, 88));

	pdc.DrawBitmap(*skillattack, wxPoint(110, 329), true);
	pdc.DrawBitmap(*skillshield, wxPoint(212, 329), true);
	pdc.DrawBitmap(*skillheal, wxPoint(313, 329), true);
	pdc.DrawBitmap(*txtattack, wxPoint(116, 291), true);
	pdc.DrawBitmap(*txtshield, wxPoint(227, 298), true);
	pdc.DrawBitmap(*txtheal, wxPoint(322, 289), true);
	pdc.DrawText(wxString::Format(wxT("%d"),mirai->skillatt), wxPoint(128, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skilldef), wxPoint(238, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skillheal), wxPoint(338, 404));
	pdc.DrawBitmap(*exit, wxPoint(398, 8), true);


}

void MenuStatus::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Menu Status clicked exit!");
	parentFrame->ShowMap();
}

void MenuStatus::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadUpgradeBitmap();
	this->LoadbuttonWindowBitmap();
	this->LoadSkillBitmap();
}

void MenuStatus::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - blur.png");
	wxImage image(locationmap, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString location1 = wxFileName(fileLocation).GetPath() + wxT("\\menu status.png");
	wxImage image1(location1, wxBITMAP_TYPE_PNG);
	layoutstatus = new wxBitmap(image1);

	wxString loc2 = wxFileName(fileLocation).GetPath() + wxT("\\exit button.png");
	wxImage image2(loc2, wxBITMAP_TYPE_PNG);
	exit = new wxBitmap(image2);

	wxString loc3 = wxFileName(fileLocation).GetPath() + wxT("\\chibistatus.png");
	wxImage image3(loc3, wxBITMAP_TYPE_PNG);
	chibistatus = new wxBitmap(image3);
}

void MenuStatus::LoadbuttonWindowBitmap()
{
	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);

	wxString locationchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image1(locationchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image1);
}

void MenuStatus::LoadUpgradeBitmap()
{
	wxString locstatus = wxFileName(fileLocation).GetPath() + wxT("\\button status.png");
	wxImage image1(locstatus, wxBITMAP_TYPE_PNG);
	bitmapstatus = new wxBitmap(image1);

	wxString locbond = wxFileName(fileLocation).GetPath() + wxT("\\button bonds.png");
	wxImage image2(locbond, wxBITMAP_TYPE_PNG);
	bitmapbonds = new wxBitmap(image2);

	wxString locinven = wxFileName(fileLocation).GetPath() + wxT("\\button inventory.png");
	wxImage image3(locinven, wxBITMAP_TYPE_PNG);
	bitmapinvent = new wxBitmap(image3);

	wxString locskill = wxFileName(fileLocation).GetPath() + wxT("\\button upgrade.png");
	wxImage image4(locskill, wxBITMAP_TYPE_PNG);
	bitmapskill = new wxBitmap(image4);
}

void MenuStatus::LoadSkillBitmap()
{
	wxString locmap1 = wxFileName(fileLocation).GetPath() + wxT("\\status critical.png");
	wxImage image1(locmap1, wxBITMAP_TYPE_PNG);
	skillattack = new wxBitmap(image1);

	wxString locmap2 = wxFileName(fileLocation).GetPath() + wxT("\\status shield.png");
	wxImage image2(locmap2, wxBITMAP_TYPE_PNG);
	skillshield = new wxBitmap(image2);

	wxString locmap3 = wxFileName(fileLocation).GetPath() + wxT("\\status heal.png");
	wxImage image3(locmap3, wxBITMAP_TYPE_PNG);
	skillheal = new wxBitmap(image3);

	wxString locmap4 = wxFileName(fileLocation).GetPath() + wxT("\\tulisan-critattack.png");
	wxImage image4(locmap4, wxBITMAP_TYPE_PNG);
	txtattack = new wxBitmap(image4);

	wxString locmap5 = wxFileName(fileLocation).GetPath() + wxT("\\tulisan-shield.png");
	wxImage image5(locmap5, wxBITMAP_TYPE_PNG);
	txtshield = new wxBitmap(image5);

	wxString locmap6 = wxFileName(fileLocation).GetPath() + wxT("\\tulisan-heal.png");
	wxImage image6(locmap6, wxBITMAP_TYPE_PNG);
	txtheal = new wxBitmap(image6);
}
