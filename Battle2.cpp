#include "Battle2.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle2, wxWindow)
EVT_BUTTON(1001, Battle2::OnClickAttack)
EVT_BUTTON(1002, Battle2::OnClickDefense)
EVT_BUTTON(1003, Battle2::OnClickHeal)
EVT_BUTTON(1004, Battle2::OnClickClaim)
EVT_PAINT(Battle2::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle2::OnTimer)
END_EVENT_TABLE()

Battle2::Battle2(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	SetBackgroundColour(*wxWHITE);
	Refresh();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->turn = 0;
	this->renew = 0;

	LoadAllBitmap();
	mirai = Hero::getInstance();

	attack = new wxBitmapButton(this, 1001, *buttonatt, wxPoint(102, 600), wxDefaultSize, wxBU_AUTODRAW);
	defense = new wxBitmapButton(this, 1002, *buttondef, wxPoint(209, 600), wxDefaultSize, wxBU_AUTODRAW);
	heal = new wxBitmapButton(this, 1003, *buttonheal, wxPoint(316, 600), wxDefaultSize, wxBU_AUTODRAW);

	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}

Battle2::~Battle2()
{
	timer->Stop();
	delete timer;
	delete map, buttonWindow, hp, mp, mpbar, hpbar, hpbarenemy, battlechibi;
	delete buttonWindow;
	for (int i = 0; i < 8; i++) delete mw[i];
	for (int i = 0; i <= 21; i++) delete mh[i];
	for (int i = 9; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 22; i++) delete md[i];
	for (int i = 0; i <= 16; i++) delete link[i];

	delete buttonatt, buttondef, buttonheal;
}


void Battle2::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);
	pdc.SetBackground(*wxWHITE);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*battlechibi, wxPoint(33, 477));
	pdc.DrawBitmap(*hp, wxPoint(179, 523), true);
	pdc.DrawBitmap(*mp, wxPoint(175, 559), true);
	pdc.DrawBitmap(*hpbar, wxPoint(225, 522), true);
	pdc.DrawBitmap(*mpbar, wxPoint(225, 558), true);
	pdc.DrawBitmap(*hpbarenemy, wxPoint(311, 26), true);

	wxFont font(20, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxFont font1(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	pdc.SetFont(font);
	pdc.DrawText(mirai->name, wxPoint(185, 485));
	pdc.SetFont(font1);

	if (turn == 0) //masih belum diapa"in
	{
		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 175));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 175));
		}

		if (renew % 2 == 0) pdc.DrawBitmap(*t1, wxPoint(225, 205));
		else if (renew % 2 == 1) pdc.DrawBitmap(*t2, wxPoint(225, 205));
	}

	else if (turn == 1) { //attack
		for (int i = 1; i <= 14; i++) {
			if (renew % 27 == 0) pdc.DrawBitmap(*mh[0], wxPoint(60, 175));
			else if (renew % 27 == i) pdc.DrawBitmap(*mh[i], wxPoint(60, 175));
		}
		// change outfit
		if (renew % 27 == 15) pdc.DrawBitmap(*mh[18], wxPoint(60, 175));
		else if (renew % 27 == 16) pdc.DrawBitmap(*mh[19], wxPoint(60, 175));
		else if (renew % 27 == 17) pdc.DrawBitmap(*mh[20], wxPoint(60, 175));
		else if (renew % 27 == 18) pdc.DrawBitmap(*mh[21], wxPoint(60, 175));
		// + retrokyuu
		else if (renew % 27 == 19) pdc.DrawBitmap(*ma[9], wxPoint(60, 175));
		else if (renew % 27 == 20) pdc.DrawBitmap(*ma[10], wxPoint(60, 175));
		else if (renew % 27 == 21) pdc.DrawBitmap(*ma[11], wxPoint(60, 175));
		else if (renew % 27 == 22) pdc.DrawBitmap(*ma[12], wxPoint(60, 175));
		else if (renew % 27 == 23) pdc.DrawBitmap(*ma[13], wxPoint(60, 175));
		else if (renew % 27 == 24) pdc.DrawBitmap(*ma[14], wxPoint(60, 175));
		else if (renew % 27 == 25) pdc.DrawBitmap(*ma[15], wxPoint(60, 175));
		else if (renew % 27 == 26) {
			pdc.DrawBitmap(*ma[16], wxPoint(60, 175));
			renew = 0;
			turn = 4;
		}

		if (renew % 2 == 0) pdc.DrawBitmap(*t1, wxPoint(225, 205));
		else if (renew % 2 == 1) pdc.DrawBitmap(*t2, wxPoint(225, 205));
	}

	else if (turn == 2) { //defense
		for (int i = 0; i <= 21; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*md[22], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*md[i], wxPoint(60, 175));
		}

		if (renew % 2 == 0) pdc.DrawBitmap(*t1, wxPoint(225, 205));
		else if (renew % 2 == 1) pdc.DrawBitmap(*t2, wxPoint(225, 205));
	}

	else if (turn == 3) { //mirai heal
		pdc.DrawText("Mirai is healing", wxPoint(100, 100));
		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 17) {
				pdc.DrawBitmap(*mh[17], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*mh[i], wxPoint(60, 175));
		}

		if (renew % 2 == 0) pdc.DrawBitmap(*t1, wxPoint(225, 205));
		else if (renew % 2 == 1) pdc.DrawBitmap(*t2, wxPoint(225, 205));
	}

	else if (turn == 4) { //Enemy attack
		pdc.DrawText("Enemy attack", wxPoint(100, 100));

		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 175));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 175));
		}

		for (int i = 1; i <= 10; i++) {
			wxMessageOutputDebug().Printf("link renew : %d", renew);
			if (renew % 11 == 10) {
				pdc.DrawBitmap(*link[2], wxPoint(225, 205));
				renew = 0;
				turn = 0;
			}
			else if(renew % 11 == i)pdc.DrawBitmap(*link[i], wxPoint(225, 205));
		}
	}


	//draw HP
	/*
	pdc.SetBrush(*wxBLUE_BRUSH);
	pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*(double)icemage.hp, 20)); //enemy HP
	pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
	pdc.SetBrush(*wxRED_BRUSH);
	pdc.DrawRectangle(wxPoint(235, 531), wxSize((double)ratiohp*(double)mirai->HP, 18)); //mirai HP
	*/

}

void Battle2::OnClickAttack(wxCommandEvent & event)
{
	turn = 1;
	renew = 0;
	wxMessageOutputDebug().Printf("Mirai attack");
}

void Battle2::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;
	wxMessageOutputDebug().Printf("Mirai defense");
}

void Battle2::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;
	wxMessageOutputDebug().Printf("Mirai healing");
}

void Battle2::OnClickClaim(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Claim muncul saat menang");
}

void Battle2::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	//	framerate = counter;
	++renew;
	//	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	Refresh();
}

void Battle2::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadSpriteMiraiBitmap();
	this->LoadSpriteEnemyBitmap();
}

void Battle2::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString loc;

	loc = wxFileName(fileLocation).GetPath() + wxT("\\bacground battle 2.png");
	wxImage image(loc, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	loc = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image2(loc, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image2);

	wxString locmap1 = wxFileName(fileLocation).GetPath() + wxT("\\battle attack.png");
	wxImage image3(locmap1, wxBITMAP_TYPE_PNG);
	buttonatt = new wxBitmap(image3);

	wxString locmap2 = wxFileName(fileLocation).GetPath() + wxT("\\battle shield.png");
	wxImage image4(locmap2, wxBITMAP_TYPE_PNG);
	buttondef = new wxBitmap(image4);

	wxString locmap3 = wxFileName(fileLocation).GetPath() + wxT("\\battle heal.png");
	wxImage image5(locmap3, wxBITMAP_TYPE_PNG);
	buttonheal = new wxBitmap(image5);

	wxString lochp = wxFileName(fileLocation).GetPath() + wxT("\\window hp.png");
	wxImage image6(lochp, wxBITMAP_TYPE_PNG);
	hp = new wxBitmap(image6);

	wxString locmp = wxFileName(fileLocation).GetPath() + wxT("\\window mp.png");
	wxImage image7(locmp, wxBITMAP_TYPE_PNG);
	mp = new wxBitmap(image7);

	wxString lochpbar = wxFileName(fileLocation).GetPath() + wxT("\\bar hp.png");
	wxImage image8(lochpbar, wxBITMAP_TYPE_PNG);
	hpbar = new wxBitmap(image8);

	wxString locmpbar = wxFileName(fileLocation).GetPath() + wxT("\\bar mp.png");
	wxImage image9(locmpbar, wxBITMAP_TYPE_PNG);
	mpbar = new wxBitmap(image9);

	wxString lochpenemy = wxFileName(fileLocation).GetPath() + wxT("\\bar enemy.png");
	wxImage image10(lochpenemy, wxBITMAP_TYPE_PNG);
	hpbarenemy = new wxBitmap(image10);

	wxString lochibi = wxFileName(fileLocation).GetPath() + wxT("\\battle mirai ikon.png");
	wxImage image11(lochibi, wxBITMAP_TYPE_PNG);
	battlechibi = new wxBitmap(image11);

}

void Battle2::LoadSpriteMiraiBitmap()
{
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

void Battle2::LoadSpriteEnemyBitmap()
{
	wxString enemy;
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\link0.png");
	wxImage i1(enemy, wxBITMAP_TYPE_PNG);
	t1 = new wxBitmap(i1);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\link2.png");
	wxImage i2(enemy, wxBITMAP_TYPE_PNG);
	t2 = new wxBitmap(i2);

	for (int i = 1; i <= 10; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\linkatt");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		link[i] = new wxBitmap(emage);
	}
}
