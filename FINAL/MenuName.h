#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"

class MenuName : public wxWindow
{
public:
	MenuName(ImageFrame *parent);
	~MenuName();
	void OnPaint(wxPaintEvent &event);
	void ClickOK(wxCommandEvent &event);

	Hero *mirai;
	Resource *rs;

private:
	ImageFrame *parentFrame;
	wxString fileLocation;

	wxBitmap *OK, *insert, *menu;
	wxTextCtrl *NameEntry;
	void LoadNameBitmap();

	DECLARE_EVENT_TABLE()
};

