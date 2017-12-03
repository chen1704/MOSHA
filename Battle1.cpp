#include "Battle1.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle1, wxWindow)
EVT_BUTTON(1001, Battle1::OnClickAttack)
EVT_BUTTON(1002, Battle1::OnClickDefense)
EVT_BUTTON(1003, Battle1::OnClickHeal)
EVT_PAINT(Battle1::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle1::OnTimer)
END_EVENT_TABLE()

Battle1::Battle1(ImageFrame * parent) :
	wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->turn = 0;
	this->renew = 0;

	LoadAllBitmap();
	mirai = Hero::getInstance();

	wxBitmapButton* attack = new wxBitmapButton(this, 1001, *buttonatt, wxPoint(102, 590), wxDefaultSize, wxBU_AUTODRAW);
	wxBitmapButton* defense = new wxBitmapButton(this, 1002, *buttondef, wxPoint(209, 590), wxDefaultSize, wxBU_AUTODRAW);
	wxBitmapButton* heal = new wxBitmapButton(this, 1003, *buttonheal, wxPoint(316, 590), wxDefaultSize, wxBU_AUTODRAW);

	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}

Battle1::~Battle1()
{
	timer->Stop();
	delete timer;
	delete map;
	delete buttonWindow;
	delete mirai0, mirai1, mirai2, mirai3, mirai4, mirai5, mirai6, mirai7;
	delete e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10,
		e11, e12, e13, e14, e15, e16, t1, t2, t3;
	delete ma0, ma1, ma2, ma3, ma4, ma5, ma6, ma7, ma8, ma9, ma10,
		ma11, ma12, ma13, ma14, ma15, ma16, ma17;
	delete md9, md10, md11, md12, md13, md14, md15, md16;
	delete buttonatt, buttondef, buttonheal;
}


void Battle1::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	if (turn == 0) //masih belum diapa"in
	{
		if (renew % 7 == 0) pdc.DrawBitmap(*mirai0, wxPoint(60, 175));
		else if (renew % 7 == 1) pdc.DrawBitmap(*mirai1, wxPoint(60, 175));
		else if (renew % 7 == 2) pdc.DrawBitmap(*mirai2, wxPoint(60, 175));
		else if (renew % 7 == 3) pdc.DrawBitmap(*mirai3, wxPoint(60, 175));
		else if (renew % 7 == 4) pdc.DrawBitmap(*mirai4, wxPoint(60, 175));
		else if (renew % 7 == 5) pdc.DrawBitmap(*mirai5, wxPoint(60, 175));
		else if (renew % 7 == 6) pdc.DrawBitmap(*mirai6, wxPoint(60, 175));

		if (renew % 5 == 0 || renew % 5 == 4) pdc.DrawBitmap(*t1, wxPoint(125, 105));
		else if (renew % 5 == 1 || renew % 5 == 3) pdc.DrawBitmap(*t2, wxPoint(125, 105));
		else if (renew % 5 == 2) pdc.DrawBitmap(*t3, wxPoint(125, 105));
	}

	else if (turn == 1) {

		if (renew % 27 == 0) pdc.DrawBitmap(*ma0, wxPoint(60, 175));
		else if (renew % 27 == 1) pdc.DrawBitmap(*ma1, wxPoint(60, 175));
		else if (renew % 27 == 2) pdc.DrawBitmap(*ma2, wxPoint(60, 175));
		else if (renew % 27 == 3) pdc.DrawBitmap(*ma3, wxPoint(60, 175));
		else if (renew % 27 == 4) pdc.DrawBitmap(*ma4, wxPoint(60, 175));
		else if (renew % 27 == 5) pdc.DrawBitmap(*ma5, wxPoint(60, 175));

		else if (renew % 27 == 6) pdc.DrawBitmap(*ma6, wxPoint(60, 175));
		else if (renew % 27 == 7) pdc.DrawBitmap(*ma7, wxPoint(60, 175));
		else if (renew % 27 == 8) pdc.DrawBitmap(*ma8, wxPoint(60, 175));
		else if (renew % 27 == 9) pdc.DrawBitmap(*ma9, wxPoint(60, 175));
		else if (renew % 27 == 10) pdc.DrawBitmap(*ma10, wxPoint(60, 175));

		else if (renew % 27 == 11) pdc.DrawBitmap(*ma11, wxPoint(60, 175));
		else if (renew % 27 == 12) pdc.DrawBitmap(*ma12, wxPoint(60, 175));
		else if (renew % 27 == 13) pdc.DrawBitmap(*ma13, wxPoint(60, 175));
		else if (renew % 27 == 14) pdc.DrawBitmap(*ma14, wxPoint(60, 175));

		//change outfit
		else if (renew % 27 == 15) pdc.DrawBitmap(*ma18, wxPoint(60, 175));
		else if (renew % 27 == 16) pdc.DrawBitmap(*ma19, wxPoint(60, 175));
		else if (renew % 27 == 17) pdc.DrawBitmap(*ma20, wxPoint(60, 175));
		else if (renew % 27 == 18) pdc.DrawBitmap(*ma21, wxPoint(60, 175));

		// + retrokyuu
		else if (renew % 27 == 19) pdc.DrawBitmap(*md9, wxPoint(60, 175));
		else if (renew % 27 == 20) pdc.DrawBitmap(*md10, wxPoint(60, 175));
		else if (renew % 27 == 21) pdc.DrawBitmap(*md11, wxPoint(60, 175));
		else if (renew % 27 == 22) pdc.DrawBitmap(*md12, wxPoint(60, 175));
		else if (renew % 27 == 23) pdc.DrawBitmap(*md13, wxPoint(60, 175));
		else if (renew % 27 == 24) pdc.DrawBitmap(*md14, wxPoint(60, 175));
		else if (renew % 27 == 25) pdc.DrawBitmap(*md15, wxPoint(60, 175));
		else if (renew % 27 == 26) {
			pdc.DrawBitmap(*md16, wxPoint(60, 175));
			renew = 0;
			turn = 4;
		}

		if (renew % 5 == 0 || renew % 5 == 4) pdc.DrawBitmap(*t1, wxPoint(125, 105));
		else if (renew % 5 == 1 || renew % 5 == 3) pdc.DrawBitmap(*t2, wxPoint(125, 105));
		else if (renew % 5 == 2) pdc.DrawBitmap(*t3, wxPoint(125, 105));
	}

	else if (turn == 2) {
		if (renew % 23 == 0) pdc.DrawBitmap(*mz0, wxPoint(60, 175));
		else if (renew % 23 == 1) pdc.DrawBitmap(*mz1, wxPoint(60, 175));
		else if (renew % 23 == 2) pdc.DrawBitmap(*mz2, wxPoint(60, 175));
		else if (renew % 23 == 3) pdc.DrawBitmap(*mz3, wxPoint(60, 175));
		else if (renew % 23 == 4) pdc.DrawBitmap(*mz4, wxPoint(60, 175));
		else if (renew % 23 == 5) pdc.DrawBitmap(*mz5, wxPoint(60, 175));

		else if (renew % 23 == 6) pdc.DrawBitmap(*mz6, wxPoint(60, 175));
		else if (renew % 23 == 7) pdc.DrawBitmap(*mz7, wxPoint(60, 175));
		else if (renew % 23 == 8) pdc.DrawBitmap(*mz8, wxPoint(60, 175));
		else if (renew % 23 == 9) pdc.DrawBitmap(*mz9, wxPoint(60, 175));
		else if (renew % 23 == 10) pdc.DrawBitmap(*mz10, wxPoint(60, 175));

		else if (renew % 23 == 11) pdc.DrawBitmap(*mz11, wxPoint(60, 175));
		else if (renew % 23 == 12) pdc.DrawBitmap(*mz12, wxPoint(60, 175));
		else if (renew % 23 == 13) pdc.DrawBitmap(*mz13, wxPoint(60, 175));
		else if (renew % 23 == 14) pdc.DrawBitmap(*mz14, wxPoint(60, 175));

		else if (renew % 23 == 15) pdc.DrawBitmap(*mz15, wxPoint(60, 175));
		else if (renew % 23 == 16) pdc.DrawBitmap(*mz16, wxPoint(60, 175));
		else if (renew % 23 == 17) pdc.DrawBitmap(*mz17, wxPoint(60, 175));
		else if (renew % 23 == 18) pdc.DrawBitmap(*mz18, wxPoint(60, 175));
		else if (renew % 23 == 19) pdc.DrawBitmap(*mz19, wxPoint(60, 175));

		else if (renew % 23 == 20) pdc.DrawBitmap(*mz20, wxPoint(60, 175));
		else if (renew % 23 == 21) pdc.DrawBitmap(*mz21, wxPoint(60, 175));
		else if (renew % 23 == 22) {
			pdc.DrawBitmap(*mz22, wxPoint(60, 175));
			renew = 0;
			turn = 4;
		}

		if (renew % 5 == 0 || renew % 5 == 4) pdc.DrawBitmap(*t1, wxPoint(125, 105));
		else if (renew % 5 == 1 || renew % 5 == 3) pdc.DrawBitmap(*t2, wxPoint(125, 105));
		else if (renew % 5 == 2) pdc.DrawBitmap(*t3, wxPoint(125, 105));
	}

	else if (turn == 3) { //mirai heal
		pdc.DrawText("Mirai is healing", wxPoint(100, 100));
		if (renew % 18 == 0) pdc.DrawBitmap(*ma0, wxPoint(60, 175));
		else if (renew % 18 == 1) pdc.DrawBitmap(*ma1, wxPoint(60, 175));
		else if (renew % 18 == 2) pdc.DrawBitmap(*ma2, wxPoint(60, 175));
		else if (renew % 18 == 3) pdc.DrawBitmap(*ma3, wxPoint(60, 175));
		else if (renew % 18 == 4) pdc.DrawBitmap(*ma4, wxPoint(60, 175));
		else if (renew % 18 == 5) pdc.DrawBitmap(*ma5, wxPoint(60, 175));

		else if (renew % 18 == 6) pdc.DrawBitmap(*ma6, wxPoint(60, 175));
		else if (renew % 18 == 7) pdc.DrawBitmap(*ma7, wxPoint(60, 175));
		else if (renew % 18 == 8) pdc.DrawBitmap(*ma8, wxPoint(60, 175));
		else if (renew % 18 == 9) pdc.DrawBitmap(*ma9, wxPoint(60, 175));
		else if (renew % 18 == 10) pdc.DrawBitmap(*ma10, wxPoint(60, 175));

		else if (renew % 18 == 11) pdc.DrawBitmap(*ma11, wxPoint(60, 175));
		else if (renew % 18 == 12) pdc.DrawBitmap(*ma12, wxPoint(60, 175));
		else if (renew % 18 == 13) pdc.DrawBitmap(*ma13, wxPoint(60, 175));
		else if (renew % 18 == 14) pdc.DrawBitmap(*ma14, wxPoint(60, 175));
		else if (renew % 18 == 15) pdc.DrawBitmap(*ma15, wxPoint(60, 175));

		else if (renew % 18 == 16) pdc.DrawBitmap(*ma16, wxPoint(60, 175));
		else if (renew % 18 == 17) {
			pdc.DrawBitmap(*ma17, wxPoint(60, 175));
			renew = 0;
			turn = 4;
		}

		if (renew % 5 == 0 || renew % 5 == 4) pdc.DrawBitmap(*t1, wxPoint(125, 105));
		else if (renew % 5 == 1 || renew % 5 == 3) pdc.DrawBitmap(*t2, wxPoint(125, 105));
		else if (renew % 5 == 2) pdc.DrawBitmap(*t3, wxPoint(240, 190));
	}

	else if (turn == 4) { //Enemy attack
		pdc.DrawText("Enemy attack", wxPoint(100, 100));
		if (renew % 7 == 0) pdc.DrawBitmap(*mirai0, wxPoint(60, 175));
		else if (renew % 7 == 1) pdc.DrawBitmap(*mirai1, wxPoint(60, 175));
		else if (renew % 7 == 2) pdc.DrawBitmap(*mirai2, wxPoint(60, 175));
		else if (renew % 7 == 3) pdc.DrawBitmap(*mirai3, wxPoint(60, 175));
		else if (renew % 7 == 4) pdc.DrawBitmap(*mirai4, wxPoint(60, 175));
		else if (renew % 7 == 5) pdc.DrawBitmap(*mirai5, wxPoint(60, 175));
		else if (renew % 7 == 6) pdc.DrawBitmap(*mirai6, wxPoint(60, 175));

		if (renew % 18 == 0) pdc.DrawBitmap(*e0, wxPoint(80, 105));
		else if (renew % 18 == 1) pdc.DrawBitmap(*e1, wxPoint(80, 105));
		else if (renew % 18 == 2) pdc.DrawBitmap(*e2, wxPoint(80, 105));
		else if (renew % 18 == 3) pdc.DrawBitmap(*e3, wxPoint(80, 105));
		else if (renew % 18 == 4) pdc.DrawBitmap(*e4, wxPoint(80, 105));
		else if (renew % 18 == 5) pdc.DrawBitmap(*e5, wxPoint(80, 105));

		else if (renew % 18 == 6) pdc.DrawBitmap(*e6, wxPoint(80, 105));
		else if (renew % 18 == 7) pdc.DrawBitmap(*e7, wxPoint(80, 105));
		else if (renew % 18 == 8) pdc.DrawBitmap(*e8, wxPoint(80, 105));
		else if (renew % 18 == 9) pdc.DrawBitmap(*e9, wxPoint(80, 105));
		else if (renew % 18 == 10) pdc.DrawBitmap(*e10, wxPoint(80, 105));

		else if (renew % 18 == 11) pdc.DrawBitmap(*e11, wxPoint(80, 105));
		else if (renew % 18 == 12) pdc.DrawBitmap(*e12, wxPoint(80, 105));
		else if (renew % 18 == 13) pdc.DrawBitmap(*e13, wxPoint(80, 105));
		else if (renew % 18 == 14) pdc.DrawBitmap(*e14, wxPoint(80, 105));
		else if (renew % 18 == 15) pdc.DrawBitmap(*e15, wxPoint(80, 105));

		else if (renew % 18 == 16) {
			pdc.DrawBitmap(*e16, wxPoint(80, 105));
			renew = 0;
			turn = 0;
		}
	}
}

void Battle1::OnClickAttack(wxCommandEvent & event)
{
	//	wxMessageOutputDebug().Printf("the button has been clicked");
	turn = 1;
	renew = 0;
}

void Battle1::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;
}

void Battle1::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;
}

void Battle1::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	//	framerate = counter;
	++renew;
	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	Refresh();
}

void Battle1::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadSpriteMiraiBitmap();
	this->LoadSpriteEnemyBitmap();
}

void Battle1::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString loc;
	loc = wxFileName(fileLocation).GetPath() + wxT("\\bacground battle 1.png");
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

}

void Battle1::LoadSpriteMiraiBitmap()
{
	wxString locmirai0 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking0.png");
	wxImage mi0(locmirai0, wxBITMAP_TYPE_PNG);
	mirai0 = new wxBitmap(mi0);

	wxString locmirai1 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking1.png");
	wxImage mi1(locmirai1, wxBITMAP_TYPE_PNG);
	mirai1 = new wxBitmap(mi1);

	wxString locmirai2 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking2.png");
	wxImage mi2(locmirai2, wxBITMAP_TYPE_PNG);
	mirai2 = new wxBitmap(mi2);

	wxString locmirai3 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking3.png");
	wxImage mi3(locmirai3, wxBITMAP_TYPE_PNG);
	mirai3 = new wxBitmap(mi3);

	wxString locmirai4 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking4.png");
	wxImage mi4(locmirai4, wxBITMAP_TYPE_PNG);
	mirai4 = new wxBitmap(mi4);

	wxString locmirai5 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking5.png");
	wxImage mi5(locmirai5, wxBITMAP_TYPE_PNG);
	mirai5 = new wxBitmap(mi5);

	wxString locmirai6 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking6.png");
	wxImage mi6(locmirai6, wxBITMAP_TYPE_PNG);
	mirai6 = new wxBitmap(mi6);

	wxString locmirai7 = wxFileName(fileLocation).GetPath() + wxT("\\chara-walking7.png");
	wxImage mi7(locmirai7, wxBITMAP_TYPE_PNG);
	mirai7 = new wxBitmap(mi7);

	//load MIRAI-HEAL
	wxString miatt;
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack0.png");
	wxImage a0(miatt, wxBITMAP_TYPE_PNG);
	ma0 = new wxBitmap(a0);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack1.png");
	wxImage a1(miatt, wxBITMAP_TYPE_PNG);
	ma1 = new wxBitmap(a1);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack2.png");
	wxImage a2(miatt, wxBITMAP_TYPE_PNG);
	ma2 = new wxBitmap(a2);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack3.png");
	wxImage a3(miatt, wxBITMAP_TYPE_PNG);
	ma3 = new wxBitmap(a3);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack4.png");
	wxImage a4(miatt, wxBITMAP_TYPE_PNG);
	ma4 = new wxBitmap(a4);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack5.png");
	wxImage a5(miatt, wxBITMAP_TYPE_PNG);
	ma5 = new wxBitmap(a5);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack6.png");
	wxImage a6(miatt, wxBITMAP_TYPE_PNG);
	ma6 = new wxBitmap(a6);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack7.png");
	wxImage a7(miatt, wxBITMAP_TYPE_PNG);
	ma7 = new wxBitmap(a7);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack8.png");
	wxImage a8(miatt, wxBITMAP_TYPE_PNG);
	ma8 = new wxBitmap(a8);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack9.png");
	wxImage a9(miatt, wxBITMAP_TYPE_PNG);
	ma9 = new wxBitmap(a9);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack10.png");
	wxImage a10(miatt, wxBITMAP_TYPE_PNG);
	ma10 = new wxBitmap(a10);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack11.png");
	wxImage a11(miatt, wxBITMAP_TYPE_PNG);
	ma11 = new wxBitmap(a11);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack12.png");
	wxImage a12(miatt, wxBITMAP_TYPE_PNG);
	ma12 = new wxBitmap(a12);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack13.png");
	wxImage a13(miatt, wxBITMAP_TYPE_PNG);
	ma13 = new wxBitmap(a13);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack14.png");
	wxImage a14(miatt, wxBITMAP_TYPE_PNG);
	ma14 = new wxBitmap(a14);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack15.png");
	wxImage a15(miatt, wxBITMAP_TYPE_PNG);
	ma15 = new wxBitmap(a15);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack16.png");
	wxImage a16(miatt, wxBITMAP_TYPE_PNG);
	ma16 = new wxBitmap(a16);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack17.png");
	wxImage a17(miatt, wxBITMAP_TYPE_PNG);
	ma17 = new wxBitmap(a17);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack18.png");
	wxImage a18(miatt, wxBITMAP_TYPE_PNG);
	ma18 = new wxBitmap(a18);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack19.png");
	wxImage a19(miatt, wxBITMAP_TYPE_PNG);
	ma19 = new wxBitmap(a19);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack20.png");
	wxImage a20(miatt, wxBITMAP_TYPE_PNG);
	ma20 = new wxBitmap(a20);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-attack21.png");
	wxImage a21(miatt, wxBITMAP_TYPE_PNG);
	ma21 = new wxBitmap(a21);

	// LOAD MIRAI + ATTACK
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense9.png");
	wxImage d1(miatt, wxBITMAP_TYPE_PNG);
	md9 = new wxBitmap(d1);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense10.png");
	wxImage d2(miatt, wxBITMAP_TYPE_PNG);
	md10 = new wxBitmap(d2);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense11.png");
	wxImage d3(miatt, wxBITMAP_TYPE_PNG);
	md11 = new wxBitmap(d3);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense12.png");
	wxImage d4(miatt, wxBITMAP_TYPE_PNG);
	md12 = new wxBitmap(d4);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense13.png");
	wxImage d5(miatt, wxBITMAP_TYPE_PNG);
	md13 = new wxBitmap(d5);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense14.png");
	wxImage d6(miatt, wxBITMAP_TYPE_PNG);
	md14 = new wxBitmap(d6);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense15.png");
	wxImage d7(miatt, wxBITMAP_TYPE_PNG);
	md15 = new wxBitmap(d7);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\chara-defense16.png");
	wxImage d8(miatt, wxBITMAP_TYPE_PNG);
	md16 = new wxBitmap(d8);

	//LOAD MIRAI + DEFENSE SHIELD
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def0.png");
	wxImage z0(miatt, wxBITMAP_TYPE_PNG);
	mz0 = new wxBitmap(z0);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def1.png");
	wxImage z1(miatt, wxBITMAP_TYPE_PNG);
	mz1 = new wxBitmap(z1);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def2.png");
	wxImage z2(miatt, wxBITMAP_TYPE_PNG);
	mz2 = new wxBitmap(z2);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def3.png");
	wxImage z3(miatt, wxBITMAP_TYPE_PNG);
	mz3 = new wxBitmap(z3);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def4.png");
	wxImage z4(miatt, wxBITMAP_TYPE_PNG);
	mz4 = new wxBitmap(z4);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def5.png");
	wxImage z5(miatt, wxBITMAP_TYPE_PNG);
	mz5 = new wxBitmap(z5);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def6.png");
	wxImage z6(miatt, wxBITMAP_TYPE_PNG);
	mz6 = new wxBitmap(z6);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def7.png");
	wxImage z7(miatt, wxBITMAP_TYPE_PNG);
	mz7 = new wxBitmap(z7);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def8.png");
	wxImage z8(miatt, wxBITMAP_TYPE_PNG);
	mz8 = new wxBitmap(z8);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def9.png");
	wxImage z9(miatt, wxBITMAP_TYPE_PNG);
	mz9 = new wxBitmap(z9);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def10.png");
	wxImage z10(miatt, wxBITMAP_TYPE_PNG);
	mz10 = new wxBitmap(z10);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def11.png");
	wxImage z11(miatt, wxBITMAP_TYPE_PNG);
	mz11 = new wxBitmap(z11);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def12.png");
	wxImage z12(miatt, wxBITMAP_TYPE_PNG);
	mz12 = new wxBitmap(z12);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def13.png");
	wxImage z13(miatt, wxBITMAP_TYPE_PNG);
	mz13 = new wxBitmap(z13);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def14.png");
	wxImage z14(miatt, wxBITMAP_TYPE_PNG);
	mz14 = new wxBitmap(z14);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def15.png");
	wxImage z15(miatt, wxBITMAP_TYPE_PNG);
	mz15 = new wxBitmap(z15);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def16.png");
	wxImage z16(miatt, wxBITMAP_TYPE_PNG);
	mz16 = new wxBitmap(z16);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def17.png");
	wxImage z17(miatt, wxBITMAP_TYPE_PNG);
	mz17 = new wxBitmap(z17);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def18.png");
	wxImage z18(miatt, wxBITMAP_TYPE_PNG);
	mz18 = new wxBitmap(z18);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def19.png");
	wxImage z19(miatt, wxBITMAP_TYPE_PNG);
	mz19 = new wxBitmap(z19);

	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def20.png");
	wxImage z20(miatt, wxBITMAP_TYPE_PNG);
	mz20 = new wxBitmap(z20);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def21.png");
	wxImage z21(miatt, wxBITMAP_TYPE_PNG);
	mz21 = new wxBitmap(z21);
	miatt = wxFileName(fileLocation).GetPath() + wxT("\\def22.png");
	wxImage z22(miatt, wxBITMAP_TYPE_PNG);
	mz22 = new wxBitmap(z22);
}

void Battle1::LoadSpriteEnemyBitmap()
{
	wxString enemy;
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageturn0.png");
	wxImage i1(enemy, wxBITMAP_TYPE_PNG);
	t1 = new wxBitmap(i1);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageturn1.png");
	wxImage i2(enemy, wxBITMAP_TYPE_PNG);
	t2 = new wxBitmap(i2);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageturn2.png");
	wxImage i3(enemy, wxBITMAP_TYPE_PNG);
	t3 = new wxBitmap(i3);

	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt0.png");
	wxImage a0(enemy, wxBITMAP_TYPE_PNG);
	e0 = new wxBitmap(a0);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt1.png");
	wxImage a1(enemy, wxBITMAP_TYPE_PNG);
	e1 = new wxBitmap(a1);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt2.png");
	wxImage a2(enemy, wxBITMAP_TYPE_PNG);
	e2 = new wxBitmap(a2);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt3.png");
	wxImage a3(enemy, wxBITMAP_TYPE_PNG);
	e3 = new wxBitmap(a3);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt4.png");
	wxImage a4(enemy, wxBITMAP_TYPE_PNG);
	e4 = new wxBitmap(a4);

	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt5.png");
	wxImage a5(enemy, wxBITMAP_TYPE_PNG);
	e5 = new wxBitmap(a5);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt6.png");
	wxImage a6(enemy, wxBITMAP_TYPE_PNG);
	e6 = new wxBitmap(a6);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt7.png");
	wxImage a7(enemy, wxBITMAP_TYPE_PNG);
	e7 = new wxBitmap(a7);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt8.png");
	wxImage a8(enemy, wxBITMAP_TYPE_PNG);
	e8 = new wxBitmap(a8);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt9.png");
	wxImage a9(enemy, wxBITMAP_TYPE_PNG);
	e9 = new wxBitmap(a9);

	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt10.png");
	wxImage a10(enemy, wxBITMAP_TYPE_PNG);
	e10 = new wxBitmap(a10);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt11.png");
	wxImage a11(enemy, wxBITMAP_TYPE_PNG);
	e11 = new wxBitmap(a11);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt12.png");
	wxImage a12(enemy, wxBITMAP_TYPE_PNG);
	e12 = new wxBitmap(a12);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt13.png");
	wxImage a13(enemy, wxBITMAP_TYPE_PNG);
	e13 = new wxBitmap(a13);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt14.png");
	wxImage a14(enemy, wxBITMAP_TYPE_PNG);
	e14 = new wxBitmap(a14);

	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt15.png");
	wxImage a15(enemy, wxBITMAP_TYPE_PNG);
	e15 = new wxBitmap(a15);
	enemy = wxFileName(fileLocation).GetPath() + wxT("\\mageatt16.png");
	wxImage a16(enemy, wxBITMAP_TYPE_PNG);
	e16 = new wxBitmap(a16);
}
