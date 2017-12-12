#include "Battle3.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle3, wxWindow)
EVT_BUTTON(1001, Battle3::OnClickAttack)
EVT_BUTTON(1002, Battle3::OnClickDefense)
EVT_BUTTON(1003, Battle3::OnClickHeal)
EVT_BUTTON(1004, Battle3::OnClickClaim)
EVT_PAINT(Battle3::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle3::OnTimer)
END_EVENT_TABLE()

Battle3::Battle3(ImageFrame * parent) : wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	SetBackgroundColour(*wxWHITE);
	Refresh();
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	this->turn = 0;
	this->renew = 0;

	LoadAllBitmap();
	mirai = Hero::getInstance();

	CalculateRatio();

	attack = new wxBitmapButton(this, 1001, *buttonatt, wxPoint(102, 600), wxDefaultSize, wxBU_AUTODRAW);
	defense = new wxBitmapButton(this, 1002, *buttondef, wxPoint(209, 600), wxDefaultSize, wxBU_AUTODRAW);
	heal = new wxBitmapButton(this, 1003, *buttonheal, wxPoint(316, 600), wxDefaultSize, wxBU_AUTODRAW);
	//retreat = new wxBitmapButton(this, 1005, *bitmapret, wxPoint(360, 402), wxDefaultSize, wxBORDER_NONE);

	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}

Battle3::~Battle3()
{
	timer->Stop();
	delete timer;
	delete map, buttonWindow, hp, mp, mpbar, hpbar, hpbarenemy, battlechibi;
	delete buttonWindow;
	for (int i = 0; i < 8; i++) delete mw[i];
	for (int i = 0; i <= 21; i++) delete mh[i];
	for (int i = 9; i <= 16; i++) delete ma[i];
	for (int i = 0; i <= 22; i++) delete md[i];
	for (int i = 1; i <= 8; i++) delete cw[i];

	delete buttonatt, buttondef, buttonheal;
}


void Battle3::OnPaintMirai(wxPaintEvent & event)
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
	pdc.DrawText(chitose.name, wxPoint(315, 7));

	if (turn == 0) //masih belum diapa"in
	{
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
																				
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); 
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18));

		if (mirai->MP >= 5) attack->Enable(true);
		if (mirai->MP >= 6) defense->Enable(true);
		if (mirai->MP >= 10) heal->Enable(true);

		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 205));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 205));
		}

		for (int i = 1; i <= 8; i++) {
			if(renew % 9 == 8) pdc.DrawBitmap(*cw[8], wxPoint(250, 205));
			else if (renew % 9 == i)pdc.DrawBitmap(*cw[i], wxPoint(250, 205));
		}
	}

	else if (turn == 1) { //attack
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP



		for (int i = 1; i <= 14; i++) {
			if (renew % 27 == 0) pdc.DrawBitmap(*mh[0], wxPoint(60, 205));
			else if (renew % 27 == i) pdc.DrawBitmap(*mh[i], wxPoint(60, 205));
		}
		// change outfit
		if (renew % 27 == 15) pdc.DrawBitmap(*mh[18], wxPoint(60, 205));
		else if (renew % 27 == 16) pdc.DrawBitmap(*mh[19], wxPoint(60, 205));
		else if (renew % 27 == 17) pdc.DrawBitmap(*mh[20], wxPoint(60, 205));
		else if (renew % 27 == 18) pdc.DrawBitmap(*mh[21], wxPoint(60, 205));
		// + retrokyuu
		else if (renew % 27 == 19) pdc.DrawBitmap(*ma[9], wxPoint(60, 205));
		else if (renew % 27 == 20) pdc.DrawBitmap(*ma[10], wxPoint(60, 205));
		else if (renew % 27 == 21) pdc.DrawBitmap(*ma[11], wxPoint(60, 205));
		else if (renew % 27 == 22) pdc.DrawBitmap(*ma[12], wxPoint(60, 205));
		else if (renew % 27 == 23) pdc.DrawBitmap(*ma[13], wxPoint(60, 205));
		else if (renew % 27 == 24) pdc.DrawBitmap(*ma[14], wxPoint(60, 205));
		else if (renew % 27 == 25) pdc.DrawBitmap(*ma[15], wxPoint(60, 205));
		else if (renew % 27 == 26) {
			pdc.DrawBitmap(*ma[16], wxPoint(60, 205));
			renew = 0;
			turn = 4;
		}

		for (int i = 1; i <= 8; i++) {
			if (renew % 9 == 8) pdc.DrawBitmap(*cw[8], wxPoint(250, 205));
			else if (renew % 9 == i)pdc.DrawBitmap(*cw[i], wxPoint(250, 205));
		}
	}

	else if (turn == 2) { //defense
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

		for (int i = 0; i <= 21; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*md[22], wxPoint(60, 205));
				renew = 0;
				turn = 4;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*md[i], wxPoint(60, 205));
		}

		for (int i = 1; i <= 8; i++) {
			if (renew % 9 == 8) pdc.DrawBitmap(*cw[8], wxPoint(250, 205));
			else if (renew % 9 == i)pdc.DrawBitmap(*cw[i], wxPoint(250, 205));
		}
	}

	else if (turn == 3) { //mirai heal
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

		pdc.DrawText("Mirai is healing", wxPoint(100, 100));
		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 17) {
				pdc.DrawBitmap(*mh[17], wxPoint(60, 205));
				renew = 0;
				turn = 4;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*mh[i], wxPoint(60, 205));
		}

		for (int i = 1; i <= 8; i++) {
			if (renew % 9 == 8) pdc.DrawBitmap(*cw[8], wxPoint(250, 205));
			else if (renew % 9 == i)pdc.DrawBitmap(*cw[i], wxPoint(250, 205));
		}
	}

	else if (turn == 4) { //Enemy attack
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

		pdc.DrawText("Enemy attack", wxPoint(100, 100));

		for (int i = 1; i <= 6; i++) { //walking
			if (renew % 7 == 0) pdc.DrawBitmap(*mw[0], wxPoint(60, 205));
			else if (renew % 7 == i) pdc.DrawBitmap(*mw[i], wxPoint(60, 205));
		}

		for (int i = 1; i <= 22; i++) {
			wxMessageOutputDebug().Printf("link renew : %d", renew);
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*ca[22], wxPoint(250, 205));
				renew = 0;
				turn = 0;
				break;
			}
			else if (renew % 23 == i)pdc.DrawBitmap(*ca[i], wxPoint(250, 205));
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


		claimok = new wxBitmapButton(this, 1004, *reward, wxPoint(182, 357), wxDefaultSize, wxBORDER_RAISED);


	}
	else if (turn == 6) { //mirai lose
		timer->Stop();
		pdc.DrawText(wxT("MIRAI LOSEEEEEE"), wxPoint(200, 100));
		//		wxMessageOutputDebug().Printf("LOSE = mirai %d mage %d", mirai->HP, icemage.hp);
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*(double)chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(0, 18)); //mirai HP

		pdc.DrawBitmap(*backlose, wxPoint(57, 17));
		claimok = new wxBitmapButton(this, 1004, *backmenu, wxPoint(182, 357), wxDefaultSize, wxBORDER_RAISED);
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

void Battle3::SetBar()
{
	mirai->HP = mirai->hpmax;
	mirai->MP = mirai->mpmax;
	chitose.name = "Chitose";
	chitose.hpmax = 60;
	chitose.hp = 60;
	chitose.attack = 15;
}

void Battle3::OnClickAttack(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Mirai attack");
	turn = 1;
	renew = 0;

	mirai->MP -= 3;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = chitose.hp - mirai->skillatt;
	if (tempenemy>0) chitose.hp -= mirai->skillatt;
	else {
		chitose.hp -= chitose.hp; tempwin = 1; turn = 5;
	}
	if (tempwin == 0) {
		tempmirai = mirai->HP - chitose.attack;
		if (tempmirai >= 0) mirai->HP -= chitose.attack;
		else {
			turn = 6;
		}
	}

	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;
	wxMessageOutputDebug().Printf("Mirai defense");
	mirai->MP -= 4;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = chitose.hp - mirai->skillatt;
	if (tempenemy>0) chitose.hp -= mirai->skillatt;
	else {
		chitose.hp -= chitose.hp; tempwin = 1; turn = 5;
	}
	if (tempwin == 0) {
		tempmirai = mirai->HP - ((1 - (mirai->skilldef / 100)) * 10);
		if (tempmirai > 0) mirai->HP -= ((1 - (mirai->skilldef / 100)) * 10);
		else {
			turn = 6;
		}
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;

	mirai->MP -= 7;

	int tempheal, tempmirai;
	tempheal = mirai->HP + mirai->skillheal;
	if (tempheal < mirai->hpmax) {
		mirai->HP += mirai->skillheal;
	}
	else {
		int selisih;
		selisih = mirai->hpmax - mirai->HP;
		mirai->HP += selisih;
	}
	tempmirai = mirai->HP - chitose.attack;
	if (tempmirai>0) mirai->HP -= chitose.attack;
	else {
		turn = 6;
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickClaim(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("Claim muncul saat menang");
}

void Battle3::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	//	framerate = counter;
	++renew;
	//	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	Refresh();
}

void Battle3::LoadAllBitmap()
{
	this->LoadMapBitmap();
	this->LoadSpriteMiraiBitmap();
	this->LoadResultBitmap();
	this->LoadSpriteEnemyBitmap();
}

void Battle3::LoadResultBitmap()
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

void Battle3::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString loc;

	loc = wxFileName(fileLocation).GetPath() + wxT("\\bacground battle 3.png");
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

	wxString locret = wxFileName(fileLocation).GetPath() + wxT("\\button retreat.png");
	wxImage image12(locret, wxBITMAP_TYPE_PNG);
	bitmapret = new wxBitmap(image12);

}

void Battle3::LoadSpriteMiraiBitmap()
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

void Battle3::CalculateRatio()
{
	ratioenemy = 168.0 / (double)chitose.hpmax;
	ratiohp = 212.0 / (double)mirai->hpmax;
	ratiomp = 212.0 / (double)mirai->mpmax;
	wxMessageOutputDebug().Printf("ratioenemy %lf", ratioenemy);
	wxMessageOutputDebug().Printf("warrior hp %d pjg %lf", chitose.hp, (double)chitose.hp*ratioenemy);
	wxMessageOutputDebug().Printf("ratio mirai HP %lf MP %lf\n", ratiohp, ratiomp);
	wxMessageOutputDebug().Printf("mirai hp max %d mp max %d\n", mirai->hpmax, mirai->mpmax);

}

void Battle3::LoadSpriteEnemyBitmap()
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