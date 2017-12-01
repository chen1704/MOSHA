#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"

class MenuName : public wxWindow
{
public:
	MenuName(ImageFrame *parent);
	~MenuName();

	void OnPaint(wxPaintEvent &event);
	void ClickOK(wxCommandEvent &event);

	Hero *mirai;
private:
	ImageFrame *parentFrame;
	wxString fileLocation;

	wxBitmap *menu = nullptr;
	wxBitmap *buttonWindow = nullptr;
	wxBitmap *OK = nullptr;
	wxTextCtrl *NameEntry;
	void LoadAllBitmap();
	void LoadMenuBitmap();
	void LoadbuttonWindowBitmap();

	DECLARE_EVENT_TABLE()
};

