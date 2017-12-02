#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"

class Battle1 : public wxWindow
{
public:
	Battle1(ImageFrame *parent);
	void OnPaintMirai(wxPaintEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);

	Hero *mirai;
	~Battle1();

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow;
	wxBitmap *buttonatt, *buttondef, *buttonheal;
	wxBitmap *mirai0, *mirai1, *mirai2, *mirai3, *mirai4, *mirai5,
		*mirai6, *mirai7, *mirai8;
	wxBitmap *e0, *e1, *e2, *e3, *e4, *e5, *e6, *e7, *e8, *e9, *e10,
		*e11, *e12, *e13, *e14, *e15, *e16,
		*t1, *t2, *t3;

	int framerate;
	bool turn;
	int enemystat, miraistat;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadSpriteMiraiBitmap();

	void LoadSpriteEnemyBitmap();
	DECLARE_EVENT_TABLE();
};

