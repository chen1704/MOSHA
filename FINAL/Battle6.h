#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"
#include "Resource.h"

class Battle6 : public wxWindow
{
public:
	Battle6(ImageFrame *parent);
	~Battle6();

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
	Enemy chitose;

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmapButton *attack, *defense, *heal, *buttonwin, *buttonlose;
	wxBitmapButton *retreat;

	wxBitmap *cw[10], *ca[30]; //battle1, battle4 [mage]

	int renew, turn;
	double ratioenemy, ratiohp, ratiomp;

	void LoadAllBitmap();
	void LoadSpriteEnemyBitmap();
	void SetBar();
	void CalculateRatio();
	DECLARE_EVENT_TABLE()
};

