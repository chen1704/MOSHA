#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuInvent : public wxWindow
{
public:
	MenuInvent(ImageFrame *parent);
	~MenuInvent();
	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);
	void OnClickStatus(wxCommandEvent &event);
	void OnClickBond(wxCommandEvent &event);
	void OnClickUpgrade(wxCommandEvent &event);
	Hero *mirai;
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonWindow, *inventory, *chibi, *description;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill, *bitmapexit;
	wxBitmap *balok, *batu, *kayu, *bara, *tanah, *diamond;
	wxBitmapButton *buttonstatus, *buttonbonds, *buttoninvent, *buttonskill, *buttonexit;


	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMenuBitmap();
	void LoaditemBitmap();
	DECLARE_EVENT_TABLE()
};

