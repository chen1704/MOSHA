#pragma once
#include "wx\wx.h"

class MOSHA;
class Map;
class MenuStatus;

class ImageFrame : public wxFrame
{
public:
	ImageFrame(const wxString &title);
	void InitComponents();
	void ShowStart();
	void ShowMap();

private:
	int frame;
	wxBoxSizer *boxSizer;
	MOSHA* mosha;
	Map *map;
	MenuStatus *menustatus;

	void fitWindowSize();
	
};

