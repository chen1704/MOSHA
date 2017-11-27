#pragma once
#include "wx\wx.h"

class MOSHA : public wxWindow
{
public:
	MOSHA(wxFrame *parent);
	~MOSHA();
	void OnPaint(wxPaintEvent &event);
	void OnChar(wxKeyEvent &event);
private:
	wxPanel *panel;
	wxBitmap *menu = nullptr;
	wxBitmap *buttonWindow = nullptr;
	wxBitmap *start = nullptr;
	DECLARE_EVENT_TABLE()
	void LoadMenuBitmap();
	void LoadbuttonWindowBitmap();
	void LoadStartButton();
	void ClickStart(wxCommandEvent &event);
};

