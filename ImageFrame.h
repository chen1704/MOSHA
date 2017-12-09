#pragma once
#include "wx\wx.h"

class MOSHA;
class Map;
class MenuStatus;
class MenuName;
class Battle1;
class Hero;
class MenuBonds;
class MenuUpgrade;
class MenuInvent;

class ImageFrame : public wxFrame
{
public:
	ImageFrame(const wxString &title);
	void InitComponents();
	void ShowStart();
	void ShowName();
	void ShowMap();
	void ShowMenuStatus();
	void ShowMenuBonds();
	void ShowMenuUpgrade();
	void ShowMenuInvent();
	void ShowBattle1();

//	void LoadMenuBitmap();
//	wxBitmap *peta;

	Hero *mirai;

private:
	int frame;
	wxBoxSizer *boxSizer;
	MOSHA* mosha;
	Map *map;
	MenuStatus *menustatus;
	MenuName *menuname;
	Battle1 *battle1;
	MenuBonds *menubonds;
	MenuUpgrade *menuupgrade;
	MenuInvent *menuinvent;

	

	void fitWindowSize();

};

