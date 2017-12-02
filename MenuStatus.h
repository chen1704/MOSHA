#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuStatus : public wxWindow
{
public:
	MenuStatus(ImageFrame *parent);
	~MenuStatus();
	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);

	Hero *mirai;
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonWindow, *chibi;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill;
	wxBitmap *layoutstatus, *exit, *chibistatus;
	wxBitmap *skillattack, *skillshield, *skillheal;
	wxBitmap *txtattack, *txtshield, *txtheal;
//	wxString *convatt, *convdef, *convheal;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadbuttonWindowBitmap();
	void LoadUpgradeBitmap();
	void LoadSkillBitmap();
	DECLARE_EVENT_TABLE()
	
};

