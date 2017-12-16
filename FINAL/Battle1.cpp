#include "Battle1.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <vector>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle1, wxWindow)
EVT_PAINT(Battle1::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle1::OnTimer)
EVT_BUTTON(1001, Battle1::OnClickAttack)
EVT_BUTTON(1002, Battle1::OnClickDefense)
EVT_BUTTON(1003, Battle1::OnClickHeal)
EVT_BUTTON(1004, Battle1::OnClickClaim)
END_EVENT_TABLE()


Battle1::Battle1(ImageFrame *parent)
	:wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	SetBackgroundColour(*wxWHITE);
	SetDoubleBuffered(true);
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	mirai = Hero::getInstance();
	mirai->LoadSpriteMiraiBitmap();

	rs = Resource::getInstance();
	rs->LoadBattleBitmap();

	LoadAllBitmap();
	SetBar();
	CalculateRatio();

	attack = new wxBitmapButton(this, 1001, *rs->buttonatt, wxPoint(102, 600), wxDefaultSize, wxBORDER_NONE);
	defense = new wxBitmapButton(this, 1002, *rs->buttondef, wxPoint(209, 600), wxDefaultSize, wxBORDER_NONE);
	heal = new wxBitmapButton(this, 1003, *rs->buttonheal, wxPoint(316, 600), wxDefaultSize, wxBORDER_NONE);

	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}


Battle1::~Battle1()
{
	timer->Stop();
	delete timer;
	delete attack, defense, heal;
	for (int i = 0; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 3; i++) delete mw[i];
}

void Battle1::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);
	
	pdc.SetBackground(*wxWHITE);
	pdc.DrawBitmap(*rs->background[1], wxPoint(0, 0));
	pdc.DrawBitmap(*rs->buttonKotak, wxPoint(0, 455));
	pdc.DrawBitmap(*rs->battlechibi, wxPoint(33, 477));
	pdc.DrawBitmap(*rs->hp, wxPoint(179, 523), true);
	pdc.DrawBitmap(*rs->mp, wxPoint(175, 559), true);
	pdc.DrawBitmap(*rs->hpbar, wxPoint(225, 522), true);
	pdc.DrawBitmap(*rs->mpbar, wxPoint(225, 558), true);
	pdc.DrawBitmap(*rs->hpbarenemy, wxPoint(311, 26), true);

	vector<char> mirainama(mirai->name.begin(), mirai->name.end());
	int i, x, n, y, o;
	x = 175; y = 480; o = mirainama.size();
	for (i = 0; i < o; i++) {
		if (mirainama[i] < 65 || mirainama[i]>122) continue;
		n = mirainama[i] - '0';
		n -= 16;
		pdc.DrawBitmap(*rs->huruf[n], wxPoint(x, y), true);
		x += 16;
	}

	wxFont font1(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	pdc.SetFont(font1);
	pdc.DrawText(icemage.name, wxPoint(315, 7));

	//Set HP MP bar
	pdc.SetBrush(*wxBLUE_BRUSH);
	pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*icemage.hp, 20)); //enemy HP
	pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
	pdc.SetBrush(*wxRED_BRUSH);
	pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

	if (turn == 0) { //nothing
		if (mirai->MP >= mirai->mpatt) attack->Enable(true);
		if (mirai->MP >= mirai->mpdef) defense->Enable(true);
		if (mirai->MP >= mirai->mpheal) heal->Enable(true);

		for (int i = 0; i <= 7; i++) //mirai walk
			if (renew % 8 == i)
				pdc.DrawBitmap(*mirai->mw[i], wxPoint(60, 175));

		for (int i = 0; i <= 3; i++)
			if (renew % 5 == i) pdc.DrawBitmap(*mw[i], wxPoint(125, 105));
			else if (renew % 5 == 4) pdc.DrawBitmap(*mw[0], wxPoint(125, 105));
	}

	else if (turn == 1) { //attack
		
		for (int i = 0; i <= 14; i++) { //mirai shine
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->mh[i], wxPoint(60, 175));
		}

		for (int i = 15; i <= 18; i++) { //change outfit
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->mh[i + 3], wxPoint(60, 175));
		}

		for (int i = 19; i <= 25; i++) {
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->ma[i - 10], wxPoint(60, 175));
		}

		if (renew % 27 == 26) {
			pdc.DrawBitmap(*ma[16], wxPoint(60, 175));
			renew = 0;
			turn = 4;
		}

		for (int i = 0; i <= 3; i++)
			if (renew % 5 == i) pdc.DrawBitmap(*mw[i], wxPoint(125, 105));
			else if (renew % 5 == 4) pdc.DrawBitmap(*mw[0], wxPoint(125, 105));
	}

	else if (turn == 2) {
		
		for (int i = 0; i <= 21; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*mirai->md[22], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*mirai->md[i], wxPoint(60, 175));
		}

		for (int i = 0; i <= 3; i++)
			if (renew % 5 == i) pdc.DrawBitmap(*mw[i], wxPoint(125, 105));
			else if (renew % 5 == 4) pdc.DrawBitmap(*mw[0], wxPoint(125, 105));
	}

	else if (turn == 3) {
		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 17) {
				pdc.DrawBitmap(*mirai->mh[17], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*mirai->mh[i], wxPoint(60, 175));
		}

		for (int i = 0; i <= 3; i++)
			if (renew % 5 == i) pdc.DrawBitmap(*mw[i], wxPoint(125, 105));
			else if (renew % 5 == 4) pdc.DrawBitmap(*mw[0], wxPoint(125, 105));
	}

	else if (turn == 4) { //Enemy attack
		for (int i = 0; i <= 7; i++) //mirai walk
			if (renew % 8 == i)
				pdc.DrawBitmap(*mirai->mw[i], wxPoint(60, 175));

		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 16) {
				pdc.DrawBitmap(*ma[16], wxPoint(125, 105));
				renew = 0;
				turn = 0;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*ma[i], wxPoint(125, 105));
		}
	}
}

void Battle1::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	++renew;
//	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	wxMessageOutputDebug().Printf("Renew %d", renew);
	Refresh();
}

void Battle1::OnClickAttack(wxCommandEvent & event)
{
	turn = 1;
	renew = 0;
	wxMessageOutputDebug().Printf("button Attack has been clicked");

	mirai->MP -= mirai->mpatt;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = icemage.hp - mirai->skillatt;
	if (tempenemy>0) icemage.hp -= mirai->skillatt;
	else {
		icemage.hp -= icemage.hp; tempwin = 1; turn = 5;
	}
	wxMessageOutputDebug().Printf("icemage %d\n", icemage.hp);
	if (tempwin == 0) {
		tempmirai = mirai->HP - icemage.attack;
		if (tempmirai >= 0) mirai->HP -= icemage.attack;
		else {
			turn = 6;
		}
	}
	wxMessageOutputDebug().Printf("mirai %d\n", mirai->HP);

	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle1::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;
	wxMessageOutputDebug().Printf("button Defense has been clicked");

	mirai->MP -= mirai->mpdef;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = icemage.hp - mirai->skillatt;
	if (tempenemy>0) icemage.hp -= mirai->skillatt;
	else {
		icemage.hp -= icemage.hp; tempwin = 1; turn = 5;
	}
	wxMessageOutputDebug().Printf("d icemage %d", icemage.hp);
	if (tempwin == 0) {
		tempmirai = mirai->HP - ((1 - (mirai->skilldef / 100)) * 10);
		if (tempmirai > 0) mirai->HP -= ((1 - (mirai->skilldef / 100)) * 10);
		else {
			turn = 6;
		}
		wxMessageOutputDebug().Printf("d mirai %d", mirai->HP);
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle1::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;
	wxMessageOutputDebug().Printf("button Heal has been clicked");

	mirai->MP -= mirai->mpheal;

	int tempheal, tempmirai;
	tempheal = mirai->HP + mirai->skillheal;
	if (tempheal < mirai->hpmax) {
		mirai->HP += mirai->skillheal;
		wxMessageOutputDebug().Printf("access if = tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	else {
		int selisih;
		selisih = mirai->hpmax - mirai->HP;
		mirai->HP += selisih;
		wxMessageOutputDebug().Printf("ELSE tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	//	wxMessageOutputDebug().Printf("tempheal %d mirai HP %d", tempheal, mirai->HP);
	tempmirai = mirai->HP - icemage.attack;
	if (tempmirai>0) mirai->HP -= icemage.attack;
	else {
		turn = 6;
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle1::OnClickClaim(wxCommandEvent & event)
{
}

void Battle1::LoadAllBitmap()
{
	LoadSpriteEnemyBitmap();
}

void Battle1::LoadSpriteEnemyBitmap()
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

void Battle1::SetBar()
{
	if (mirai->level <= 1) {
		mirai->HP = mirai->hpmax;
		mirai->MP = mirai->mpmax;
		icemage.name = "Ice Mage";
		icemage.hpmax = 50;
		icemage.hp = 50;
		icemage.attack = 10;
	}
	else if (mirai->level <= 4 && mirai->level > 1) {
		mirai->HP = mirai->hpmax;
		mirai->MP = mirai->mpmax;
		icemage.name = "Ice King";
		icemage.hpmax = 80;
		icemage.hp = 80;
		icemage.attack = 45;
	}
}

void Battle1::CalculateRatio()
{
	ratioenemy = 168.0 / (double)icemage.hpmax;
	ratiohp = 212.0 / (double)mirai->hpmax;
	ratiomp = 212.0 / (double)mirai->mpmax;
	wxMessageOutputDebug().Printf("ratioenemy %lf", ratioenemy);
	wxMessageOutputDebug().Printf("ratio mirai HP %lf MP %lf\n", ratiohp, ratiomp);
	wxMessageOutputDebug().Printf("mirai hp max %d mp max %d\n", mirai->hpmax, mirai->mpmax);
}
