#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"

class Battle2 : public wxWindow
{
public:
	Battle2(ImageFrame *parent);
	~Battle2();
	void OnPaintMirai(wxPaintEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnClickClaim(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);

	Hero *mirai;
	Enemy warrior;

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow, *hp, *mp, *mpbar, *hpbar, *hpbarenemy, *battlechibi;
	wxBitmap *reward, *backmenu, *backwin, *backlose;
	wxBitmap *balok, *bara, *gold;
	wxBitmap *buttonatt, *buttondef, *buttonheal;

	//mirai walking
	wxBitmap *mw[10];
	//mirai healing
	wxBitmap *mh[25];
	//mirai attack
	wxBitmap *ma[20];
	//mirai defense
	wxBitmap *md[25];
	//enemy
	wxBitmap *ww[5], *wa[15]; //walking & attack

	wxBitmapButton *attack, *defense, *heal, *claimok;
	int framerate;
	int renew;
	int turn;
	double ratioenemy, ratiohp, ratiomp;

	void SetBar();
	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadSpriteMiraiBitmap();
	void LoadResultBitmap();
	void CalculateRatio();

	void LoadSpriteEnemyBitmap();
	DECLARE_EVENT_TABLE();

};

