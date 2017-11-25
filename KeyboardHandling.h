#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"

class KeyboardHandling : public wxWindow {
public:
	void OnChar(wxKeyEvent &event);
private:
	DECLARE_EVENT_TABLE()
};
