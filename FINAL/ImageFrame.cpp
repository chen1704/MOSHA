#include <wx/stdpaths.h>
#include <wx/filename.h>

#include "ImageFrame.h"
#include "MenuStart.h"
#include "MenuName.h"
#include "Map.h"
#include "MenuUpgrade.h"
#include "MenuInvent.h"
#include "MenuStatus.h"
#include "MenuBonds.h"
#include "Battle1.h"
#include "Battle2.h"
#include "Battle3.h"
#include "Battle4.h"
#include "Battle5.h"
#include "Battle6.h"
#include "Hero.h"
#include "Resource.h"

Hero *Hero::instance = 0;
Resource *Resource::inst = 0;

ImageFrame::ImageFrame(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	wxIcon icon(wxT("retrokyuu.ico"), wxBITMAP_TYPE_ICO);
	SetIcon(icon);
/*
	rs = Resource::getInstance();
	rs->LoadMenuBitmap();
	rs->LoadResourceBitmap();
*/
	this->InitComponents();
}

ImageFrame::~ImageFrame()
{
}

void ImageFrame::InitComponents()
{
	boxSizer = new wxBoxSizer(wxHORIZONTAL);

	this->menustart = new MenuStart(this);
	this->menustart->Show(false);
	this->boxSizer->Add(menustart, 1, wxEXPAND, 0);

	this->menuname = new MenuName(this);
	this->menuname->Show(false);
	this->boxSizer->Add(menuname, 1, wxEXPAND, 0);

	this->map = new Map(this);
	this->map->Show(false);
	this->boxSizer->Add(map, 1, wxEXPAND, 0);

	this->menuupgrade = new MenuUpgrade(this);
	this->menuupgrade->Show(false);
	this->boxSizer->Add(menuupgrade, 1, wxEXPAND, 0);

	this->menuinvent = new MenuInvent(this);
	this->menuinvent->Show(false);
	this->boxSizer->Add(menuinvent, 1, wxEXPAND, 0);

	this->menustatus = new MenuStatus(this);
	this->menustatus->Show(false);
	this->boxSizer->Add(menustatus, 1, wxEXPAND, 0);

	this->menubonds = new MenuBonds(this);
	this->menubonds->Show(false);
	this->boxSizer->Add(menubonds, 1, wxEXPAND, 0);

	this->battle1 = new Battle1(this);
	this->battle1->Show(false);
	this->boxSizer->Add(battle1, 1, wxEXPAND, 0);

	this->battle2 = new Battle2(this);
	this->battle2->Show(false);
	this->boxSizer->Add(battle2, 1, wxEXPAND, 0);

	this->battle3 = new Battle3(this);
	this->battle3->Show(false);
	this->boxSizer->Add(battle3, 1, wxEXPAND, 0);

	this->battle4 = new Battle4(this);
	this->battle4->Show(false);
	this->boxSizer->Add(battle4, 1, wxEXPAND, 0);

	this->battle5 = new Battle5(this);
	this->battle5->Show(false);
	this->boxSizer->Add(battle5, 1, wxEXPAND, 0);

	this->battle6 = new Battle6(this);
	this->battle6->Show(false);
	this->boxSizer->Add(battle6, 1, wxEXPAND, 0);

	SetSizer(boxSizer);
	ShowStart();

}

void ImageFrame::ShowStart()
{
	this->menustart->Show(true);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowName()
{
	this->menustart->Show(false);
	this->menuname->Show(true);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);

	fitWindowSize();
}

void ImageFrame::ShowMap()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(true);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuUpgrade()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(true);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);


	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuInvent()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(true);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuStatus()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(true);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowMenuBonds()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(true);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle1()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(true);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle2()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(true);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle3()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(true);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle4()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(true);
	this->battle5->Show(false);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle5()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(true);
	this->battle6->Show(false);
	fitWindowSize();
}

void ImageFrame::ShowBattle6()
{
	this->menustart->Show(false);
	this->menuname->Show(false);
	this->map->Show(false);
	this->menuupgrade->Show(false);
	this->menuinvent->Show(false);
	this->menustatus->Show(false);
	this->menubonds->Show(false);

	this->battle1->Show(false);
	this->battle2->Show(false);
	this->battle3->Show(false);
	this->battle4->Show(false);
	this->battle5->Show(false);
	this->battle6->Show(true);
	fitWindowSize();
}

void ImageFrame::fitWindowSize()
{
	this->boxSizer->Fit(this);
	this->boxSizer->SetSizeHints(this);
	this->SetSize(wxSize(515, 700));
	this->Layout();
}
