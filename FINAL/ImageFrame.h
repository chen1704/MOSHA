#pragma once
#include "wx\wx.h"

class MenuStart;
class MenuName;
class Map;
class MenuUpgrade;
class MenuInvent;
class MenuStatus;
class MenuBonds;
class Battle1;
class Battle2;
class Battle3;
class Battle4;
class Battle5;
class Battle6;
class Hero;
class Resource;

class ImageFrame : public wxFrame
{
public:
	ImageFrame(const wxString &title);
	~ImageFrame();

	void InitComponents();
	void ShowStart();
	void ShowName();
	void ShowMap();
	void ShowMenuUpgrade();
	void ShowMenuInvent();
	void ShowMenuStatus();
	void ShowMenuBonds();
	void ShowBattle1();
	void ShowBattle2();
	void ShowBattle3();
	void ShowBattle4();
	void ShowBattle5();
	void ShowBattle6();

	Hero *mirai;
	Resource *rs;

private:
	wxBoxSizer *boxSizer;
	MenuStart *menustart;
	MenuName *menuname;
	Map *map;
	MenuUpgrade *menuupgrade;
	MenuInvent *menuinvent;
	MenuStatus *menustatus;
	MenuBonds *menubonds;
	Battle1 *battle1;
	Battle2 *battle2;
	Battle3 *battle3;
	Battle4 *battle4;
	Battle5 *battle5;
	Battle6 *battle6;
	
	void fitWindowSize();

};

