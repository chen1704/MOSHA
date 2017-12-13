#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"

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
	Resource *rs;

private:
	ImageFrame *parentFrame;
	wxString fileLocation;

	wxBitmap *upgrade, *moneypanel, *description, *exit;
	wxBitmap *upattack, *uppotion, *upshield, *tupattack, *tuppotion, *tupshield;
	wxBitmap *attackitem1, *attackitem2, *shielditem1, *shielditem2, *potionitem1, *potionitem2;
	wxBitmap *money1, *money2, *money3;
	wxBitmap *bitmapbuy;
	wxBitmapButton *buy1, *buy2, *buy3;

	int rbalok, rbatu, rkayu, rbara, rtanah, rdiamond; //requirement
	int moneyatt, moneydef, moneyheal; //requirement to buy

	void LoadRequirement();
	void LoadAllBitmap();
	void LoadUpgradeBitmap();
	void LoadUpgradeItemBitmap();
	void LoadRequirementBitmap();

	DECLARE_EVENT_TABLE()
};

