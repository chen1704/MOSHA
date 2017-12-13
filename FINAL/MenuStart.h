#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
class Resource;

class MenuStart : public wxWindow
{
public:
	MenuStart(ImageFrame *parent);
	~MenuStart();
	void OnPaint(wxPaintEvent &event);
	void ClickStart(wxCommandEvent &event);

private:
	ImageFrame *parentFrame;
	Resource *rs;

	wxString fileLocation;
	wxBitmap *start, *menu;
	void LoadStartBitmap();

	DECLARE_EVENT_TABLE()
};

