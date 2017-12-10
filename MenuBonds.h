#pragma once
#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuBonds : public wxWindow
{
public:
	MenuBonds(ImageFrame* parent);
	~MenuBonds();
	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);

	Hero *mirai;
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonwindow, *bond, *chibi, *description;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill, *bitmapexit;
	wxBitmap *shimura, *hijikata, *sakata;
	wxBitmap *nameshimura, *namehijikata, *namesakata;
	wxBitmap *heartnull, *hearthalf, *heartfull;
	//wxBitmap *buttonexit;
	wxBitmapButton *buttonstatus, *buttonbonds, *buttoninvent, *buttonskill, *buttonexit;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMenuBitmap();
	void LoadBondsBitmap();

	DECLARE_EVENT_TABLE()
};
