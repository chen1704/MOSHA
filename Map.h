#pragma once
#include "wx\wx.h"
#include "wx/animate.h"
#include "ImageFrame.h"
#include "Hero.h"

class Map : public wxWindow
{
public:
	Map(ImageFrame *parent);
	~Map();
	Hero *mirai;
	//	string heroname;
	void OnPaint(wxPaintEvent &event);

	void ClickMap1(wxCommandEvent &event);
	void ClickMap2(wxCommandEvent &event);
	void ClickMap3(wxCommandEvent &event);
	void ClickMap4(wxCommandEvent &event);
	void ClickMap5(wxCommandEvent &event);
	void ClickMap6(wxCommandEvent &event);

	void ClickButtonStatus(wxCommandEvent &event);
	void ClickButtonBonds(wxCommandEvent &event);
	void ClickButtonInventory(wxCommandEvent &event);
	void ClickButtonUpgrade(wxCommandEvent &event);


private:

	ImageFrame *parentFrame;
	wxBitmap *huruf[60];
	wxString fileLocation;
	wxBitmap *map = nullptr;
	wxBitmap *buttonWindow = nullptr;
	wxBitmap *chibi = nullptr;
	wxBitmap *mp = nullptr;
	wxBitmap *hp = nullptr;
	wxBitmap *hpbar = nullptr;
	wxBitmap *mpbar = nullptr;
	//	wxTextCtrl *MapName;
	//	wxBitmap *mirai = nullptr;
	//	wxAnimation *mirai;

	/*Map Number bitmap*/
//	wxBitmap *mapnum1, *mapnum2, *mapnum3, *mapnum4, *mapnum5, *mapnum6;
	wxBitmap *mapnum[7];
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill;

	wxPanel *panel;
	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMapNumberBitmap();
	void LoadbuttonWindowBitmap();
	void LoadUpgradeBitmap();
	void LoadHurufbesarBitmap();
	void LoadHurufkecilBitmap();
	DECLARE_EVENT_TABLE();
};
