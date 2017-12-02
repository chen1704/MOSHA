#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"

class MenuInvent : public wxWindow
{
public:
	MenuInvent(ImageFrame *parent);
	~MenuInvent();
	void OnPaint(wxPaintEvent &event);
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonWindow;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadbuttonWindowBitmap();
	void LoadUpgradeBitmap();
	DECLARE_EVENT_TABLE()
};

