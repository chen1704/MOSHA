#include "Enemy.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
/*
	for (int i = 0; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 3; i++) delete mw[i];

	for (int i = 1; i <= 4; i++) delete ww[i];
	for (int i = 0; i <= 12; i++) delete wa[i];
	for (int i = 1; i <= 8; i++) delete cw[i];
	for (int i = 1; i <= 22; i++) delete ca[i];
*/
}

/*
void Enemy::LoadMageBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	for (int i = 0; i <= 17; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\mageatt");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		ma[i] = new wxBitmap(emage);
	}

	for (int i = 0; i <= 3; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\mageturn");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		mw[i] = new wxBitmap(emage);
	}
	
}

void Enemy::LoadWarriorBitmap()
{
	for (int i = 1; i <= 4; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\warriorwalking");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		ww[i] = new wxBitmap(emage);
	}

	for (int i = 0; i <= 12; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\warrioratas");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		wa[i] = new wxBitmap(emage);
	}
}

void Enemy::LoadChitoseBitmap()
{
	for (int i = 1; i <= 8; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\chitose walking");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		cw[i] = new wxBitmap(emage);
	}

	for (int i = 1; i <= 22; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\chitose");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		ca[i] = new wxBitmap(emage);
	}
}
*/