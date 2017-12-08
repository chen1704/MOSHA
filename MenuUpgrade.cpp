#include "MenuUpgrade.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>

BEGIN_EVENT_TABLE(MenuUpgrade, wxWindow)
EVT_PAINT(MenuUpgrade::OnPaint)
EVT_BUTTON(1001, MenuUpgrade::OnClickExit)
END_EVENT_TABLE()

MenuUpgrade::MenuUpgrade(ImageFrame *parent) : wxWindow(parent, wxID_ANY), parentFrame(parent) {
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	LoadAllBitmap();
	mirai = Hero::getInstance();

	buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(258, 622), wxDefaultSize, wxBORDER_MASK);
	buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(378, 627), wxDefaultSize, wxBORDER_MASK);
	buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(28, 628), wxDefaultSize, wxBORDER_MASK);
	buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(146, 625), wxDefaultSize, wxBORDER_MASK);
	buttonexit = new wxBitmapButton(this, 1001, *bitmapexit, wxPoint(397, 8), wxDefaultSize, wxBORDER_NONE);
}


MenuUpgrade::~MenuUpgrade(){
	delete map, buttonwindow, upgrade, chibi, moneypanel;
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
	pdc.DrawBitmap(*money2, wxPoint(311, 260), true);
	pdc.DrawBitmap(*money3, wxPoint(314, 370), true);
}

void MenuUpgrade::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Exit Clicked");
	parentFrame->ShowMap();
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

	wxString locmoney1 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade money attack.png");
	wxImage image7(locmoney1, wxBITMAP_TYPE_PNG);
	money1 = new wxBitmap(image7);

	wxString locmoney2 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade money shield.png");
	wxImage image8(locmoney2, wxBITMAP_TYPE_PNG);
	money2 = new wxBitmap(image8);

	wxString locmoney3 = wxFileName(fileLocation).GetPath() + wxT("\\upgrade money heal.png");
	wxImage image9(locmoney3, wxBITMAP_TYPE_PNG);
	money3 = new wxBitmap(image9);
}
