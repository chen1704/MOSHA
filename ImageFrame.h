#pragma once
#include "wx\wx.h"

class MOSHA;
class Map;
class MenuStatus;
class MenuName;
class Battle1;
class Hero;

class ImageFrame : public wxFrame
{
public:
	ImageFrame(const wxString &title);
	void InitComponents();
	void ShowStart();
	void ShowName();
	void ShowMap();
	void ShowBattle1();

private:
	int frame;
	wxBoxSizer *boxSizer;
	MOSHA* mosha;
	Map *map;
	MenuStatus *menustatus;
	MenuName *menuname;
	Battle1 *battle1;

	void fitWindowSize();
	
};

