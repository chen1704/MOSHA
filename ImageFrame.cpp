#include "ImageFrame.h"
#include "MOSHA.h"
#include "MenuName.h"
#include "Map.h"
#include "MenuStatus.h"
#include "Battle1.h"
#include "Hero.h"
#include "MenuBonds.h"

Hero* Hero::instance = 0;

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

	this->menustatus = new MenuStatus(this);
	this->menustatus->Show(false);
	this->boxSizer->Add(menustatus, 1, wxEXPAND, 0);

	this->battle1 = new Battle1(this);
	this->battle1->Show(false);
	this->boxSizer->Add(battle1, 1, wxEXPAND, 0);

	SetSizer(boxSizer);

	//	ShowStart();
	//ShowBattle1();

	this->menubonds = new MenuBonds(this);
	this->menubonds->Show(false);
	this->boxSizer->Add(menubonds, 1, wxEXPAND, 0);

	ShowMenuBonds();
}

void ImageFrame::ShowStart()
{
	this->mosha->Show(true);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menustatus->Show(false);
	this->battle1->Show(false);
	this->menubonds->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowName()
{
	this->mosha->Show(false);
	this->menuname->Show(true);
	this->map->Show(false);
	this->menustatus->Show(false);
	this->battle1->Show(false);
	this->menubonds->Show(false);

	fitWindowSize();
}

void ImageFrame::ShowMap()
{
	this->mosha->Show(false);
	this->menuname->Show(false);
	this->map->Show(true);
	this->menustatus->Show(false);
	this->battle1->Show(false);
	this->menubonds->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuStatus()
{
	this->mosha->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menustatus->Show(true);
	this->battle1->Show(false);
	this->menubonds->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuBonds() {
	this->mosha->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menustatus->Show(false);
	this->battle1->Show(false);
	this->menubonds->Show(true);
	fitWindowSize();
}

void ImageFrame::ShowBattle1()
{
	this->mosha->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menustatus->Show(false);
	this->battle1->Show(true);
	this->menubonds->Show(false);
	fitWindowSize();
}

void ImageFrame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(515, 700));
	this->Layout();
}
