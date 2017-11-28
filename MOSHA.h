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
	void OnChar(wxKeyEvent &event);
	void ClickStart(wxCommandEvent &event);
	int ChangeState();
private:

	ImageFrame *parentFrame;

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

