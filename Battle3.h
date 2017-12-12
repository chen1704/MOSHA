#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"

class Battle3 : public wxWindow
{
public:
	Battle3(ImageFrame *parent);
	void OnPaintMirai(wxPaintEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnClickClaim(wxCommandEvent &event);
	void OnTimer(wxTimerEvent &event);

	Hero *mirai;
	Enemy chitose;
	~Battle3();

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow, *hp, *mp, *mpbar, *hpbar, *hpbarenemy, *battlechibi;
	wxBitmap *reward, *backmenu, *claim, *backwin, *backlose;
	wxBitmap *balok, *bara, *gold;
	wxBitmap *buttonatt, *buttondef, *buttonheal;
	wxBitmap *bitmapret;
	//mirai walking
	wxBitmap *mw[10];
	//mirai healing
	wxBitmap *mh[25];
	//mirai attack
	wxBitmap *ma[20];
	//mirai defense
	wxBitmap *md[25];
	//enemy
	wxBitmap *cw[10], *ca[28];//enemy biasa //enemy attack

	wxBitmapButton *attack, *defense, *heal, *claimok, *retreat;
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
	void CalculateRatio();
	void LoadSpriteEnemyBitmap();
	DECLARE_EVENT_TABLE();
};