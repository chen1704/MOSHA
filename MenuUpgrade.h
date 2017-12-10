#pragma once
#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuUpgrade : public wxWindow
{
public:
	MenuUpgrade(ImageFrame *parent);
	~MenuUpgrade();
	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);
	void OnClickStatus(wxCommandEvent &event);
	void OnClickBond(wxCommandEvent &event);
	void OnClickInvent(wxCommandEvent &event);
	void OnClickUpgradeAttack(wxCommandEvent &event);
	void OnClickUpgradeShield(wxCommandEvent &event);
	void OnClickUpgradeHeal(wxCommandEvent &event);

	Hero *mirai;
private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *map, *buttonwindow, *upgrade, *chibi, *moneypanel, *description;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill, *bitmapexit,*bitmapbuy1, *bitmapbuy2, *bitmapbuy3;
	wxBitmap *upattack, *uppotion, *upshield, *tupattack, *tuppotion, *tupshield;
	wxBitmap *attackitem1, *attackitem2, *shielditem1, *shielditem2, *potionitem1, *potionitem2;
	wxBitmap *money1, *money2, *money3;
	wxBitmapButton *buttonstatus, *buttonbonds, *buttoninvent, *buttonskill, *buttonexit;
	wxBitmapButton *buy1, *buy2, *buy3;

	void LoadAllBitmap();
	void LoadMapBitmap();
	void LoadMenuBitmap();
	void LoadUpgradeBitmap();
	void LoadUpgradeItemBitmap();

	DECLARE_EVENT_TABLE()
};

