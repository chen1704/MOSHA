#include "MenuBonds.h"
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


MenuBonds::MenuBonds(ImageFrame * parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	
	mirai = Hero::getInstance();
	rs = Resource::getInstance();
	LoadAllBitmap();

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *rs->bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *rs->bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *rs->bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *rs->bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);

	wxBitmapButton *buttonexit = new wxBitmapButton(this, 1001, *exit, wxPoint(397, 8), wxDefaultSize, wxBORDER_NONE);

	rewardshimura = new wxBitmapButton(this, 1011, *claim, wxPoint(339, 100), wxDefaultSize, wxBORDER_NONE);
	rewardhijikata = new wxBitmapButton(this, 1012, *claim, wxPoint(88, 233), wxDefaultSize, wxBORDER_NONE);
	rewardsakata = new wxBitmapButton(this, 1013, *claim, wxPoint(338, 352), wxDefaultSize, wxBORDER_NONE);
}

MenuBonds::~MenuBonds()
{
	delete bond, description, exit;
	delete shimura, hijikata, sakata;
	delete nameshimura, namehijikata, namesakata;
	delete heartnull, hearthalf, heartfull, claim;
	delete rewardshimura, rewardhijikata, rewardsakata;
}

void MenuBonds::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);

	pdc.DrawBitmap(*rs->mapblur, wxPoint(0, 0), true);
	pdc.DrawBitmap(*rs->buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*bond, wxPoint(55, -1), true);
	pdc.DrawBitmap(*rs->chibi, wxPoint(30, 490), true);
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
		pdc.DrawBitmap(*heartfull, wxPoint(292, 368));
	}
}

void MenuBonds::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Menu Bond click Exit");
	parentFrame->ShowMap();
}

void MenuBonds::OnClickShimura(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Get Reward from Shimura");
	if (mirai->bondshi == 6) {
		mirai->skillheal += 10;
		rewardshimura->Enable(false);
	}
	else
		wxMessageBox(wxT("Your bond with Shimura has not full yet!"), wxT("Warning!"), wxICON_STOP);
}

void MenuBonds::OnClickHijikata(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Get Reward from Hijikata");
	if (mirai->bondhij == 6) {
		mirai->skillatt += 15;
		rewardhijikata->Enable(false);
	}
	else
		wxMessageBox(wxT("Your bond with Hijikata has not full yet!"), wxT("Warning!"), wxICON_STOP);
}

void MenuBonds::OnClickSakata(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Get Reward from Sakata");
	if (mirai->bondsak == 6) {
		mirai->skilldef += 25;
		rewardsakata->Enable(false);
	}
	else
		wxMessageBox(wxT("Your bond with Sakata has not full yet!"), wxT("Warning!"), wxICON_STOP);
}

void MenuBonds::OnClickStatus(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on status");
	parentFrame->ShowMenuStatus();
}

void MenuBonds::OnClickInvent(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void MenuBonds::OnClickUpgrade(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on upgrade skill");
	parentFrame->ShowMenuUpgrade();
}

void MenuBonds::LoadAllBitmap()
{
	LoadBondBitmap();
	LoadPrinceBitmap();
	LoadHeartBitmap();
}

void MenuBonds::LoadBondBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locbondwindow = wxFileName(fileLocation).GetPath() + wxT("\\menu bonds.png");
	wxImage image2(locbondwindow, wxBITMAP_TYPE_PNG);
	bond = new wxBitmap(image2);
	wxString locdes = wxFileName(fileLocation).GetPath() + wxT("\\bond description.png");
	wxImage image4(locdes, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image4);
	wxString locexit = wxFileName(fileLocation).GetPath() + wxT("\\exit button.png");
	wxImage image5(locexit, wxBITMAP_TYPE_PNG);
	exit = new wxBitmap(image5);
}

void MenuBonds::LoadPrinceBitmap()
{
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
}

void MenuBonds::LoadHeartBitmap()
{
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
