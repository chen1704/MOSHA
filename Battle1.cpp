#include "Battle1.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#define TIMER_ID 2000

BEGIN_EVENT_TABLE(Battle1, wxWindow)
EVT_PAINT(Battle1::OnPaint)
EVT_TIMER(TIMER_ID, Battle1::OnTimer)
END_EVENT_TABLE()

Battle1::Battle1(ImageFrame * parent) :
	wxWindow(parent, wxID_ANY), parentFrame(parent)
{
	SetBackgroundColour(wxColour(*wxWHITE));
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	LoadAllBitmap();

	timer = new wxTimer(this, TIMER_ID);
	timer->Start(100);
}

void Battle1::OnPaint(wxPaintEvent & event)
{
	wxPaintDC pdc(this);
	pdc.DrawBitmap(*map, wxPoint(0, 0), true);
	pdc.DrawBitmap(*buttonWindow, wxPoint(0, 455), true);
	if (framerate % 8 == 0) pdc.DrawBitmap(*mirai0, wxPoint(100, 100), true);
	else if (framerate % 8 == 1) pdc.DrawBitmap(*mirai1, wxPoint(100, 100), true);
	else if (framerate % 8 == 2) pdc.DrawBitmap(*mirai2, wxPoint(100, 100), true);
	else if (framerate % 8 == 3) pdc.DrawBitmap(*mirai3, wxPoint(100, 100), true);
	else if (framerate % 8 == 4) pdc.DrawBitmap(*mirai4, wxPoint(100, 100), true);
	else if (framerate % 8 == 5) pdc.DrawBitmap(*mirai5, wxPoint(100, 100), true);
	else if (framerate % 8 == 6) pdc.DrawBitmap(*mirai6, wxPoint(100, 100), true);
	else if (framerate % 8 == 7) pdc.DrawBitmap(*mirai7, wxPoint(100, 100), true);
}

void Battle1::OnTimer(wxTimerEvent & event)
{
	static int counter = 0;
	framerate = counter;
	wxMessageOutputDebug().Printf("wxTimer %d", counter++);
	Refresh();
}

Battle1::~Battle1()
{
	timer->Stop();
	delete timer;
	delete map;
	delete buttonWindow;
	delete mirai0, mirai1, mirai2, mirai3, mirai4, mirai5, mirai6, mirai7;
}

void Battle1::LoadAllBitmap()
{
	this->LoadMapBitmap();
}

void Battle1::LoadMapBitmap()
{
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	fileLocation = stdPaths.GetExecutablePath();
	wxString locmenu = wxFileName(fileLocation).GetPath() + wxT("\\bacground battle 1.png");
	wxImage image(locmenu, wxBITMAP_TYPE_PNG);
	map = new wxBitmap(image);

	wxString locwindow = wxFileName(fileLocation).GetPath() + wxT("\\button window.png");
	wxImage image2(locwindow, wxBITMAP_TYPE_PNG);
	buttonWindow = new wxBitmap(image2);

	wxString locmirai0 = wxFileName(fileLocation).GetPath() + wxT("\\mirai0.png");
	wxImage mi0(locmirai0, wxBITMAP_TYPE_PNG);
	mirai0 = new wxBitmap(mi0);

	wxString locmirai1 = wxFileName(fileLocation).GetPath() + wxT("\\mirai1.png");
	wxImage mi1(locmirai1, wxBITMAP_TYPE_PNG);
	mirai1 = new wxBitmap(mi1);

	wxString locmirai2 = wxFileName(fileLocation).GetPath() + wxT("\\mirai2.png");
	wxImage mi2(locmirai2, wxBITMAP_TYPE_PNG);
	mirai2 = new wxBitmap(mi2);

	wxString locmirai3 = wxFileName(fileLocation).GetPath() + wxT("\\mirai3.png");
	wxImage mi3(locmirai3, wxBITMAP_TYPE_PNG);
	mirai3 = new wxBitmap(mi3);

	wxString locmirai4 = wxFileName(fileLocation).GetPath() + wxT("\\mirai4.png");
	wxImage mi4(locmirai4, wxBITMAP_TYPE_PNG);
	mirai4 = new wxBitmap(mi4);

	wxString locmirai5 = wxFileName(fileLocation).GetPath() + wxT("\\mirai5.png");
	wxImage mi5(locmirai5, wxBITMAP_TYPE_PNG);
	mirai5 = new wxBitmap(mi5);

	wxString locmirai6 = wxFileName(fileLocation).GetPath() + wxT("\\mirai6.png");
	wxImage mi6(locmirai6, wxBITMAP_TYPE_PNG);
	mirai6 = new wxBitmap(mi6);

	wxString locmirai7 = wxFileName(fileLocation).GetPath() + wxT("\\mirai7.png");
	wxImage mi7(locmirai7, wxBITMAP_TYPE_PNG);
	mirai7 = new wxBitmap(mi7);
}
