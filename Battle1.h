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
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);

	Hero *mirai;
	~Battle1();

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow;
	wxBitmap *buttonatt, *buttondef, *buttonheal;
	//mirai walking
	wxBitmap *mirai0, *mirai1, *mirai2, *mirai3, *mirai4, *mirai5,
		*mirai6, *mirai7, *mirai8;
	//mirai healing
	wxBitmap *ma0, *ma1, *ma2, *ma3, *ma4, *ma5, *ma6, *ma7, *ma8, *ma9, *ma10,
		*ma11, *ma12, *ma13, *ma14, *ma15, *ma16, *ma17, *ma18, *ma19, *ma20, *ma21;
	//mirai attack
	wxBitmap *md9, *md10, *md11, *md12, *md13, *md14, *md15, *md16;
	//mirai defense
	wxBitmap *mz0, *mz1, *mz2, *mz3, *mz4, *mz5, *mz6, *mz7, *mz8, *mz9, *mz10,
		*mz11, *mz12, *mz13, *mz14, *mz15, *mz16, *mz17, *mz18, *mz19, *mz20, *mz21, *mz22;
	//enemy
	wxBitmap *e0, *e1, *e2, *e3, *e4, *e5, *e6, *e7, *e8, *e9, *e10, //enemy biasa
		*e11, *e12, *e13, *e14, *e15, *e16,
		*t1, *t2, *t3; //enemy attack
	
	wxBitmapButton *attack, *defense, *heal;
	int framerate;
	int renew;
	int turn;
	int enemystat, miraistat;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadSpriteMiraiBitmap();

	void LoadSpriteEnemyBitmap();
	DECLARE_EVENT_TABLE();
};

