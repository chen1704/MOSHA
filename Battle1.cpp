#include "Battle1.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dcbuffer.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle1, wxWindow)
EVT_BUTTON(1001, Battle1::OnClickAttack)
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

	this->turn = true;
	
	LoadAllBitmap();
	mirai = Hero::getInstance();

	wxBitmapButton* attbutton = new wxBitmapButton(this, 1001, *buttonatt, wxPoint(102, 600), wxDefaultSize, wxBU_AUTODRAW);
	wxBitmapButton* defbutton = new wxBitmapButton(this, 1001, *buttondef, wxPoint(209, 600), wxDefaultSize, wxBU_AUTODRAW);
	wxBitmapButton* healbutton = new wxBitmapButton(this, 1001, *buttonheal, wxPoint(316, 600), wxDefaultSize, wxBU_AUTODRAW);

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
	delete buttonatt, buttondef, buttonheal;
}


void Battle1::OnPaintMirai(wxPaintEvent & event)
{
	wxBufferedPaintDC pdc(this);
	PrepareDC(pdc);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);

	if (turn) {
		pdc.DrawText(wxT("yourturn"), wxPoint(100, 10));
		if (framerate % 8 == 0) pdc.DrawBitmap(*mirai0, wxPoint(76, 219), true);
		else if (framerate % 8 == 1) pdc.DrawBitmap(*mirai1, wxPoint(76, 219), true);
		else if (framerate % 8 == 2) pdc.DrawBitmap(*mirai2, wxPoint(76, 219), true);
		else if (framerate % 8 == 3) pdc.DrawBitmap(*mirai3, wxPoint(76, 219), true);
		else if (framerate % 8 == 4) pdc.DrawBitmap(*mirai4, wxPoint(76, 219), true);
		else if (framerate % 8 == 5) pdc.DrawBitmap(*mirai5, wxPoint(76, 219), true);
		else if (framerate % 8 == 6) pdc.DrawBitmap(*mirai6, wxPoint(76, 219), true);
		else if (framerate % 8 == 7) pdc.DrawBitmap(*mirai7, wxPoint(76, 219), true);

		if (framerate % 5 == 0) pdc.DrawBitmap(*t1, wxPoint(206, 170), true);
		else if (framerate % 5 == 1) pdc.DrawBitmap(*t2, wxPoint(206, 170), true);
		else if (framerate % 5 == 2) pdc.DrawBitmap(*t3, wxPoint(206, 170), true);
//		else if (framerate % 5 == 3) pdc.DrawBitmap(*t3, wxPoint(206, 170), true);
		else if (framerate % 5 == 3) pdc.DrawBitmap(*t2, wxPoint(206, 170), true);
		else if (framerate % 5 == 4) pdc.DrawBitmap(*t1, wxPoint(206, 170), true);
	}

	else if (!turn) {
		pdc.DrawText(wxT("Enemy turn"), wxPoint(200, 10));
		if (framerate % 17 == 0) pdc.DrawBitmap(*e0, wxPoint(106, 170), true);
		else if (framerate % 17 == 1) pdc.DrawBitmap(*e1, wxPoint(106, 170), true);
		else if (framerate % 17 == 2) pdc.DrawBitmap(*e2, wxPoint(106, 170), true);
		else if (framerate % 17 == 3) pdc.DrawBitmap(*e3, wxPoint(106, 170), true);
		else if (framerate % 17 == 4) pdc.DrawBitmap(*e4, wxPoint(106, 170), true);
		else if (framerate % 17 == 5) pdc.DrawBitmap(*e5, wxPoint(106, 170), true);

		else if (framerate % 17 == 6) pdc.DrawBitmap(*e6, wxPoint(106, 170), true);
		else if (framerate % 17 == 7) pdc.DrawBitmap(*e7, wxPoint(106, 170), true);
		else if (framerate % 17 == 8) pdc.DrawBitmap(*e8, wxPoint(106, 170), true);
		else if (framerate % 17 == 9) pdc.DrawBitmap(*e9, wxPoint(106, 170), true);
		else if (framerate % 17 == 10) pdc.DrawBitmap(*e10, wxPoint(106, 170), true);

		else if (framerate % 17 == 11) pdc.DrawBitmap(*e11, wxPoint(106, 170), true);
		else if (framerate % 17 == 12) pdc.DrawBitmap(*e12, wxPoint(106, 170), true);
		else if (framerate % 17 == 13) pdc.DrawBitmap(*e13, wxPoint(106, 170), true);
		else if (framerate % 17 == 14) pdc.DrawBitmap(*e14, wxPoint(106, 170), true);
		else if (framerate % 17 == 15) pdc.DrawBitmap(*e15, wxPoint(106, 170), true);
		else if (framerate % 17 == 16) {
			pdc.DrawBitmap(*e16, wxPoint(106, 170), true); turn = true;
		}
	}
}

void Battle1::OnClickAttack(wxCommandEvent & event)
{
	wxMessageOutputDebug().Printf("the button has been clicked");
	turn = false;
}

void Battle1::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	framerate = counter;
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

	loc = wxFileName(fileLocation).GetPath() + wxT("\\battle attack.png");
	wxImage image3(loc, wxBITMAP_TYPE_PNG);
	buttonatt = new wxBitmap(image3);
	loc = wxFileName(fileLocation).GetPath() + wxT("\\battle shield.png");
	wxImage image4(loc, wxBITMAP_TYPE_PNG);
	buttondef = new wxBitmap(image4);
	loc = wxFileName(fileLocation).GetPath() + wxT("\\battle heal.png");
	wxImage image5(loc, wxBITMAP_TYPE_PNG);
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
