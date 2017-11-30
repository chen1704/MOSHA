#include "ImageFrame.h"
#include "MOSHA.h"
#include "MenuName.h"
#include "Map.h"
#include "Battle1.h"

ImageFrame::ImageFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title)
{
//	this->SetInitialSize(wxSize(515, 700));
	this->InitComponents();
}

void ImageFrame::InitComponents()
{

	boxSizer = new wxBoxSizer(wxHORIZONTAL);

	this->mosha = new MOSHA(this);
	this->mosha->Show(false);
	this->boxSizer->Add(mosha, 1, wxEXPAND, 0);

	this->menuname = new MenuName(this);
	this->menuname->Show(false);
	this->boxSizer->Add(menuname, 1, wxEXPAND, 0);

	this->map = new Map(this);
	this->map->Show(false);
	this->boxSizer->Add(map, 1, wxEXPAND, 0);

	this->battle1 = new Battle1(this);
	this->battle1->Show(false);
	this->boxSizer->Add(battle1, 1, wxEXPAND, 0);

	SetSizer(boxSizer);

	ShowStart();
}

void ImageFrame::ShowStart()
{
	this->mosha->Show(true);
	this->menuname->Show(false);
	this->map->Show(false);
	this->battle1->Show(false);

	fitWindowSize();
}

void ImageFrame::ShowName()
{
	this->mosha->Show(false);
	this->menuname->Show(true);
	this->map->Show(false);
	this->battle1->Show(false);
	
	fitWindowSize();
}

void ImageFrame::ShowMap()
{
	this->map->Show(true);
	this->mosha->Show(false);
	this->menuname->Show(false);
	this->battle1->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle1()
{
	this->battle1->Show(true);
	this->map->Show(false);
	this->mosha->Show(false);
	fitWindowSize();
}

void ImageFrame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(515, 700));
	this->Layout();
}
