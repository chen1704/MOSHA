#pragma once
#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuBonds : public wxWindow
{
public:
	MenuBonds(ImageFrame* parent);
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
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonwindow, *bond, *chibi, *description;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill, *bitmapexit;
	wxBitmap *shimura, *hijikata, *sakata;
	wxBitmap *nameshimura, *namehijikata, *namesakata;
	wxBitmap *heartnull, *hearthalf, *heartfull, *claim;
	//wxBitmap *buttonexit;
	wxBitmapButton *buttonstatus, *buttonbonds, *buttoninvent, *buttonskill, *buttonexit;
	wxBitmapButton *rewardshimura, *rewardhijikata, *rewardsakata;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMenuBitmap();
	void LoadBondsBitmap();

	DECLARE_EVENT_TABLE()
};
