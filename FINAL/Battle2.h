#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"
#include "Resource.h"

class Battle2 : public wxWindow
{
public:
	Battle2(ImageFrame *parent);
	~Battle2();

	void OnPaintMirai(wxPaintEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnClickRetreat(wxCommandEvent &event);
	void OnClickClaim(wxCommandEvent &event);
	void OnClickBackMenu(wxCommandEvent &event);

	Hero *mirai;
	Resource *rs;
	Enemy warrior;

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmapButton *attack, *defense, *heal, *retreat, *buttonwin, *buttonlose;
	wxBitmap *ww[5], *wa[15]; //battle2, battle5 [warrior]

	int renew, turn;
	double ratioenemy, ratiohp, ratiomp;

	void LoadAllBitmap();
	void LoadSpriteEnemyBitmap();
	void SetBar();
	void CalculateRatio();
	DECLARE_EVENT_TABLE()
};

