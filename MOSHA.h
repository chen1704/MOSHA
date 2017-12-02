#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"

//file location Nat : D:\\ITS SMT 3\\PBO (C)\\FP\\moshapic\\

class MOSHA : public wxWindow
{
public:
	MOSHA(ImageFrame *parent);
	~MOSHA();
	void OnPaint(wxPaintEvent &event);
	void ClickStart(wxCommandEvent &event);

private:

	ImageFrame *parentFrame;

	wxString fileLocation;
	wxPanel *panel;
	wxBitmap *menu = nullptr;
	wxBitmap *buttonWindow = nullptr;
	wxBitmap *start = nullptr;
	wxBitmap *map = nullptr;
	int state;
	DECLARE_EVENT_TABLE()
	void LoadAllBitmap();
	void LoadMenuBitmap();
	void LoadbuttonWindowBitmap();
	void LoadStartButton();
	void LoadMapButton();
	
};

