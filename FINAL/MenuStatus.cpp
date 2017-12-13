#include "MenuStatus.h"
#include "Hero.h"
#include "Resource.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>
#include <string.h>
#include <vector>


BEGIN_EVENT_TABLE(MenuStatus, wxWindow)
EVT_PAINT(MenuStatus::OnPaint)
EVT_BUTTON(1001, MenuStatus::OnClickExit)
//EVT_BUTTON(1007, MenuUpgrade::OnClickStatus)
EVT_BUTTON(1008, MenuStatus::OnClickBond)
EVT_BUTTON(1009, MenuStatus::OnClickInvent)
EVT_BUTTON(1010, MenuStatus::OnClickUpgrade)
END_EVENT_TABLE()

MenuStatus::MenuStatus(ImageFrame * parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	mirai = Hero::getInstance();
	rs = Resource::getInstance();
	LoadAllBitmap();

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *rs->bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *rs->bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *rs->bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *rs->bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);

	wxBitmapButton *buttonexit = new wxBitmapButton(this, 1001, *exit, wxPoint(398, 10), wxDefaultSize, wxBORDER_NONE);
}

MenuStatus::~MenuStatus()
{
	delete layoutstatus, exit, chibistatus;
	delete skillattack, skillshield, skillheal;
	delete txtattack, txtshield, txtheal;
}

void MenuStatus::OnPaint(wxPaintEvent & event)
{
	vector<char> mirainama(mirai->name.begin(), mirai->name.end());

	wxPaintDC pdc(this);
	pdc.DrawBitmap(*rs->mapblur, wxPoint(0, 0), true);
	pdc.DrawBitmap(*rs->buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*rs->chibi, wxPoint(28, 488), true);
	pdc.DrawBitmap(*layoutstatus, wxPoint(56, 1));
	pdc.DrawBitmap(*chibistatus, wxPoint(96, 88));
	pdc.DrawBitmap(*level, wxPoint(260, 221), true);
	pdc.DrawBitmap(*description, wxPoint(151, 493), true);

	pdc.DrawBitmap(*skillattack, wxPoint(110, 329), true);
	pdc.DrawBitmap(*skillshield, wxPoint(212, 329), true);
	pdc.DrawBitmap(*skillheal, wxPoint(313, 329), true);
	pdc.DrawBitmap(*txtattack, wxPoint(116, 291), true);
	pdc.DrawBitmap(*txtshield, wxPoint(227, 298), true);
	pdc.DrawBitmap(*txtheal, wxPoint(322, 289), true);

	wxFont font(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	pdc.SetFont(font);
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skillatt), wxPoint(130, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skilldef), wxPoint(236, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skillheal), wxPoint(340, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->level), wxPoint(350, 223));
	pdc.DrawBitmap(*exit, wxPoint(398, 8), true);

	int i, x, n, y, o;
	x = 260; y = 192; o = mirainama.size();
	for (i = 0; i < o; i++) {
		if (mirainama[i] < 65 || mirainama[i]>122) continue;
		n = mirainama[i] - '0';
		n -= 16;
		pdc.DrawBitmap(*rs->huruf[n], wxPoint(x, y), true);
		x += 16;
	}
}

void MenuStatus::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Menu Status clicked exit!");
	parentFrame->ShowMap();
}

void MenuStatus::OnClickInvent(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void MenuStatus::OnClickBond(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on bonds");
	parentFrame->ShowMenuBonds();
}

void MenuStatus::OnClickUpgrade(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on upgrade");
	parentFrame->ShowMenuUpgrade();
}

void MenuStatus::LoadAllBitmap()
{
	LoadStatusBitmap();
	LoadSkillBitmap();
}

void MenuStatus::LoadStatusBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString location1 = wxFileName(fileLocation).GetPath() + wxT("\\menu status.png");
	wxImage image1(location1, wxBITMAP_TYPE_PNG);
	layoutstatus = new wxBitmap(image1);

	wxString loc2 = wxFileName(fileLocation).GetPath() + wxT("\\exit button.png");
	wxImage image2(loc2, wxBITMAP_TYPE_PNG);
	exit = new wxBitmap(image2);

	wxString loc3 = wxFileName(fileLocation).GetPath() + wxT("\\chibistatus.png");
	wxImage image3(loc3, wxBITMAP_TYPE_PNG);
	chibistatus = new wxBitmap(image3);

	wxString lochp = wxFileName(fileLocation).GetPath() + wxT("\\tulisan level.png");
	wxImage image4(lochp, wxBITMAP_TYPE_PNG);
	level = new wxBitmap(image4);

	wxString locdes = wxFileName(fileLocation).GetPath() + wxT("\\status description.png");
	wxImage image5(locdes, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image5);
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
