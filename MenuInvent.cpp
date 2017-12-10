#include "MenuInvent.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>

BEGIN_EVENT_TABLE(MenuInvent, wxWindow)
EVT_PAINT(MenuInvent::OnPaint)
EVT_BUTTON(1001, MenuInvent::OnClickExit)
EVT_BUTTON(1007, MenuInvent::OnClickStatus)
EVT_BUTTON(1008, MenuInvent::OnClickBond)
//EVT_BUTTON(1009, MenuInvent::OnClickInvent)
EVT_BUTTON(1010, MenuInvent::OnClickUpgrade)
END_EVENT_TABLE()


MenuInvent::MenuInvent(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	LoadAllBitmap();
	mirai = Hero::getInstance();

	buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);
	buttonexit = new wxBitmapButton(this, 1001, *bitmapexit, wxPoint(397, 8), wxDefaultSize, wxBORDER_NONE);


}

MenuInvent::~MenuInvent()
{
	delete buttonbonds, buttonexit, buttoninvent, buttonskill, buttonstatus;
	delete map, buttonWindow, inventory, chibi;
	delete balok, batu, bara, kayu, tanah, diamond;
}

void MenuInvent::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*inventory, wxPoint(55, -1), true);
	pdc.DrawBitmap(*chibi, wxPoint(30, 490), true);
	pdc.DrawBitmap(*description, wxPoint(140, 487), true);

	//draw bitmap of inventory
	pdc.DrawBitmap(*balok, wxPoint(100, 124), true);
	pdc.DrawBitmap(*bara, wxPoint(204, 124), true);
	pdc.DrawBitmap(*batu, wxPoint(309, 124), true);
	pdc.DrawBitmap(*tanah, wxPoint(100, 254), true);
	pdc.DrawBitmap(*diamond, wxPoint(204, 254), true);
	pdc.DrawBitmap(*kayu, wxPoint(309, 254), true);

	//isi jumlah tiap inventory
	wxFont font(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD); //default-bold
	pdc.SetFont(font);
	pdc.SetTextForeground(*wxWHITE);
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmlog)), wxPoint(130, 223));
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmbrick)), wxPoint(235, 223));
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmstone)), wxPoint(345, 223));
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmearth)), wxPoint(130, 350));
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmdia)), wxPoint(235, 350));
	pdc.DrawText((wxString::Format(wxT("%d"), mirai->itmwood)), wxPoint(345, 350));
}

void MenuInvent::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadMenuBitmap();
	this->LoaditemBitmap();
}

void MenuInvent::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Exit Clicked");
	parentFrame->ShowMap();
}

void MenuInvent::OnClickStatus(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on status");
	parentFrame->ShowMenuStatus();
}

void MenuInvent::OnClickBond(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on bond");
	parentFrame->ShowMenuBonds();
}

void MenuInvent::OnClickUpgrade(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on upgrade skill");
	parentFrame->ShowMenuUpgrade();
}
void MenuInvent::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - blur.png");
	wxImage image(locationmap, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image1(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image1);

	wxString locbondwindow = wxFileName(fileLocation).GetPath() + wxT("\\menu inventory1.png");
	wxImage image2(locbondwindow, wxBITMAP_TYPE_PNG);
	inventory = new wxBitmap(image2);

	wxString locchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image3(locchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image3);

	wxString locdes = wxFileName(fileLocation).GetPath() + wxT("\\inventory description.png");
	wxImage image4(locdes, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image4);
}

void MenuInvent::LoadMenuBitmap()
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

	wxString locexit = wxFileName(fileLocation).GetPath() + wxT("\\exit button1.png");
	wxImage image5(locexit, wxBITMAP_TYPE_PNG);
	bitmapexit = new wxBitmap(image5);
}

void MenuInvent::LoaditemBitmap() {
	wxString loclog = wxFileName(fileLocation).GetPath() + wxT("\\inventory log.png");
	wxImage image1(loclog, wxBITMAP_TYPE_PNG);
	balok = new wxBitmap(image1);

	wxString locrock = wxFileName(fileLocation).GetPath() + wxT("\\inventory batu.png");
	wxImage image2(locrock, wxBITMAP_TYPE_PNG);
	batu = new wxBitmap(image2);

	wxString locbbara = wxFileName(fileLocation).GetPath() + wxT("\\inventory batu bara.png");
	wxImage image3(locbbara, wxBITMAP_TYPE_PNG);
	bara = new wxBitmap(image3);

	wxString locwood = wxFileName(fileLocation).GetPath() + wxT("\\inventory kayu.png");
	wxImage image4(locwood, wxBITMAP_TYPE_PNG);
	kayu = new wxBitmap(image4);

	wxString loctan = wxFileName(fileLocation).GetPath() + wxT("\\inventory tanah.png");
	wxImage image6(loctan, wxBITMAP_TYPE_PNG);
	tanah = new wxBitmap(image6);

	wxString locdia = wxFileName(fileLocation).GetPath() + wxT("\\inventory diamond.png");
	wxImage image5(locdia, wxBITMAP_TYPE_PNG);
	diamond = new wxBitmap(image5);
}
