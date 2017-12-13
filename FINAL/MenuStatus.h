#pragma once
#include "wx\wx.h"
#include "ImageFrame.h"
#include "Hero.h"
#include "Resource.h"
#include<vector>
class MenuStatus : public wxWindow
{
public:
	MenuStatus(ImageFrame *parent);
	~MenuStatus();
	void OnPaint(wxPaintEvent &event);
	void OnClickExit(wxCommandEvent &event);
	void OnClickInvent(wxCommandEvent &event);
	void OnClickBond(wxCommandEvent &event);
	void OnClickUpgrade(wxCommandEvent &event);

	Hero *mirai;
	Resource *rs;

private:
	ImageFrame *parentFrame;
	wxString fileLocation;

	wxBitmap *layoutstatus, *exit, *chibistatus, *level, *description;
	wxBitmap *skillattack, *skillshield, *skillheal;
	wxBitmap *txtattack, *txtshield, *txtheal;

	void LoadAllBitmap();
	void LoadStatusBitmap();
	void LoadSkillBitmap();
	DECLARE_EVENT_TABLE()
};

