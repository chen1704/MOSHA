#include "ImageFrame.h"
#include "MOSHA.h"
#include "Map.h"

ImageFrame::ImageFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title)
{
//	this->SetInitialSize(wxSize(515, 700));
	this->InitComponents();
}

void ImageFrame::InitComponents()
{
//	if (this->frame==0)	
//	this->mosha = new MOSHA(this);
//	this->frame = mosha->ChangeState();
//	if (this->frame==1)	
//	this->SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
//	this->map = new Map(this);

	boxSizer = new wxBoxSizer(wxHORIZONTAL);

	this->mosha = new MOSHA(this);
	this->mosha->Show(false);
	this->boxSizer->Add(mosha, 1, wxEXPAND, 0);

	this->map = new Map(this);
	this->map->Show(false);
	this->boxSizer->Add(map, 1, wxEXPAND, 0);

	SetSizer(boxSizer);

	ShowStart();
}

void ImageFrame::ShowStart()
{
	this->mosha->Show(true);
	this->map->Show(false);

	fitWindowSize();
}

void ImageFrame::ShowMap()
{
	this->mosha->Show(false);
	this->map->Show(true);
	fitWindowSize();
}

void ImageFrame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(515, 700));
	this->Layout();
}
