#include "Hero.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

Hero::Hero()
{
	hpmax = 40; mpmax = 30;
	HP = 40; MP = 30;

//	hpmax = 1000; mpmax = 1000;
//	HP = 1000; MP = 1000;

	level = 1;
	bondshi = bondhij = bondsak = 0;
	itmlog = itmstone = itmbrick = itmdia = itmearth = itmwood = 0;
	money = 100;

	skillatt = 15; skilldef = 20; skillheal = 15;
	mpatt = 3; mpdef = 4; mpheal = 7;
}


Hero::~Hero()
{
	for (int i = 0; i < 8; i++) delete mw[i];
	for (int i = 0; i <= 21; i++) delete mh[i];
	for (int i = 9; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 22; i++) delete md[i];
}

Hero * Hero::getInstance()
{
	if (!instance) {
		instance = new Hero();
	}
	return instance;
}


void Hero::LoadSpriteMiraiBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	//load mirai-walk
	for (int i = 0; i < 8; i++) {
		wxString locwalk;
		locwalk = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking");
		locwalk = locwalk + wxString::Format("%d", i);
		locwalk = locwalk + wxT(".png");
		wxImage mi(locwalk, wxBITMAP_TYPE_PNG);
		mw[i] = new wxBitmap(mi);
	}
	//load mirai-heal
	for (int i = 0; i <= 21; i++) {
		wxString locheal;
		locheal = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack");
		locheal = locheal + wxString::Format("%d", i);
		locheal = locheal + wxT(".png");
		wxImage mi1(locheal, wxBITMAP_TYPE_PNG);
		mh[i] = new wxBitmap(mi1);
	}

	// LOAD MIRAI + ATTACK
	for (int i = 9; i <= 16; i++) {
		wxString locatt;
		locatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense");
		locatt = locatt + wxString::Format("%d", i);
		locatt = locatt + wxT(".png");
		wxImage mi2(locatt, wxBITMAP_TYPE_PNG);
		ma[i] = new wxBitmap(mi2);
	}

	//LOAD MIRAI + DEFENSE SHIELD
	for (int i = 0; i <= 22; i++) {
		wxString locdef;
		locdef = wxFileName(fileLocation).GetPath() + wxT("\\def");
		locdef = locdef + wxString::Format("%d", i);
		locdef = locdef + wxT(".png");
		wxImage mi3(locdef, wxBITMAP_TYPE_PNG);
		md[i] = new wxBitmap(mi3);
	}
}