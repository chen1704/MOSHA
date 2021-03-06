#include "Map.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/animate.h>

BEGIN_EVENT_TABLE(Map, wxWindow)
EVT_PAINT(Map::OnPaint)
EVT_BUTTON(1001, Map::ClickMap1)
EVT_BUTTON(1002, Map::ClickMap2)
EVT_BUTTON(1003, Map::ClickMap3)
EVT_BUTTON(1004, Map::ClickMap4)
EVT_BUTTON(1005, Map::ClickMap5)
EVT_BUTTON(1006, Map::ClickMap6)
EVT_BUTTON(1007, Map::ClickButtonStatus)
EVT_BUTTON(1008, Map::ClickButtonBonds)
EVT_BUTTON(1009, Map::ClickButtonInventory)
EVT_BUTTON(1010, Map::ClickButtonUpgrade)
END_EVENT_TABLE()



Map::Map(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImageHandler *gifLoader = new wxGIFHandler();
	wxImage::AddHandler(pngLoader);
	wxImage::AddHandler(gifLoader);
	LoadAllBitmap();

	mirai = Hero::getInstance();
	//	heroname = mirai->name;
	//	wxMessageOutputDebug().Printf("hero name = %s", heroname);


	wxBitmapButton* map1 = new wxBitmapButton(this, 1001, *mapnum[1], wxPoint(320, 10), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map2 = new wxBitmapButton(this, 1002, *mapnum[2], wxPoint(230, 105), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map3 = new wxBitmapButton(this, 1003, *mapnum[3], wxPoint(125, 145), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map4 = new wxBitmapButton(this, 1004, *mapnum[4], wxPoint(285, 190), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map5 = new wxBitmapButton(this, 1005, *mapnum[5], wxPoint(325, 290), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map6 = new wxBitmapButton(this, 1006, *mapnum[6], wxPoint(115, 335), wxDefaultSize, wxBORDER_NONE);

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);
}

Map::~Map()
{
	delete map, buttonWindow, chibi, hp, mp;
	delete bitmapstatus, bitmapbonds, bitmapinvent, bitmapskill;
	for (int i = 1; i <= 6; i++) delete mapnum[i];
	for (int i = 1; i <= 58; i++) delete huruf[i];
}

void Map::OnPaint(wxPaintEvent & event)
{
	vector<char> mirainama(mirai->name.begin(), mirai->name.end());


	wxPaintDC pdc(this);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*chibi, wxPoint(30, 490), true);
	//pdc.DrawText(mirai->name, wxPoint(160, 480));
	pdc.DrawBitmap(*hp, wxPoint(162, 522), true);
	pdc.DrawBitmap(*mp, wxPoint(157, 565), true);
	pdc.DrawBitmap(*hpbar, wxPoint(207, 524), true);
	pdc.DrawBitmap(*mpbar, wxPoint(207, 566), true);

	pdc.SetBrush(*wxRED_BRUSH);
	pdc.DrawRectangle(wxPoint(215, 531), wxSize((242 / mirai->hpmax)*mirai->HP, 20));
	pdc.SetBrush(*wxBLUE_BRUSH);
	pdc.DrawRectangle(wxPoint(215, 572), wxSize((242 / mirai->mpmax)*mirai->MP, 20));

	int i, x, n, y, o;
	x = 165; y = 480; o = mirainama.size();
	for (i = 0; i < o; i++) {
		if (mirainama[i] < 65 || mirainama[i]>122) continue;
		n = mirainama[i] - '0';
		n -= 16;
		pdc.DrawBitmap(*huruf[n], wxPoint(x, y), true);
		x += 16;
	}
	//	wxMessageOutputDebug().Printf("ini pakai mirailgsung: %s", mirai->name);
	//	wxMessageOutputDebug().Printf("ini tempheroname: %s", heroname);
	//	pdc.DrawBitmap(*mirai, 0,0);

}

void Map::ClickMap1(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map1");
	parentFrame->ShowBattle1();
	//	DeleteBitmap();
}

void Map::ClickMap2(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map2");
	parentFrame->ShowBattle2();
}

void Map::ClickMap3(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map3");
	parentFrame->ShowBattle3();
}

void Map::ClickMap4(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map4");
}

void Map::ClickMap5(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map5");
}

void Map::ClickMap6(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map6");
}

void Map::ClickButtonStatus(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on status");
	parentFrame->ShowMenuStatus();

}

void Map::ClickButtonBonds(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on bonds");
	parentFrame->ShowMenuBonds();

}

void Map::ClickButtonUpgrade(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on upgrade skill");
	parentFrame->ShowMenuUpgrade();
}

void Map::ClickButtonInventory(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void Map::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadbuttonWindowBitmap();
	this->LoadMapNumberBitmap();
	this->LoadUpgradeBitmap();
	this->LoadHurufbesarBitmap();
	this->LoadHurufkecilBitmap();
}

void Map::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	wxString locationmap = wxFileName(fileLocation).GetPath() + wxT("\\MAP - FIX.png");
	//	wxMessageOutputDebug().Printf("Relative path is at %s", locationmap);
	wxImage image(locationmap, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString locationchibi = wxFileName(fileLocation).GetPath() + wxT("\\chibi sprites.png");
	wxImage image1(locationchibi, wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image1);

	//	wxString locmirai = wxFileName(fileLocation).GetPath() + wxT("\\miraiwalking.gif");
	//	wxImage image2(locmirai, wxBITMAP_TYPE_GIF);
	//	mirai = new wxBitmap(image2);


}

void Map::LoadMapNumberBitmap()
{
	wxString locmap1 = wxFileName(fileLocation).GetPath() + wxT("\\map1.png");
	wxImage image1(locmap1, wxBITMAP_TYPE_PNG);
	mapnum[1] = new wxBitmap(image1);

	wxString locmap2 = wxFileName(fileLocation).GetPath() + wxT("\\map2.png");
	wxImage image2(locmap2, wxBITMAP_TYPE_PNG);
	mapnum[2] = new wxBitmap(image2);

	wxString locmap3 = wxFileName(fileLocation).GetPath() + wxT("\\map3.png");
	wxImage image3(locmap3, wxBITMAP_TYPE_PNG);
	mapnum[3] = new wxBitmap(image3);

	wxString locmap4 = wxFileName(fileLocation).GetPath() + wxT("\\map4.png");
	wxImage image4(locmap4, wxBITMAP_TYPE_PNG);
	mapnum[4] = new wxBitmap(image4);

	wxString locmap5 = wxFileName(fileLocation).GetPath() + wxT("\\map5.png");
	wxImage image5(locmap5, wxBITMAP_TYPE_PNG);
	mapnum[5] = new wxBitmap(image5);

	wxString locmap6 = wxFileName(fileLocation).GetPath() + wxT("\\map6.png");
	wxImage image6(locmap6, wxBITMAP_TYPE_PNG);
	mapnum[6] = new wxBitmap(image6);
}

void Map::LoadbuttonWindowBitmap()
{
	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);

	wxString lochp = wxFileName(fileLocation).GetPath() + wxT("\\window hp.png");
	wxImage image2(lochp, wxBITMAP_TYPE_PNG);
	hp = new wxBitmap(image2);

	wxString locmp = wxFileName(fileLocation).GetPath() + wxT("\\window mp.png");
	wxImage image3(locmp, wxBITMAP_TYPE_PNG);
	mp = new wxBitmap(image3);

	wxString lochpbar = wxFileName(fileLocation).GetPath() + wxT("\\bar hp status.png");
	wxImage image4(lochpbar, wxBITMAP_TYPE_PNG);
	hpbar = new wxBitmap(image4);

	wxString locmpbar = wxFileName(fileLocation).GetPath() + wxT("\\bar mp status.png");
	wxImage image5(locmpbar, wxBITMAP_TYPE_PNG);
	mpbar = new wxBitmap(image5);
}

void Map::LoadUpgradeBitmap()
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

void Map::LoadHurufkecilBitmap() {
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

void Map::LoadHurufbesarBitmap() {
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