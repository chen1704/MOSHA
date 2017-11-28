#pragma once
#include <wx\wx.h>
#include "ImageFrame.h"

class Battle1 : public wxWindow
{
public:
	Battle1(ImageFrame *parent);
	void OnPaint(wxPaintEvent &event);
	void OnTimer(wxTimerEvent &event);
	~Battle1();

private:
	ImageFrame *parentFrame;
	wxTimer *timer;
	wxString fileLocation;

	wxBitmap *map, *buttonWindow;
	wxBitmap *mirai0, *mirai1, *mirai2, *mirai3, *mirai4, *mirai5,
		*mirai6, *mirai7, *mirai8;

	int framerate;

	void LoadAllBitmap();
	void LoadMapBitmap();
	DECLARE_EVENT_TABLE();
};

