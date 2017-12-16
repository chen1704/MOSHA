#include "Battle3.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#include <wx/font.h>
#include <vector>
#define TIMER_ID 2003

BEGIN_EVENT_TABLE(Battle3, wxWindow)
EVT_PAINT(Battle3::OnPaintMirai)
EVT_TIMER(TIMER_ID, Battle3::OnTimer)
EVT_BUTTON(1001, Battle3::OnClickAttack)
EVT_BUTTON(1002, Battle3::OnClickDefense)
EVT_BUTTON(1003, Battle3::OnClickHeal)
EVT_BUTTON(1004, Battle3::OnClickRetreat)
EVT_BUTTON(1005, Battle3::OnClickClaim)
EVT_BUTTON(1006, Battle3::OnClickBackMenu)
END_EVENT_TABLE()




Battle3::Battle3(ImageFrame *parent)
	:wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	Refresh();
	SetBackgroundColour(*wxWHITE);
	SetDoubleBuffered(true);

	mirai = Hero::getInstance();
	rs = Resource::getInstance();

	LoadAllBitmap();
	
	attack = new wxBitmapButton(this, 1001, *rs->buttonatt, wxPoint(102, 600), wxDefaultSize, wxBORDER_NONE);
	defense = new wxBitmapButton(this, 1002, *rs->buttondef, wxPoint(209, 600), wxDefaultSize, wxBORDER_NONE);
	heal = new wxBitmapButton(this, 1003, *rs->buttonheal, wxPoint(316, 600), wxDefaultSize, wxBORDER_NONE);
	retreat = new wxBitmapButton(this, 1004, *rs->retreat[3], wxPoint(362, 404), wxDefaultSize, wxBORDER_NONE);

	buttonwin = new wxBitmapButton(this, 1005, *rs->reward, wxPoint(177, 353), wxDefaultSize, wxBORDER_NONE);
	buttonlose = new wxBitmapButton(this, 1006, *rs->backmenu, wxPoint(177, 353), wxDefaultSize, wxBORDER_NONE);
	buttonwin->Show(false);
	buttonlose->Show(false);
	SetBar();
	CalculateRatio();
	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}


Battle3::~Battle3()
{
	timer->Stop();
	delete timer;
	delete attack, defense, heal, buttonwin, buttonlose, retreat;
	for (int i = 1; i <= 8; i++) delete cw[i];
	for (int i = 1; i <= 23; i++) delete ca[i];

}

void Battle3::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);

	pdc.SetBackground(*wxWHITE);
	pdc.DrawBitmap(*rs->background[3], wxPoint(0, 0));
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
	pdc.SetTextForeground(*wxWHITE);
	pdc.DrawText(chitose.name, wxPoint(315, 7));

	//Set HP MP bar
	pdc.SetBrush(*wxBLUE_BRUSH);
	pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*chitose.hp, 20)); //enemy HP
	pdc.DrawRectangle(wxPoint(235, 568), wxSize(ratiomp*mirai->MP, 18)); //mirai MP
	pdc.SetBrush(*wxRED_BRUSH);
	pdc.DrawRectangle(wxPoint(235, 531), wxSize(ratiohp*mirai->HP, 18)); //mirai HP

	if (turn == 0) { //nothing
		if (mirai->MP >= mirai->mpatt) attack->Enable(true);
		if (mirai->MP >= mirai->mpdef) defense->Enable(true);
		if (mirai->MP >= mirai->mpheal) heal->Enable(true);

		for (int i = 0; i <= 7; i++) //mirai walk
			if (renew % 8 == i) {
				pdc.DrawBitmap(*mirai->mw[i], wxPoint(60, 205));
				pdc.DrawBitmap(*cw[i + 1], wxPoint(250,205)); //chitose walk
			}
	}

	else if (turn == 1) { //attack

		for (int i = 0; i <= 14; i++) { //mirai shine
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->mh[i], wxPoint(60, 205));
		}

		for (int i = 15; i <= 18; i++) { //change outfit
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->mh[i + 3], wxPoint(60, 205));
		}

		for (int i = 19; i <= 25; i++) {
			if (renew % 27 == i) pdc.DrawBitmap(*mirai->ma[i - 10], wxPoint(60, 205));
		}

		if (renew % 27 == 26) {
			pdc.DrawBitmap(*mirai->ma[16], wxPoint(60, 205));
			renew = 0;
			turn = 4;
		}

		for (int i = 0; i <= 7; i++)
			if (renew % 8 == i)
				pdc.DrawBitmap(*cw[i+1], wxPoint(250, 205));
	}

	else if (turn == 2) {

		for (int i = 0; i <= 21; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*mirai->md[22], wxPoint(60, 205));
				renew = 0;
				turn = 4;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*mirai->md[i], wxPoint(60, 205));
		}
		for (int i = 0; i <= 7; i++)
			if (renew % 8 == i)
				pdc.DrawBitmap(*cw[i + 1], wxPoint(250, 205));
	}

	else if (turn == 3) {
		for (int i = 0; i <= 16; i++) {
			if (renew % 18 == 17) {
				pdc.DrawBitmap(*mirai->mh[17], wxPoint(60, 205));
				renew = 0;
				turn = 4;
			}
			else if (renew % 18 == i) pdc.DrawBitmap(*mirai->mh[i], wxPoint(60, 205));
		}
		for (int i = 0; i <= 7; i++)
			if (renew % 8 == i)
				pdc.DrawBitmap(*cw[i + 1], wxPoint(250, 205));
	}

	else if (turn == 4) {
		for (int i = 0; i < 22; i++) {
			if (renew % 23 == 22) {
				pdc.DrawBitmap(*ca[i + 1], wxPoint(250, 205));
				turn = 0;
				renew = 0;
			}
			else if (renew % 23 == i) pdc.DrawBitmap(*ca[i + 1], wxPoint(250, 205));
		}

		for (int i = 0; i <= 7; i++) //mirai walk
			if (renew % 8 == i) 
				pdc.DrawBitmap(*mirai->mw[i], wxPoint(60, 205));

	}

	else if (turn == 5) { //mirai win
		timer->Stop();
		retreat->Show(false);
		buttonwin->Show(true);
		mirai->level = max(mirai->level,4);
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(0, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize((double)ratiohp*(double)mirai->HP, 18)); //mirai HP
/*
		int bawah = 2, atas = 5, randdrop1, randdrop2;
		randdrop1 = rand() % (atas - bawah + 1) + bawah;
		randdrop2 = rand() % (atas - bawah + 1) + bawah;
		int temp1, temp2;
		temp1 = randdrop1;
		temp2 = randdrop2;
		mirai->itmdia += temp1;
		mirai->itmearth += temp2;
		wxString drop1, drop2;
		drop1 = wxString::Format("%d", randdrop1);
		drop2 = wxString::Format("%d", randdrop2);
*/
		pdc.SetTextForeground(*wxWHITE);
		pdc.DrawBitmap(*rs->backwin, wxPoint(57, 17));
		pdc.DrawBitmap(*rs->drop[5], wxPoint(122, 248));
		pdc.DrawBitmap(*rs->drop[4], wxPoint(212, 247));
		pdc.DrawBitmap(*rs->drop[7], wxPoint(305, 247));

		pdc.DrawText(wxT("2"), wxPoint(152, 323));
		pdc.DrawText(wxT("2"), wxPoint(243, 323));

		int min, max, randnum;
		min = 40; max = 50;
		randnum = rand() % (max - min + 1) + min;
		mirai->money += randnum;
		wxString apa;
		apa = wxString::Format("%d", randnum);
		pdc.DrawText(apa, wxPoint(338, 323));
	}

	else if (turn == 6) {
		timer->Stop();
		retreat->Show(false);
		buttonlose->Show(true);
		pdc.SetBrush(*wxBLUE_BRUSH);
		pdc.DrawRectangle(wxPoint(319, 34), wxSize(ratioenemy*(double)chitose.hp, 20)); //enemy HP
		pdc.DrawRectangle(wxPoint(235, 568), wxSize((double)ratiomp*(double)mirai->MP, 18)); //mirai MP
		pdc.SetBrush(*wxRED_BRUSH);
		pdc.DrawRectangle(wxPoint(235, 531), wxSize(0, 18)); //mirai HP

		pdc.DrawBitmap(*rs->backlose, wxPoint(57, 17));
	}

}

void Battle3::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	++renew;
	//	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	//	wxMessageOutputDebug().Printf("Renew %d", renew);
	Refresh();
}

void Battle3::OnClickAttack(wxCommandEvent & event)
{
	turn = 1;
	renew = 0;
	mirai->MP -= mirai->mpatt;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = chitose.hp - mirai->skillatt;
	//simpan selisih HP enemy
	if (tempenemy>0) chitose.hp -= mirai->skillatt; //selama masih >0 (attack)
	else { //jika sudah <0 berarti mirai win
		chitose.hp -= chitose.hp; tempwin = 1; turn = 5;
	}
	wxMessageOutputDebug().Printf("chitose %d\n", chitose.hp);

	wxMessageOutputDebug().Printf("tempwin %d", tempwin);
	if (tempwin == 0) { //jika mirai masih belum win > attack
		tempmirai = mirai->HP - chitose.attack; //simpan selisih HP mirai
		if (tempmirai > 0) mirai->HP -= chitose.attack; //jika selisih >0, attack mirai
		else { //jika tidak mirai lose
			turn = 6;
			tempwin = 0;
			mirai->HP = 0;
		}
	}
	wxMessageOutputDebug().Printf("mirai %d\n", mirai->HP);

	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickDefense(wxCommandEvent & event)
{
	turn = 2;
	renew = 0;
	mirai->MP -= mirai->mpdef;

	int tempenemy, tempmirai, tempwin = 0;
	tempenemy = chitose.hp - mirai->skillatt;
	if (tempenemy>0) chitose.hp -= mirai->skillatt;
	else {
		chitose.hp -= chitose.hp; tempwin = 1; turn = 5;
	}
	wxMessageOutputDebug().Printf("d chitose %d", chitose.hp);
	if (tempwin == 0) {
		tempmirai = mirai->HP - ((1 - (mirai->skilldef / 100)) * chitose.attack);
		if (tempmirai > 0) mirai->HP -= ((1 - (mirai->skilldef / 100)) * chitose.attack);
		else {
			turn = 6;
			mirai->HP = 0;
		}
		wxMessageOutputDebug().Printf("d mirai %d", mirai->HP);
	}
	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickHeal(wxCommandEvent & event)
{
	turn = 3;
	renew = 0;
	int tempheal;
/*
	tempmirai = mirai->HP - chitose.attack;
	if (tempmirai>0) mirai->HP -= chitose.attack;
	else {
		turn = 6;
		mirai->HP = 0;
	}
*/
	tempheal = mirai->HP + (mirai->skillheal - chitose.attack);
	if (tempheal >0 && tempheal < mirai->hpmax) {
		mirai->HP += (mirai->skillheal - chitose.attack);
		wxMessageOutputDebug().Printf("access if = tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	else if (tempheal > mirai->hpmax){
		mirai->HP = mirai->hpmax;
		wxMessageOutputDebug().Printf("ELSE tempheal %d mirai HP %d", tempheal, mirai->HP);
	}
	else if (tempheal<=0){
		turn = 6;
		mirai->HP = 0;
	}
	//	wxMessageOutputDebug().Printf("tempheal %d mirai HP %d", tempheal, mirai->HP);

	attack->Enable(false);
	defense->Enable(false);
	heal->Enable(false);
}

void Battle3::OnClickRetreat(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("button Retreat has been clicked");
	parentFrame->ShowMap();
	SetBar();
	CalculateRatio();
	turn = 0; renew = 0;
	timer->Start(100);
	buttonlose->Show(false);
	buttonwin->Show(false);
}

void Battle3::OnClickClaim(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("claim");
	
		wxMessageOutputDebug().Printf("Claim muncul saat menang");
		mirai->itmdia += 2;
		mirai->itmearth += 2;
		mirai->bondsak += 1;
		wxMessageOutputDebug().Printf("Mirai diamond %d diamond %d", mirai->itmlog, mirai->itmbrick);
	
	parentFrame->ShowMap();
	SetBar();
	CalculateRatio();
	turn = 0; renew = 0;
	timer->Start(100);
	buttonlose->Show(false);
	buttonwin->Show(false);
}

void Battle3::OnClickBackMenu(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("lose back to menu");
	parentFrame->ShowMap();
	SetBar();
	CalculateRatio();
	turn = 0; renew = 0;
	timer->Start(100);
	buttonlose->Show(false);
	buttonwin->Show(false);
}

void Battle3::LoadAllBitmap()
{
	LoadSpriteEnemyBitmap();
}

void Battle3::LoadSpriteEnemyBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();

	for (int i = 1; i <= 8; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\chitose walking");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		cw[i] = new wxBitmap(emage);
	}

	for (int i = 1; i <= 23; i++) {
		wxString elocatt;
		elocatt = wxFileName(fileLocation).GetPath() + wxT("\\chitose");
		elocatt = elocatt + wxString::Format("%d", i);
		elocatt = elocatt + wxT(".png");
		wxImage emage(elocatt, wxBITMAP_TYPE_PNG);
		ca[i] = new wxBitmap(emage);
	}
}

void Battle3::SetBar()
{
	mirai->HP = mirai->hpmax;
	mirai->MP = mirai->mpmax;
	chitose.name = "Lynn Lilliana";
	chitose.hpmax = 70;
	chitose.hp = 70;
	chitose.attack = 18;
	retreat->Show(true);
}

void Battle3::CalculateRatio()
{
	ratioenemy = 168.0 / (double)chitose.hpmax;
	ratiohp = 212.0 / (double)mirai->hpmax;
	ratiomp = 212.0 / (double)mirai->mpmax;
	wxMessageOutputDebug().Printf("ratioenemy %lf", ratioenemy);
	wxMessageOutputDebug().Printf("ratio mirai HP %lf MP %lf\n", ratiohp, ratiomp);
	wxMessageOutputDebug().Printf("mirai hp max %d mp max %d\n", mirai->hpmax, mirai->mpmax);
}
