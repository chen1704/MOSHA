#include "MenuStatus.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Hero.h"
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


MenuStatus::MenuStatus(ImageFrame *parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	mirai = Hero::getInstance();
	//mirainama(mirai->name.begin(), mirai->name.end());

	LoadAllBitmap();

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);

	wxBitmapButton *buttonexit = new wxBitmapButton(this, 1001, *exit, wxPoint(398, 10), wxDefaultSize, wxBORDER_NONE);
}


MenuStatus::~MenuStatus()
{
	delete map, buttonWindow, chibi, level;
	delete bitmapstatus, bitmapbonds, bitmapinvent, bitmapskill;
	delete layoutstatus, exit, chibistatus;
	delete skillattack, skillshield, skillheal;
	delete txtattack, txtshield, txtheal;
	for (int i = 1; i <= 58; i++) delete huruf[i];
	//	delete convatt, convdef, convheal;

}

void MenuStatus::OnPaint(wxPaintEvent & event)
{
	vector<char> mirainama(mirai->name.begin(), mirai->name.end());

	wxPaintDC pdc(this);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*chibi, wxPoint(28, 488), true);
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
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skillatt), wxPoint(128, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skilldef), wxPoint(238, 404));
	pdc.DrawText(wxString::Format(wxT("%d"), mirai->skillheal), wxPoint(338, 404));
	pdc.DrawBitmap(*exit, wxPoint(398, 8), true);

	int i, x, n, y, o;
	x = 260; y = 192; o = mirainama.size();
	for (i = 0; i < o; i++) {
		n = mirainama[i] - '0';
		n -= 16;
		pdc.DrawBitmap(*huruf[n], wxPoint(x, y), true);
		x += 16;
	}
}

void MenuStatus::OnClickExit(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Menu Status clicked exit!");
	parentFrame->ShowMap();
}

void MenuStatus::OnClickBond(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on bonds");
	parentFrame->ShowMenuBonds();
}

void MenuStatus::OnClickUpgrade(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on upgrade");
	parentFrame->ShowMenuUpgrade();
}

void MenuStatus::OnClickInvent(wxCommandEvent &event) {
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void MenuStatus::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadUpgradeBitmap();
	this->LoadbuttonWindowBitmap();
	this->LoadSkillBitmap();
	this->LoadHurufbesarBitmap();
	this->LoadHurufkecilBitmap();
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

	wxString lochp = wxFileName(fileLocation).GetPath() + wxT("\\tulisan level.png");
	wxImage image2(lochp, wxBITMAP_TYPE_PNG);
	level = new wxBitmap(image2);

	wxString locdes = wxFileName(fileLocation).GetPath() + wxT("\\status description.png");
	wxImage image3(locdes, wxBITMAP_TYPE_PNG);
	description = new wxBitmap(image3);

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

void MenuStatus::LoadHurufbesarBitmap() {
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\a.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[1] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\b.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[2] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\c.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[3] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\d.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[4] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\e.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[5] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\f.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[6] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\g.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[7] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\h.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[8] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\i.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[9] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\j.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[10] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\k.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[11] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\l.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[12] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\m.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[13] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\n.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[14] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\o.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[15] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\p.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[16] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\q.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[17] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\r.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[18] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\s.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[19] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\t.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[20] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\u.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[21] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\v.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[22] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\w.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[23] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\x.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[24] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\y.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[25] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\z.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[26] = new wxBitmap(image25);
}

void MenuStatus::LoadHurufkecilBitmap() {
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\akecil.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[33] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\bkecil.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[34] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\ckecil.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[35] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\dkecil.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[36] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\ekecil.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[37] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\fkecil.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[38] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\gkecil.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[39] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\hkecil.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[40] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\ikecil.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[41] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\jkecil.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[42] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\kkecil.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[43] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\lkecil.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[44] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\mkecil.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[45] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\nkecil.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[46] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\okecil.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[47] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\pkecil.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[48] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\qkecil.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[49] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\rkecil.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[50] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\skecil.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[51] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\tkecil.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[52] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\ukecil.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[53] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\vkecil.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[54] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\wkecil.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[55] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\xkecil.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[56] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\ykecil.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[57] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\zkecil.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[58] = new wxBitmap(image25);
}