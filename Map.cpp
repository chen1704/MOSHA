#include "Map.h"
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
EVT_BUTTON(1009, Map::ClickButtonShop)
EVT_BUTTON(1010, Map::ClickButtonBlackSmith)
END_EVENT_TABLE()



Map::Map(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
//	Refresh();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	LoadAllBitmap();

	wxBitmapButton* map1 = new wxBitmapButton(this, 1001, *mapnum1, wxPoint(320, 10), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map2 = new wxBitmapButton(this, 1002, *mapnum2, wxPoint(230, 105), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map3 = new wxBitmapButton(this, 1003, *mapnum3, wxPoint(125, 145), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map4 = new wxBitmapButton(this, 1004, *mapnum4, wxPoint(285, 190), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map5 = new wxBitmapButton(this, 1005, *mapnum5, wxPoint(325, 290), wxDefaultSize, wxBORDER_NONE);
	wxBitmapButton* map6 = new wxBitmapButton(this, 1006, *mapnum6, wxPoint(115, 335), wxDefaultSize, wxBORDER_NONE);

//	mirai = new wxAnimation("miraiwalking.gif",wxANIMATION_TYPE_ANY);
	
//	wxAnimationCtrl *an = new wxAnimationCtrl(this, wxID_ANY, wxAnimation(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\miraiwalking.gif"), wxANIMATION_TYPE_ANY), wxPoint(28, 300));
//	an->Play();
	// https://github.com/LuaDist/wxwidgets/blob/master/samples/animate/anitest.cpp

	wxBitmapButton *buttonstatus = new wxBitmapButton(this, 1007, *bitmapstatus, wxPoint(40, 630), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonbonds = new wxBitmapButton(this, 1008, *bitmapbonds, wxPoint(165, 627), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonshop = new wxBitmapButton(this, 1009, *bitmapshop, wxPoint(270, 628), wxDefaultSize, wxBORDER_MASK);
	wxBitmapButton *buttonblacksmith = new wxBitmapButton(this, 1010, *bitmapblacksmith, wxPoint(380, 625), wxDefaultSize, wxBORDER_MASK);
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
	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\MAP - FIX.png"), wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxImage image1(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\chibi sprites.png"), wxBITMAP_TYPE_PNG);
	chibi = new wxBitmap(image1);

//	wxImage image2(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\miraiwalking.gif"), wxBITMAP_TYPE_GIF);
//	mirai = new wxBitmap(image2);


}

void Map::LoadMapNumberBitmap()
{
	wxImage image1(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map1.png"), wxBITMAP_TYPE_PNG);
	mapnum1 = new wxBitmap(image1);
	wxImage image2(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map2.png"), wxBITMAP_TYPE_PNG);
	mapnum2 = new wxBitmap(image2);
	wxImage image3(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map3.png"), wxBITMAP_TYPE_PNG);
	mapnum3 = new wxBitmap(image3);
	wxImage image4(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map4.png"), wxBITMAP_TYPE_PNG);
	mapnum4 = new wxBitmap(image4);
	wxImage image5(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map5.png"), wxBITMAP_TYPE_PNG);
	mapnum5 = new wxBitmap(image5);
	wxImage image6(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\map6.png"), wxBITMAP_TYPE_PNG);
	mapnum6 = new wxBitmap(image6);
}

void Map::LoadbuttonWindowBitmap()
{
	wxImage image(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\button window.png"), wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image);
}

void Map::LoadUpgradeBitmap()
{
	wxImage image1(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\status button.png"), wxBITMAP_TYPE_PNG);
	bitmapstatus = new wxBitmap(image1);
	wxImage image2(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\bonds button.png"), wxBITMAP_TYPE_PNG);
	bitmapbonds = new wxBitmap(image2);
	wxImage image3(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\shop button.png"), wxBITMAP_TYPE_PNG);
	bitmapshop = new wxBitmap(image3);
	wxImage image4(wxT("D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\blacksmith button.png"), wxBITMAP_TYPE_PNG);
	bitmapblacksmith = new wxBitmap(image4);

}
