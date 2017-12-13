#include "Map.h"
#include "Resource.h"
#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

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


Map::Map(ImageFrame * parent)
	: wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	LoadAllBitmap();

	mirai = Hero::getInstance();
	rs = Resource::getInstance();

	wxBitmapButton* map1 = new wxBitmapButton(this, 1001, *mapnum[1], wxPoint(320, 10), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map2 = new wxBitmapButton(this, 1002, *mapnum[2], wxPoint(230, 105), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map3 = new wxBitmapButton(this, 1003, *mapnum[3], wxPoint(125, 145), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map4 = new wxBitmapButton(this, 1004, *mapnum[4], wxPoint(285, 190), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map5 = new wxBitmapButton(this, 1005, *mapnum[5], wxPoint(325, 290), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map6 = new wxBitmapButton(this, 1006, *mapnum[6], wxPoint(115, 335), wxDefaultSize, wxBORDER_NONE);

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *rs->bitmapstatus, wxPoint(256, 619), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *rs->bitmapbonds, wxPoint(376, 620), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *rs->bitmapinvent, wxPoint(138, 621), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *rs->bitmapskill, wxPoint(32, 620), wxDefaultSize, wxBORDER_MASK);

}

Map::~Map()
{
	delete mp, hp, mpbar, hpbar;
	for (int i = 1; i <= 6; i++) delete mapnum[i];
}

void Map::OnPaint(wxPaintEvent & event)
{
	vector<char> mirainama(mirai->name.begin(), mirai->name.end());

	wxPaintDC pdc(this);
	pdc.DrawBitmap(*rs->map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*rs->buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*rs->chibi, wxPoint(30, 490), true);
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
		pdc.DrawBitmap(*rs->huruf[n], wxPoint(x, y), true);
		x += 16;
	}
}

void Map::ClickMap1(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map1");
}

void Map::ClickMap2(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map2");
}

void Map::ClickMap3(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on map3");
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
	wxMessageOutputDebug().Printf("Click on status");
	parentFrame->ShowMenuStatus();
}

void Map::ClickButtonBonds(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on bonds");
	parentFrame->ShowMenuBonds();
}

void Map::ClickButtonInventory(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on inventory");
	parentFrame->ShowMenuInvent();
}

void Map::ClickButtonUpgrade(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("click on upgrade");
	parentFrame->ShowMenuUpgrade();
}

void Map::LoadAllBitmap()
{
	LoadMapNumberBitmap();
	LoadMapBitmap();
}

void Map::LoadMapNumberBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

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

void Map::LoadMapBitmap()
{
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
