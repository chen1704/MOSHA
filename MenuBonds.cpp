#include "MenuBonds.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>

BEGIN_EVENT_TABLE(MenuBonds, wxWindow)
EVT_PAINT(MenuBonds::OnPaint)
EVT_BUTTON(1001, MenuBonds::OnClickExit)
EVT_BUTTON(1011, MenuBonds::OnClickShimura)
EVT_BUTTON(1012, MenuBonds::OnClickHijikata)
EVT_BUTTON(1013, MenuBonds::OnClickSakata)
EVT_BUTTON(1007, MenuBonds::OnClickStatus)
//EVT_BUTTON(1008, Map::ClickButtonBonds)
EVT_BUTTON(1009, MenuBonds::OnClickInvent)
EVT_BUTTON(1010, MenuBonds::OnClickUpgrade)
END_EVENT_TABLE()

MenuBonds::MenuBonds(ImageFrame *parent) : wxWindow(parent, wxID_ANY), parentFrame(parent) {
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	mirai = Hero::getInstance();

	LoadAllBitmap();

	buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);
	buttonexit = new wxBitmapButton(this, 1001, *bitmapexit, wxPoint(397, 8), wxDefaultSize, wxBORDER_NONE);

	rewardshimura = new wxBitmapButton(this, 1011, *claim, wxPoint(339, 100), wxDefaultSize, wxBORDER_NONE);
	rewardhijikata = new wxBitmapButton(this, 1012, *claim, wxPoint(88, 233), wxDefaultSize, wxBORDER_NONE);
	rewardsakata = new wxBitmapButton(this, 1013, *claim, wxPoint(338, 352
	), wxDefaultSize, wxBORDER_NONE);

}

MenuBonds::~MenuBonds() {
	delete map, buttonwindow, buttonbonds, buttoninvent, buttonskill, buttonstatus;
	delete shimura, hijikata, sakata, namesakata, nameshimura, namehijikata;
	delete heartfull, heartnull, hearthalf;
	delete chibi, bond;
}

void MenuBonds::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);

	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonwindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*bond, wxPoint(55, -1), true);
	pdc.DrawBitmap(*chibi, wxPoint(30, 490), true);
	pdc.DrawBitmap(*description, wxPoint(142, 494), true);
	pdc.DrawBitmap(*shimura, wxPoint(94, 71), true);
	pdc.DrawBitmap(*hijikata, wxPoint(281, 175), true);
	pdc.DrawBitmap(*sakata, wxPoint(94, 288), true);
	pdc.DrawBitmap(*nameshimura, wxPoint(210, 93), true);
	pdc.DrawBitmap(*namehijikata, wxPoint(177, 221), true); //atau 171
	pdc.DrawBitmap(*namesakata, wxPoint(215, 341), true);

	//drawnullheart on three boys
	//shimura null
	pdc.DrawBitmap(*heartnull, wxPoint(212, 126), true);
	pdc.DrawBitmap(*heartnull, wxPoint(252, 126), true);
	pdc.DrawBitmap(*heartnull, wxPoint(292, 126), true);
	//hijikata null
	pdc.DrawBitmap(*heartnull, wxPoint(154, 249), true);
	pdc.DrawBitmap(*heartnull, wxPoint(194, 249), true);
	pdc.DrawBitmap(*heartnull, wxPoint(234, 249), true);
	//sakata null
	pdc.DrawBitmap(*heartnull, wxPoint(212, 368), true);
	pdc.DrawBitmap(*heartnull, wxPoint(252, 368), true);
	pdc.DrawBitmap(*heartnull, wxPoint(292, 368), true);

	//bond +1
	if (mirai->bondshi == 1) pdc.DrawBitmap(*hearthalf, wxPoint(212, 126));
	if (mirai->bondhij == 1) pdc.DrawBitmap(*hearthalf, wxPoint(154, 249));
	if (mirai->bondsak == 1) pdc.DrawBitmap(*hearthalf, wxPoint(212, 368));

	//bond + 2
	if (mirai->bondshi == 2) pdc.DrawBitmap(*heartfull, wxPoint(212, 126));
	if (mirai->bondhij == 2) pdc.DrawBitmap(*heartfull, wxPoint(154, 249));
	if (mirai->bondsak == 2) pdc.DrawBitmap(*heartfull, wxPoint(252, 368));

	//bond +3
	if (mirai->bondshi == 3) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 126));
		pdc.DrawBitmap(*hearthalf, wxPoint(252, 126));
	}
	if (mirai->bondhij == 3) {
		pdc.DrawBitmap(*heartfull, wxPoint(154, 249));
		pdc.DrawBitmap(*hearthalf, wxPoint(194, 249));
	}
	if (mirai->bondsak == 3) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 368));
		pdc.DrawBitmap(*hearthalf, wxPoint(252, 368));
	}

	//bond+4
	if (mirai->bondshi == 4) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 126));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 126));
	}
	if (mirai->bondhij == 4) {
		pdc.DrawBitmap(*heartfull, wxPoint(154, 249));
		pdc.DrawBitmap(*heartfull, wxPoint(194, 249));
	}
	if (mirai->bondsak == 4) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 368));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 368));
	}

	//bond+5
	if (mirai->bondshi == 5) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 126));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 126));
		pdc.DrawBitmap(*hearthalf, wxPoint(292, 126));
	}
	if (mirai->bondhij == 5) {
		pdc.DrawBitmap(*heartfull, wxPoint(154, 249));
		pdc.DrawBitmap(*heartfull, wxPoint(194, 249));
		pdc.DrawBitmap(*hearthalf, wxPoint(234, 249));
	}
	if (mirai->bondsak == 5) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 368));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 368));
		pdc.DrawBitmap(*hearthalf, wxPoint(292, 368));
	}

	//bond +6
	if (mirai->bondshi == 6) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 126));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 126));
		pdc.DrawBitmap(*heartfull, wxPoint(292, 126));
	}
	if (mirai->bondhij == 6) {
		pdc.DrawBitmap(*heartfull, wxPoint(154, 249));
		pdc.DrawBitmap(*heartfull, wxPoint(194, 249));
		pdc.DrawBitmap(*heartfull, wxPoint(234, 249));
	}
	if (mirai->bondsak == 6) {
		pdc.DrawBitmap(*heartfull, wxPoint(212, 368));
		pdc.DrawBitmap(*heartfull, wxPoint(252, 368));
		pdc.DrawBitmap(*heartfull, wxPoint(292
			, 368));
	}

}

void MenuBonds::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Exit Clicked");
	parentFrame->ShowMap();
}

void MenuBonds::OnClickShimura(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("Get Reward from Shimura");
}

void MenuBonds::OnClickHijikata(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("Get Reward from Hijikata");
}

void MenuBonds::OnClickSakata(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("Get Reward from Sakata");
}

void MenuBonds::OnClickStatus(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on status");
	parentFrame->ShowMenuStatus();
}

void MenuBonds::OnClickInvent(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}


void MenuBonds::OnClickUpgrade(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on upgrade skill");
	parentFrame->ShowMenuUpgrade();
}


void MenuBonds::LoadAllBitmap() {
	this->LoadMapBitmap();
	this->LoadMenuBitmap();
	this->LoadBondsBitmap();
}

void MenuBonds::LoadMapBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - blur.png");
	wxImage image(locationmap, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image1(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonwindow = new wxBitmap(image1);

	wxString locbondwindow = wxFileName(fileLocation).GetPath() + wxT("\\menu bonds.png");
	wxImage image2(locbondwindow, wxBITMAP_TYPE_PNG);
	bond = new wxBitmap(image2);

	wxString locchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image3(locchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image3);

	wxString locdes = wxFileName(fileLocation).GetPath() + wxT("\\bond description.png");
	wxImage image4(locdes, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image4);
	//chibi sprites
	//menu bonds
}

void MenuBonds::LoadMenuBitmap() {
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

	wxString locexit = wxFileName(fileLocation).GetPath() + wxT("\\exit button.png");
	wxImage image5(locexit, wxBITMAP_TYPE_PNG);
	bitmapexit = new wxBitmap(image5);
}

void MenuBonds::LoadBondsBitmap() {
	wxString locshimura = wxFileName(fileLocation).GetPath() + wxT("\\bond shimura.png");
	wxImage image1(locshimura, wxBITMAP_TYPE_PNG);
	shimura = new wxBitmap(image1);

	wxString lochijikata = wxFileName(fileLocation).GetPath() + wxT("\\bond hijikata.png");
	wxImage image2(lochijikata, wxBITMAP_TYPE_PNG);
	hijikata = new wxBitmap(image2);

	wxString locsakata = wxFileName(fileLocation).GetPath() + wxT("\\bond sakata.png");
	wxImage image3(locsakata, wxBITMAP_TYPE_PNG);
	sakata = new wxBitmap(image3);

	wxString locnshimura = wxFileName(fileLocation).GetPath() + wxT("\\name shimura.png");
	wxImage image4(locnshimura, wxBITMAP_TYPE_PNG);
	nameshimura = new wxBitmap(image4);

	wxString locnhijikata = wxFileName(fileLocation).GetPath() + wxT("\\name hijikata.png");
	wxImage image5(locnhijikata, wxBITMAP_TYPE_PNG);
	namehijikata = new wxBitmap(image5);

	wxString locnsakata = wxFileName(fileLocation).GetPath() + wxT("\\name sakata.png");
	wxImage image6(locnsakata, wxBITMAP_TYPE_PNG);
	namesakata = new wxBitmap(image6);

	wxString hnull = wxFileName(fileLocation).GetPath() + wxT("\\bond heart bar null.png");
	wxImage image7(hnull, wxBITMAP_TYPE_PNG);
	heartnull = new wxBitmap(image7);

	wxString hhalf = wxFileName(fileLocation).GetPath() + wxT("\\bond heart bar half.png");
	wxImage image8(hhalf, wxBITMAP_TYPE_PNG);
	hearthalf = new wxBitmap(image8);

	wxString hfull = wxFileName(fileLocation).GetPath() + wxT("\\bond heart bar full.png");
	wxImage image9(hfull, wxBITMAP_TYPE_PNG);
	heartfull = new wxBitmap(image9);
	
	wxString locclaim = wxFileName(fileLocation).GetPath() + wxT("\\bond claim.png");
	wxImage image10(locclaim, wxBITMAP_TYPE_PNG);
	claim = new wxBitmap(image10);
}
