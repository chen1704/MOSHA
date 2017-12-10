#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include<vector>

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
	wxBitmap *huruf[60];
	wxBitmap *map, *buttonWindow, *chibi, *hp, *mp;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill, *level, *description;
	wxBitmap *layoutstatus, *exit, *chibistatus;
	wxBitmap *skillattack, *skillshield, *skillheal;
	wxBitmap *txtattack, *txtshield, *txtheal;
	//	wxString *convatt, *convdef, *convheal;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadbuttonWindowBitmap();
	void LoadUpgradeBitmap();
	void LoadSkillBitmap();
	void LoadHurufbesarBitmap();
	void LoadHurufkecilBitmap();
	DECLARE_EVENT_TABLE()

};
