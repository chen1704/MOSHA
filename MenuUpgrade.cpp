#include "MenuUpgrade.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>

BEGIN_EVENT_TABLE(MenuUpgrade, wxWindow)
EVT_PAINT(MenuUpgrade::OnPaint)
EVT_BUTTON(1001, MenuUpgrade::OnClickExit)
EVT_BUTTON(1007, MenuUpgrade::OnClickStatus)
EVT_BUTTON(1008, MenuUpgrade::OnClickBond)
EVT_BUTTON(1009, MenuUpgrade::OnClickInvent)
EVT_BUTTON(1011, MenuUpgrade::OnClickUpgradeAttack)
EVT_BUTTON(1012, MenuUpgrade::OnClickUpgradeShield)
EVT_BUTTON(1013, MenuUpgrade::OnClickUpgradeHeal)
END_EVENT_TABLE()

MenuUpgrade::MenuUpgrade(ImageFrame *parent) : wxWindow(parent, wxID_ANY), parentFrame(parent) {
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	LoadAllBitmap();
	LoadRequirement();
	mirai = Hero::getInstance();

	buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);
	buttonexit = new wxBitmapButton(this, 1001, *bitmapexit, wxPoint(397, 8), wxDefaultSize, wxBORDER_NONE);

	buy1 = new wxBitmapButton(this, 1011, *bitmapbuy1, wxPoint(339, 115), wxDefaultSize, wxBORDER_MASK);
	buy2 = new wxBitmapButton(this, 1012, *bitmapbuy2, wxPoint(341, 224), wxDefaultSize, wxBORDER_MASK);
	buy3 = new wxBitmapButton(this, 1013, *bitmapbuy3, wxPoint(344, 343), wxDefaultSize, wxBORDER_MASK);
}


MenuUpgrade::~MenuUpgrade(){
	delete map, buttonwindow, upgrade, chibi, moneypanel, description;
	delete buttonstatus, buttoninvent, buttonskill, buttonbonds;
	delete upattack, upshield, uppotion;
	delete tupattack, tupshield, tuppotion;
	delete attackitem1, attackitem2, shielditem1, shielditem2, potionitem1, potionitem2;
}

void MenuUpgrade::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);

	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonwindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*upgrade, wxPoint(55, -1), true);
	pdc.DrawBitmap(*chibi, wxPoint(30, 490), true);
	pdc.DrawBitmap(*moneypanel, wxPoint(296, 58), true);
	pdc.DrawBitmap(*description, wxPoint(141, 490), true);
	pdc.DrawBitmap(*upattack, wxPoint(100,95), true);
	pdc.DrawBitmap(*upshield, wxPoint(100, 208), true);
	pdc.DrawBitmap(*uppotion, wxPoint(100, 327), true);
	pdc.DrawBitmap(*tupattack, wxPoint(192,100), true);
	pdc.DrawBitmap(*tupshield, wxPoint(194, 210), true);
	pdc.DrawBitmap(*tuppotion, wxPoint(192, 326), true);
	pdc.DrawBitmap(*attackitem1, wxPoint(191,125), true);
	pdc.DrawBitmap(*attackitem2, wxPoint(247, 124), true);
	pdc.DrawBitmap(*shielditem1, wxPoint(193, 237), true);
	pdc.DrawBitmap(*shielditem2, wxPoint(253, 237), true);
	pdc.DrawBitmap(*potionitem1, wxPoint(191, 350), true);
	pdc.DrawBitmap(*potionitem2, wxPoint(253, 350), true);
	pdc.DrawBitmap(*money1, wxPoint(309, 142), true);
	pdc.DrawBitmap(*money1, wxPoint(309, 260), true);
	pdc.DrawBitmap(*money1, wxPoint(309, 370), true);

	wxFont font(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD); //default-bold
	pdc.SetFont(font);
	pdc.DrawText(wxString::Format("%d", mirai->money), wxPoint(341, 73));

	//draw requirement
	pdc.SetTextForeground(*wxWHITE);
	pdc.DrawText(wxString::Format("%d", rbalok), wxPoint(207, 180));
	pdc.DrawText(wxString::Format("%d", rbatu), wxPoint(268, 180));
	pdc.DrawText(wxString::Format("%d", rbara), wxPoint(207, 296));
	pdc.DrawText(wxString::Format("%d", rkayu), wxPoint(270, 296));
	pdc.DrawText(wxString::Format("%d", rtanah), wxPoint(207, 406));
	pdc.DrawText(wxString::Format("%d", rdiamond), wxPoint(268, 406));

	//draw money requirement
	pdc.DrawText(wxString::Format("%d", moneyatt), wxPoint(349, 156));
	pdc.DrawText(wxString::Format("%d", moneydef), wxPoint(353, 267));
	pdc.DrawText(wxString::Format("%d", moneyheal), wxPoint(354, 386));

}

void MenuUpgrade::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Exit Clicked");
	parentFrame->ShowMap();
}

void MenuUpgrade::OnClickStatus(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on status");
	parentFrame->ShowMenuStatus();
}

void MenuUpgrade::OnClickBond(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on bonds");
	parentFrame->ShowMenuBonds();
}

void MenuUpgrade::OnClickInvent(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void MenuUpgrade::OnClickUpgradeAttack(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("upgrade attack");
	if (mirai->itmlog >= rbalok && mirai->itmstone >= rbatu && mirai->money >= moneyatt) {
		mirai->skillatt += 5;
		mirai->itmlog -= rbalok; mirai->itmstone -= rbatu; mirai->money -= moneyatt;
		rbalok++; rbatu++; moneyatt += 50;
		Refresh();
	}
	else
		wxMessageBox(wxT("Your have not fullfill the requirements!"), wxT("Warning!"), wxICON_STOP);
	
}

void MenuUpgrade::OnClickUpgradeShield(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("upgrade shield");
	if (mirai->itmbrick >= rbara && mirai->itmwood >= rkayu && mirai->money >= moneydef) {
		mirai->skilldef += 2;
		mirai->itmbrick -= rbara; mirai->itmwood -= rkayu; mirai->money -= moneydef;
		rbara++; rkayu++; moneydef += 50;
		Refresh();
	}
	else
		wxMessageBox(wxT("Your have not fullfill the requirements!"), wxT("Warning!"), wxICON_STOP);
}

void MenuUpgrade::OnClickUpgradeHeal(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("upgrade heal");
	if (mirai->itmearth >= rtanah && mirai->itmdia >= rdiamond&&mirai->money >= moneyheal) {
		mirai->skillheal += 10;
		mirai->itmearth -= rtanah; mirai->itmdia -= rdiamond; mirai->money -= moneyheal;
		rtanah++; rkayu++; moneyheal += 100;
		Refresh();
	}
	else
		wxMessageBox(wxT("Your have not fullfill the requirements!"), wxT("Warning!"), wxICON_STOP);
}

void MenuUpgrade::LoadRequirement()
{
	rbalok = 2; rbatu = 3; moneyatt = 50;
	rbara = 2; rkayu = 3; moneydef = 50;
	rtanah = 3; rdiamond = 3; moneyheal = 100;
}

void MenuUpgrade::LoadAllBitmap() {
	this->LoadMapBitmap();
	this->LoadMenuBitmap();
	this->LoadUpgradeBitmap();
	this->LoadUpgradeItemBitmap();
}

void MenuUpgrade::LoadMapBitmap() {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - blur.png");
	wxImage image(locationmap, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image1(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonwindow = new wxBitmap(image1);

	wxString locbondwindow = wxFileName(fileLocation).GetPath() + wxT("\\menu upgrade.png");
	wxImage image2(locbondwindow, wxBITMAP_TYPE_PNG);
	upgrade = new wxBitmap(image2);

	wxString locchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image3(locchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image3);

	wxString locmoneypan = wxFileName(fileLocation).GetPath() + wxT("\\money panel.png");
	wxImage image4(locmoneypan, wxBITMAP_TYPE_PNG);
	moneypanel = new wxBitmap(image4);

	wxString lochp = wxFileName(fileLocation).GetPath() + wxT("\\upgrade description.png");
	wxImage image5(lochp, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image5);

	wxString locbuy1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade buybutton attack.png");
	wxImage image6(locbuy1, wxBITMAP_TYPE_PNG);
	bitmapbuy1 = new wxBitmap(image6);

	wxString locbuy2 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade buybutton shield.png");
	wxImage image7(locbuy2, wxBITMAP_TYPE_PNG);
	bitmapbuy2 = new wxBitmap(image7);

	wxString locbuy3 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade buybutton heal.png");
	wxImage image8(locbuy3, wxBITMAP_TYPE_PNG);
	bitmapbuy3 = new wxBitmap(image8);
}

void MenuUpgrade::LoadMenuBitmap() {
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

	wxString locexit = wxFileName(fileLocation).GetPath() + wxT("\\exit button1.png");
	wxImage image5(locexit, wxBITMAP_TYPE_PNG);
	bitmapexit = new wxBitmap(image5);
}

void MenuUpgrade::LoadUpgradeBitmap() {
	wxString locupattack = wxFileName(fileLocation).GetPath() + wxT("\\upgrade attack.png");
	wxImage image1(locupattack, wxBITMAP_TYPE_PNG);
	upattack = new wxBitmap(image1);

	wxString locupshield = wxFileName(fileLocation).GetPath() + wxT("\\upgrade shield.png");
	wxImage image2(locupshield, wxBITMAP_TYPE_PNG);
	upshield = new wxBitmap(image2);

	wxString locupheal = wxFileName(fileLocation).GetPath() + wxT("\\upgrade potion.png");
	wxImage image3(locupheal, wxBITMAP_TYPE_PNG);
	uppotion = new wxBitmap(image3);

	wxString loctupattack = wxFileName(fileLocation).GetPath() + wxT("\\tulisan upgrade attack.png");
	wxImage image4(loctupattack, wxBITMAP_TYPE_PNG);
	tupattack = new wxBitmap(image4);

	wxString loctupshield = wxFileName(fileLocation).GetPath() + wxT("\\tulisan upgrade shield.png");
	wxImage image5(loctupshield, wxBITMAP_TYPE_PNG);
	tupshield = new wxBitmap(image5);

	wxString loctupheal = wxFileName(fileLocation).GetPath() + wxT("\\tulisan upgrade heal.png");
	wxImage image6(loctupheal, wxBITMAP_TYPE_PNG);
	tuppotion = new wxBitmap(image6);
}

void MenuUpgrade::LoadUpgradeItemBitmap() {
	wxString locattacki1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item 1 attack.png");
	wxImage image1(locattacki1, wxBITMAP_TYPE_PNG);
	attackitem1 = new wxBitmap(image1);

	wxString locattacki2 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item 2 attack.png");
	wxImage image2(locattacki2, wxBITMAP_TYPE_PNG);
	attackitem2 = new wxBitmap(image2);

	wxString locshieli1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item1 shield.png");
	wxImage image3(locshieli1, wxBITMAP_TYPE_PNG);
	shielditem1 = new wxBitmap(image3);

	wxString locshieli2 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item2 shield.png");
	wxImage image4(locshieli2, wxBITMAP_TYPE_PNG);
	shielditem2 = new wxBitmap(image4);

	wxString locheali1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item1 heal.png");
	wxImage image5(locheali1, wxBITMAP_TYPE_PNG);
	potionitem1 = new wxBitmap(image5);

	wxString locheali2 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade item2 heal.png");
	wxImage image6(locheali2, wxBITMAP_TYPE_PNG);
	potionitem2 = new wxBitmap(image6);

	wxString locmoney1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade money.png");
	wxImage image7(locmoney1, wxBITMAP_TYPE_PNG);
	money1 = new wxBitmap(image7);
}
