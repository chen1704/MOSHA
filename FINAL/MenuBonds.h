#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"

class MenuBonds : public wxWindow
{
public:
	MenuBonds(ImageFrame *parent);
	~MenuBonds();

	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);
	void OnClickShimura(wxCommandEvent &event);
	void OnClickHijikata(wxCommandEvent &event);
	void OnClickSakata(wxCommandEvent &event);
	void OnClickStatus(wxCommandEvent &event);
	void OnClickInvent(wxCommandEvent &event);
	void OnClickUpgrade(wxCommandEvent &event);

	Hero *mirai;
	Resource *rs;

private:
	ImageFrame *parentFrame;
	wxString fileLocation;

	wxBitmap *bond, *description, *exit;
	wxBitmap *shimura, *hijikata, *sakata;
	wxBitmap *nameshimura, *namehijikata, *namesakata;
	wxBitmap *heartnull, *hearthalf, *heartfull, *claim;

	wxBitmapButton *rewardshimura, *rewardhijikata, *rewardsakata;

	void LoadAllBitmap();
	void LoadBondBitmap();
	void LoadPrinceBitmap();
	void LoadHeartBitmap();

	DECLARE_EVENT_TABLE()
};

