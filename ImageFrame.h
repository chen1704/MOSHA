#pragma once
#include "wx\wx.h"

class MOSHA;

class ImageFrame : public wxFrame
{
private:
	MOSHA* mosha;
public:
	ImageFrame(const wxString &title);
};

