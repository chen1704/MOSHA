#include "Battle2.h"
#include "ImageFrame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <vector>
#define TIMER_ID 2001

BEGIN_EVENT_TABLE(Battle2, wxWindow)
EVT_BUTTON(1001, Battle2::OnClickAttack)
EVT_BUTTON(1002, Battle2::OnClickDefense)
EVT_BUTTON(1003, Battle2::OnClickHeal)
EVT_BUTTON(1004, Battle2::OnClickClaim)
EVT_PAINT(Battle2::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle2::OnTimer)
END_EVENT_TABLE()

Battle2::Battle2(ImageFrame * parent)
	:wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	SetBackgroundColour(*wxWHITE);
	Refresh();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->turn = 0;
	this->renew = 0;

	LoadAllBitmap();
	mirai = Hero::getInstance();
	SetBar();
	CalculateRatio();

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
	delete buttonatt, buttondef, buttonheal;
	delete reward, backmenu, backwin, backlose, balok, bara, gold, attack, defense, heal, claimok;
	for (int i = 0; i < 8; i++) delete mw[i];
	for (int i = 0; i <= 21; i++) delete mh[i];
	for (int i = 9; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 22; i++) delete md[i];
	for (int i = 1; i <= 4; i++) delete ww[i];
	for (int i = 0; i <= 12; i++) delete wa[i];
}

void Battle2::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);
	//	pdc.DrawBitmap(*apa, wxPoint(10, 10));
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	pdc.DrawBitmap(*battlechibi, wxPoint(33, 477));
	pdc.DrawBitmap(*hp, wxPoint(179, 523), true);
	pdc.DrawBitmap(*mp, wxPoint(175, 559), true);
	pdc.DrawBitmap(*hpbar, wxPoint(225, 522), true);
	pdc.DrawBitmap(*mpbar, wxPoint(225, 558), true);
	pdc.DrawBitmap(*hpbarenemy, wxPoint(311, 26), true);

	vector<char> mirainama(mirai->name.begin(), mirai->name.end());
	int i, x, n, y, o;
	x = 175; y = 480; o = mirainama.size();
	for (i = 0; i < o; i++) {
		if (mirainama[i] < 65 || mirainama[i]>122) continue;
		n = mirainama[i] - '0';
		n -= 16;
		pdc.DrawBitmap(*huruf[n], wxPoint(x, y), true);
		x += 16;
	}

	if (turn == 0) //masih belum diapa"in
	{

		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*warrior.hp, 20)); //enemy HP
																				//		wxMessageOutputDebug().Printf("warrior hp %d pjg %d", warrior.hp, warrior.hp*ratioenemy);
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

		if (mirai->MP >= 5) attack->Enable(true);
		if (mirai->MP >= 6) defense->Enable(true);
		if (mirai->MP >= 10) heal->Enable(true);

		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 175));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 175));
		}

		for (int i = 0; i < 4; i++)
			if (renew % 4 == i) pdc.DrawBitmap(*ww[i + 1], wxPoint(228, 144));

	}

	else if (turn == 1) { //attack

		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*warrior.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP


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

		for (int i = 0; i < 4; i++)
			if (renew % 4 == i) pdc.DrawBitmap(*ww[i + 1], wxPoint(234, 144));
	}

	else if (turn == 2) { //defense
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*warrior.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

		for (int i = 0; i <= 21; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*md[22], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*md[i], wxPoint(60, 175));
		}

		for (int i = 0; i < 4; i++)
			if (renew % 4 == i) pdc.DrawBitmap(*ww[i + 1], wxPoint(234, 144));
	}

	else if (turn == 3) { //mirai heal
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*warrior.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP


																			 //		pdc.DrawText("Mirai is healing", wxPoint(100, 100));
		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 17) {
				pdc.DrawBitmap(*mh[17], wxPoint(60, 175));
				renew = 0;
				turn = 4;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*mh[i], wxPoint(60, 175));
		}
		for (int i = 0; i < 4; i++)
			if (renew % 4 == i) pdc.DrawBitmap(*ww[i + 1], wxPoint(234, 144));
	}

	else if (turn == 4) { //Enemy attack
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*warrior.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

																			 //		pdc.DrawText("Enemy attack", wxPoint(100, 100));

		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 175));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 175));
		}

		for (int i = 0; i <= 7; i++)
			if (renew % 13 == i) pdc.DrawBitmap(*wa[i], wxPoint(156, 144));
		for (int i = 8; i < 12; i++) {
			if (renew % 13 == 12) {
				pdc.DrawBitmap(*wa[12], wxPoint(156, 174));
				renew = 0; turn = 0;
			}
			else if (renew % 13 == i) pdc.DrawBitmap(*wa[i], wxPoint(156, 174));
		}
	}

	else if (turn == 5) { //mirai win
		timer->Stop();
		pdc.DrawText(wxT("MIRAI WIN"), wxPoint(300, 100));
		//		wxMessageOutputDebug().Printf("WIN = mirai %d mage %d", mirai->HP, icemage.hp);
		mirai->win = 1;
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(0, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize((double)ratiohp*(double)mirai->HP, 18)); //mirai HP

		pdc.SetTextForeground(*wxWHITE);
		pdc.DrawBitmap(*backwin, wxPoint(57, 17));
		pdc.DrawBitmap(*balok, wxPoint(122, 248));
		pdc.DrawBitmap(*bara, wxPoint(212, 247));
		pdc.DrawBitmap(*gold, wxPoint(305, 247));
		pdc.DrawText(wxT("2"), wxPoint(152, 323));
		pdc.DrawText(wxT("2"), wxPoint(243, 323));
		pdc.DrawText(wxT("50"), wxPoint(338, 323));


		claimok = new wxBitmapButton(this, 1004, *reward, wxPoint(177, 353), wxDefaultSize, wxBORDER_NONE);


	}
	else if (turn == 6) { //mirai lose
		timer->Stop();
		pdc.DrawText(wxT("MIRAI LOSEEEEEE"), wxPoint(200, 100));
		//		wxMessageOutputDebug().Printf("LOSE = mirai %d mage %d", mirai->HP, icemage.hp);
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*(double)warrior.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(0, 18)); //mirai HP

		pdc.DrawBitmap(*backlose, wxPoint(57, 17));
		claimok = new wxBitmapButton(this, 1004, *backmenu, wxPoint(173, 351), wxDefaultSize, wxBORDER_NONE);
	}

}

void Battle2::OnClickAttack(wxCommandEvent & event)
{
	turn = 1;
	renew = 0;

	mirai->MP -= 4;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = warrior.hp - mirai->skillatt;
	if (tempenemy>0) warrior.hp -= mirai->skillatt;
	else {
		warrior.hp -= warrior.hp; tempwin = 1; turn = 5;
	}
	//	wxMessageOutputDebug().Printf("warrior %d\n", warrior.hp);
	if (tempwin == 0) {
		tempmirai = mirai->HP - warrior.attack;
		if (tempmirai > 0) mirai->HP -= warrior.attack;
		else {
			turn = 6;
		}
	}
	//	wxMessageOutputDebug().Printf("mirai %d\n", mirai->HP);

	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);

}

void Battle2::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;

	mirai->MP -= 6;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = warrior.hp - mirai->skillatt;
	if (tempenemy>0) warrior.hp -= mirai->skillatt;
	else {
		warrior.hp -= warrior.hp; tempwin = 1; turn = 5;
	}
	//	wxMessageOutputDebug().Printf("d warrior %d", warrior.hp);
	if (tempwin == 0) {
		tempmirai = mirai->HP - ((1 - (mirai->skilldef / 100)) * 10);
		if (tempmirai > 0) mirai->HP -= ((1 - (mirai->skilldef / 100)) * 10);
		else {
			turn = 6;
		}
		//		wxMessageOutputDebug().Printf("d mirai %d", mirai->HP);
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle2::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;

	mirai->MP -= 10;

	int tempheal, tempmirai;
	tempheal = mirai->HP + mirai->skillheal;
	if (tempheal < mirai->hpmax) {
		mirai->HP += mirai->skillheal;
		//		wxMessageOutputDebug().Printf("access if = tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	else {
		int selisih;
		selisih = mirai->hpmax - mirai->HP;
		mirai->HP += selisih;
		//		wxMessageOutputDebug().Printf("ELSE tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	//	wxMessageOutputDebug().Printf("tempheal %d mirai HP %d", tempheal, mirai->HP);
	tempmirai = mirai->HP - warrior.attack;
	if (tempmirai>0) mirai->HP -= warrior.attack;
	else {
		turn = 6;
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle2::OnClickClaim(wxCommandEvent & event)
{
	parentFrame->ShowMap();
}

void Battle2::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	++renew;
	Refresh();
}

void Battle2::SetBar()
{
	mirai->HP = mirai->hpmax;
	mirai->MP = mirai->mpmax;
	warrior.name = "Knight";
	warrior.hpmax = 60;
	warrior.hp = 60;
	warrior.attack = 15;
}

void Battle2::LoadAllBitmap()
{
	LoadMapBitmap();
	LoadSpriteMiraiBitmap();
	LoadSpriteEnemyBitmap();
	LoadResultBitmap();
	LoadHurufbesarBitmap();
	LoadHurufkecilBitmap();
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

void Battle2::LoadResultBitmap()
{
	wxString loclaim = wxFileName(fileLocation).GetPath() + wxT("\\button reward.png");
	wxImage image1(loclaim, wxBITMAP_TYPE_PNG);
	reward = new wxBitmap(image1);

	wxString loclaim2 = wxFileName(fileLocation).GetPath() + wxT("\\button back.png");
	wxImage image10(loclaim2, wxBITMAP_TYPE_PNG);
	backmenu = new wxBitmap(image10);

	wxString locwin = wxFileName(fileLocation).GetPath() + wxT("\\window win.png");
	wxImage image2(locwin, wxBITMAP_TYPE_PNG);
	backwin = new wxBitmap(image2);

	wxString loclose = wxFileName(fileLocation).GetPath() + wxT("\\window lose.png");
	wxImage image3(loclose, wxBITMAP_TYPE_PNG);
	backlose = new wxBitmap(image3);

	wxString locbalok = wxFileName(fileLocation).GetPath() + wxT("\\drop1.png");
	wxImage image4(locbalok, wxBITMAP_TYPE_PNG);
	balok = new wxBitmap(image4);

	wxString locbara = wxFileName(fileLocation).GetPath() + wxT("\\drop2.png");
	wxImage image5(locbara, wxBITMAP_TYPE_PNG);
	bara = new wxBitmap(image5);

	wxString locuang = wxFileName(fileLocation).GetPath() + wxT("\\drop7.png");
	wxImage image6(locuang, wxBITMAP_TYPE_PNG);
	gold = new wxBitmap(image6);
}

void Battle2::CalculateRatio()
{
	ratioenemy = 168.0 / (double)warrior.hpmax;
	ratiohp = 212.0 / (double)mirai->hpmax;
	ratiomp = 212.0 / (double)mirai->mpmax;
	wxMessageOutputDebug().Printf("ratioenemy %lf", ratioenemy);
	wxMessageOutputDebug().Printf("warrior hp %d pjg %lf", warrior.hp, (double)warrior.hp*ratioenemy);
	wxMessageOutputDebug().Printf("ratio mirai HP %lf MP %lf\n", ratiohp, ratiomp);
	wxMessageOutputDebug().Printf("mirai hp max %d mp max %d\n", mirai->hpmax, mirai->mpmax);

}

void Battle2::LoadSpriteEnemyBitmap()
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

void Battle2::LoadHurufkecilBitmap() {
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\akecil.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[33] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\bkecil.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[34] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\ckecil.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[35] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\dkecil.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[36] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\ekecil.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[37] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\fkecil.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[38] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\gkecil.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[39] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\hkecil.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[40] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\ikecil.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[41] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\jkecil.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[42] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\kkecil.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[43] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\lkecil.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[44] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\mkecil.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[45] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\nkecil.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[46] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\okecil.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[47] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\pkecil.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[48] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\qkecil.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[49] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\rkecil.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[50] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\skecil.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[51] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\tkecil.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[52] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\ukecil.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[53] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\vkecil.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[54] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\wkecil.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[55] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\xkecil.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[56] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\ykecil.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[57] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\zkecil.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[58] = new wxBitmap(image25);
}

void Battle2::LoadHurufbesarBitmap() {
	wxString loca = wxFileName(fileLocation).GetPath() + wxT("\\a.png");
	wxImage image1(loca, wxBITMAP_TYPE_PNG);
	huruf[1] = new wxBitmap(image1);

	wxString locb = wxFileName(fileLocation).GetPath() + wxT("\\b.png");
	wxImage image2(locb, wxBITMAP_TYPE_PNG);
	huruf[2] = new wxBitmap(image2);

	wxString locc = wxFileName(fileLocation).GetPath() + wxT("\\c.png");
	wxImage image3(locc, wxBITMAP_TYPE_PNG);
	huruf[3] = new wxBitmap(image3);

	wxString locd = wxFileName(fileLocation).GetPath() + wxT("\\d.png");
	wxImage image4(locd, wxBITMAP_TYPE_PNG);
	huruf[4] = new wxBitmap(image4);

	wxString loce = wxFileName(fileLocation).GetPath() + wxT("\\e.png");
	wxImage image5(loce, wxBITMAP_TYPE_PNG);
	huruf[5] = new wxBitmap(image5);

	wxString locf = wxFileName(fileLocation).GetPath() + wxT("\\f.png");
	wxImage image6(locf, wxBITMAP_TYPE_PNG);
	huruf[6] = new wxBitmap(image6);

	wxString locg = wxFileName(fileLocation).GetPath() + wxT("\\g.png");
	wxImage image7(locg, wxBITMAP_TYPE_PNG);
	huruf[7] = new wxBitmap(image7);

	wxString loch = wxFileName(fileLocation).GetPath() + wxT("\\h.png");
	wxImage image8(loch, wxBITMAP_TYPE_PNG);
	huruf[8] = new wxBitmap(image8);

	wxString loci = wxFileName(fileLocation).GetPath() + wxT("\\i.png");
	wxImage image26(loci, wxBITMAP_TYPE_PNG);
	huruf[9] = new wxBitmap(image26);

	wxString locj = wxFileName(fileLocation).GetPath() + wxT("\\j.png");
	wxImage image9(locj, wxBITMAP_TYPE_PNG);
	huruf[10] = new wxBitmap(image9);

	wxString lock = wxFileName(fileLocation).GetPath() + wxT("\\k.png");
	wxImage image10(lock, wxBITMAP_TYPE_PNG);
	huruf[11] = new wxBitmap(image10);

	wxString locl = wxFileName(fileLocation).GetPath() + wxT("\\l.png");
	wxImage image11(locl, wxBITMAP_TYPE_PNG);
	huruf[12] = new wxBitmap(image11);

	wxString locm = wxFileName(fileLocation).GetPath() + wxT("\\m.png");
	wxImage image12(locm, wxBITMAP_TYPE_PNG);
	huruf[13] = new wxBitmap(image12);

	wxString locn = wxFileName(fileLocation).GetPath() + wxT("\\n.png");
	wxImage image13(locn, wxBITMAP_TYPE_PNG);
	huruf[14] = new wxBitmap(image13);

	wxString loco = wxFileName(fileLocation).GetPath() + wxT("\\o.png");
	wxImage image14(loco, wxBITMAP_TYPE_PNG);
	huruf[15] = new wxBitmap(image14);

	wxString locp = wxFileName(fileLocation).GetPath() + wxT("\\p.png");
	wxImage image15(locp, wxBITMAP_TYPE_PNG);
	huruf[16] = new wxBitmap(image15);

	wxString locq = wxFileName(fileLocation).GetPath() + wxT("\\q.png");
	wxImage image16(locq, wxBITMAP_TYPE_PNG);
	huruf[17] = new wxBitmap(image16);

	wxString locr = wxFileName(fileLocation).GetPath() + wxT("\\r.png");
	wxImage image17(locr, wxBITMAP_TYPE_PNG);
	huruf[18] = new wxBitmap(image17);

	wxString locs = wxFileName(fileLocation).GetPath() + wxT("\\s.png");
	wxImage image18(locs, wxBITMAP_TYPE_PNG);
	huruf[19] = new wxBitmap(image18);

	wxString loct = wxFileName(fileLocation).GetPath() + wxT("\\t.png");
	wxImage image19(loct, wxBITMAP_TYPE_PNG);
	huruf[20] = new wxBitmap(image19);

	wxString locu = wxFileName(fileLocation).GetPath() + wxT("\\u.png");
	wxImage image20(locu, wxBITMAP_TYPE_PNG);
	huruf[21] = new wxBitmap(image20);

	wxString locv = wxFileName(fileLocation).GetPath() + wxT("\\v.png");
	wxImage image21(locv, wxBITMAP_TYPE_PNG);
	huruf[22] = new wxBitmap(image21);

	wxString locw = wxFileName(fileLocation).GetPath() + wxT("\\w.png");
	wxImage image22(locw, wxBITMAP_TYPE_PNG);
	huruf[23] = new wxBitmap(image22);

	wxString locx = wxFileName(fileLocation).GetPath() + wxT("\\x.png");
	wxImage image23(locx, wxBITMAP_TYPE_PNG);
	huruf[24] = new wxBitmap(image23);

	wxString locy = wxFileName(fileLocation).GetPath() + wxT("\\y.png");
	wxImage image24(locy, wxBITMAP_TYPE_PNG);
	huruf[25] = new wxBitmap(image24);

	wxString locz = wxFileName(fileLocation).GetPath() + wxT("\\z.png");
	wxImage image25(locz, wxBITMAP_TYPE_PNG);
	huruf[26] = new wxBitmap(image25);
}