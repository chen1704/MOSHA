#include "MenuBonds.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/font.h>

BEGIN_EVENT_TABLE(MenuBonds, wxWindow)
EVT_PAINT(MenuBonds::OnPaint)
EVT_BUTTON(1001, MenuBonds::OnClickExit)
END_EVENT_TABLE()

MenuBonds::MenuBonds(ImageFrame *parent) : wxWindow(parent, wxID_ANY), parentFrame(parent) {
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	mirai = Hero::getInstance();

	LoadAllBitmap();

	buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(258, 622), wxDefaultSize, wxBORDER_MASK);
	buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(378, 627), wxDefaultSize, wxBORDER_MASK);
	buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(28, 628), wxDefaultSize, wxBORDER_MASK);
	buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(146, 625), wxDefaultSize, wxBORDER_MASK);
	//wxBitmapButton *buttonexit = new wxBitmapButton(this, 1001, *exit, wxPoint(398, 10), wxDefaultSize, wxBORDER_NONE);

}

MenuBonds::~MenuBonds(){
	delete map, buttonwindow, buttonbonds, buttoninvent, buttonskill, buttonstatus;
	delete shimura, hijikata, sakata, namesakata, nameshimura, namehijikata;
	delete chibi, bond;
}

void MenuBonds::OnPaint(wxPaintEvent &event) {
	wxPaintDC pdc(this);

	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonwindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*bond, wxPoint(55, -1), true);
	pdc.DrawBitmap(*chibi, wxPoint(30, 490), true);
	pdc.DrawBitmap(*shimura, wxPoint(94,71), true);
	pdc.DrawBitmap(*hijikata, wxPoint(281, 175), true);
	pdc.DrawBitmap(*sakata, wxPoint(101, 288), true);
	pdc.DrawBitmap(*nameshimura, wxPoint(210,93), true); 
	pdc.DrawBitmap(*namehijikata, wxPoint(117, 221), true);
	pdc.DrawBitmap(*namesakata, wxPoint(234, 341), true);
}

void MenuBonds::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Exit Clicked");
	parentFrame->ShowMap();
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
}

void MenuBonds::LoadBondsBitmap(){
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
