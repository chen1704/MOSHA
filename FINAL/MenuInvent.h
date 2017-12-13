#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"

class MenuInvent : public wxWindow
{
public:
	MenuInvent(ImageFrame *parent);
	~MenuInvent();

	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);
	void OnClickStatus(wxCommandEvent &event);
	void OnClickBond(wxCommandEvent &event);
	void OnClickUpgrade(wxCommandEvent &event);
	Hero *mirai;
	Resource *rs;

private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	wxBitmap *inventory, *description, *exit;
	wxBitmap *balok, *batu, *kayu, *bara, *tanah, *diamond;

	void LoadAllBitmap();
	void LoadInventBitmap();
	void LoadItemBitmap();
	DECLARE_EVENT_TABLE()
};

