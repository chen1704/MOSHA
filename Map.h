#pragma once
#include "wx\wx.h"
#include "wx/animate.h"

class Map : public wxWindow
{
public:
	Map();
	Map(wxFrame *parent);
	~Map();

	void OnPaint(wxPaintEvent &event);

	void ClickMap1(wxCommandEvent &event);
	void ClickMap2(wxCommandEvent &event);
	void ClickMap3(wxCommandEvent &event);
	void ClickMap4(wxCommandEvent &event);
	void ClickMap5(wxCommandEvent &event);
	void ClickMap6(wxCommandEvent &event);
	

private:
	wxBitmap *map = nullptr;
	wxBitmap *buttonWindow = nullptr;
	wxBitmap *chibi = nullptr;
//	wxBitmap *mirai = nullptr;
//	wxAnimation *mirai;

	/*Map Number bitmap*/
	wxBitmap *mapnum1, *mapnum2, *mapnum3, *mapnum4, *mapnum5, *mapnum6;
	wxPanel *panel;
	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMapNumberBitmap();
	void LoadbuttonWindowBitmap();
	void LoadUpgradeBitmap();
	DECLARE_EVENT_TABLE();
};

