#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"

class Battle1 : public wxWindow
{
public:
	Battle1(ImageFrame *parent);
	void OnPaintMirai(wxPaintEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnClickClaim(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);

	Hero *mirai;
	Enemy icemage;
	~Battle1();

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow, *hp, *mp, *mpbar, *hpbar, *hpbarenemy, *battlechibi;
	wxBitmap *reward, *backmenu, *backwin, *backlose;
	wxBitmap *balok, *bara, *gold;
	wxBitmap *buttonatt, *buttondef, *buttonheal;
	//mirai walking
	wxBitmap *mw[10], *huruf[60];
	//mirai healing
	wxBitmap *mh[25];
	//mirai attack
	wxBitmap *ma[20];
	//mirai defense
	wxBitmap *md[25];

	//enemy
	wxBitmap *mage[20], //enemy biasa
		*t1, *t2, *t3; //enemy attack

	wxBitmapButton *attack, *defense, *heal, *claimok;
	int framerate;
	int renew;
	int turn;
	int enemystat, miraistat;
	double ratioenemy, ratiohp, ratiomp;

	void SetBar();
	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadSpriteMiraiBitmap();
	void LoadResultBitmap();
	void LoadHurufkecilBitmap();
	void LoadHurufbesarBitmap();
	void CalculateRatio();

	void LoadSpriteEnemyBitmap();
	DECLARE_EVENT_TABLE();
};
