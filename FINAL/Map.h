#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"

class Map : public wxWindow
{
public:
	Map(ImageFrame *parent);
	~Map();
	
	Hero *mirai;
	Resource *rs;

	void OnPaint(wxPaintEvent &event);

	void ClickMap1(wxCommandEvent &event);
	void ClickMap2(wxCommandEvent &event);
	void ClickMap3(wxCommandEvent &event);
	void ClickMap4(wxCommandEvent &event);
	void ClickMap5(wxCommandEvent &event);
	void ClickMap6(wxCommandEvent &event);

	void ClickButtonStatus(wxCommandEvent &event);
	void ClickButtonBonds(wxCommandEvent &event);
	void ClickButtonInventory(wxCommandEvent &event);
	void ClickButtonUpgrade(wxCommandEvent &event);

private:
	ImageFrame *parentFrame;
	wxString fileLocation;
	
	wxBitmap *mp, *hp, *hpbar, *mpbar;
	wxBitmap *mapnum[10];

	void LoadAllBitmap();
	void LoadMapNumberBitmap();
	void LoadMapBitmap();
	DECLARE_EVENT_TABLE()
};

