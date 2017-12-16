#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"
#include "Hero.h"
#include "Enemy.h"
#include "Resource.h"

class Battle1 : public wxWindow
{
public:
	Battle1(ImageFrame *parent);
	~Battle1();

	void OnPaintMirai(wxPaintEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnClickAttack(wxCommandEvent &event);
	void OnClickDefense(wxCommandEvent &event);
	void OnClickHeal(wxCommandEvent &event);
	void OnClickClaim(wxCommandEvent &event);

	Hero *mirai;
	Resource *rs;
	Enemy icemage;

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmapButton *attack, *defense, *heal;
	
	wxBitmap *mw[5], *ma[20];
	
	int renew, turn;
	double ratioenemy, ratiohp, ratiomp;

	void LoadAllBitmap();
	void LoadSpriteEnemyBitmap();
	void SetBar();
	void CalculateRatio();
	DECLARE_EVENT_TABLE()
};