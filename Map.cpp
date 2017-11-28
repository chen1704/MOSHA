#include "Map.h"
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
EVT_BUTTON(1009, Map::ClickButtonShop)
EVT_BUTTON(1010, Map::ClickButtonBlackSmith)
END_EVENT_TABLE()



Map::Map(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
//	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImageHandler *gifLoader = new wxGIFHandler();
	wxImage::AddHandler(pngLoader);
	wxImage::AddHandler(gifLoader);
	LoadAllBitmap();

	wxBitmapButton* map1 = new wxBitmapButton(this, 1001, *mapnum1, wxPoint(320, 10), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map2 = new wxBitmapButton(this, 1002, *mapnum2, wxPoint(230, 105), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map3 = new wxBitmapButton(this, 1003, *mapnum3, wxPoint(125, 145), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map4 = new wxBitmapButton(this, 1004, *mapnum4, wxPoint(285, 190), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map5 = new wxBitmapButton(this, 1005, *mapnum5, wxPoint(325, 290), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map6 = new wxBitmapButton(this, 1006, *mapnum6, wxPoint(115, 335), wxDefaultSize, wxBORDER_NONE);

//	wxAnimationCtrl *mirai;
//	mirai = new wxAnimationCtrl(this, wxID_ANY);
//	if (mirai->LoadFile(wxT("miraiwalking.gif")))
//		mirai->Play();

//	mirai = new wxAnimation(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\miraiwalking.gif"),wxANIMATION_TYPE_ANY);
	
//	wxAnimationCtrl *an = new wxAnimationCtrl(this, wxID_ANY, wxAnimation(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\miraiwalking.gif"), wxANIMATION_TYPE_ANY), wxPoint(28, 300));
//	an->Play();
	// https://github.com/LuaDist/wxwidgets/blob/master/samples/animate/anitest.cpp

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(40, 630), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(165, 627), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttoninvent = new wxBitmapButton(this, 1009, *bitmapinvent, wxPoint(270, 628), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonskill = new wxBitmapButton(this, 1010, *bitmapskill, wxPoint(380, 625), wxDefaultSize, wxBORDER_MASK);
}

Map::~Map()
{
	delete map;
	delete buttonWindow;
	delete chibi;
//	delete mirai;
}

void Map::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);

	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*chibi, wxPoint(28, 488), true);
//	pdc.DrawBitmap(*mirai, 0,0);
	
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
	Refresh();
}

void Map::ClickButtonBonds(wxCommandEvent & event)
{
}

void Map::ClickButtonShop(wxCommandEvent & event)
{
}

void Map::ClickButtonBlackSmith(wxCommandEvent & event)
{
}

void Map::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadbuttonWindowBitmap();
	this->LoadMapNumberBitmap();
	this->LoadUpgradeBitmap();
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
	mapnum1 = new wxBitmap(image1);

	wxString locmap2 = wxFileName(fileLocation).GetPath() + wxT("\\map1.png");
	wxImage image2(locmap2, wxBITMAP_TYPE_PNG);
	mapnum2 = new wxBitmap(image2);

	wxString locmap3 = wxFileName(fileLocation).GetPath() + wxT("\\map3.png");
	wxImage image3(locmap3, wxBITMAP_TYPE_PNG);
	mapnum3 = new wxBitmap(image3);

	wxString locmap4 = wxFileName(fileLocation).GetPath() + wxT("\\map4.png");
	wxImage image4(locmap4, wxBITMAP_TYPE_PNG);
	mapnum4 = new wxBitmap(image4);

	wxString locmap5 = wxFileName(fileLocation).GetPath() + wxT("\\map5.png");
	wxImage image5(locmap5, wxBITMAP_TYPE_PNG);
	mapnum5 = new wxBitmap(image5);

	wxString locmap6 = wxFileName(fileLocation).GetPath() + wxT("\\map6.png");
	wxImage image6(locmap6, wxBITMAP_TYPE_PNG);
	mapnum6 = new wxBitmap(image6);
}

void Map::LoadbuttonWindowBitmap()
{
	wxString locbuttonwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image(locbuttonwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);
}

void Map::LoadUpgradeBitmap()
{
	wxString locstatus = wxFileName(fileLocation).GetPath() + wxT("\\status button.png");
	wxImage image1(locstatus, wxBITMAP_TYPE_PNG);
	bitmapstatus = new wxBitmap(image1);

	wxString locbond = wxFileName(fileLocation).GetPath() + wxT("\\bonds button.png");
	wxImage image2(locbond, wxBITMAP_TYPE_PNG); 
	bitmapbonds = new wxBitmap(image2);

	wxString locinven = wxFileName(fileLocation).GetPath() + wxT("\\shop button.png");
	wxImage image3(locinven, wxBITMAP_TYPE_PNG); 
	bitmapinvent = new wxBitmap(image3);

	wxString locskill = wxFileName(fileLocation).GetPath() + wxT("\\blacksmith button.png");
	wxImage image4(locskill, wxBITMAP_TYPE_PNG); 
	bitmapskill = new wxBitmap(image4);

}
