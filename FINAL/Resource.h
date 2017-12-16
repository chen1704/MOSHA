//singleton of resource
//harus dibuat singleton jika tidak, pindah" pointer lalu error

#pragma once
#include "wx\wx.h"
#include <string>
using namespace std;

class Resource
{
public:
	//	Resource();
	~Resource();
	static Resource *getInstance();
	wxString fileLocation;

	//Main Menu
	wxBitmap *buttonWindow, *map, *mapblur, *chibi;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill;
	wxBitmap *huruf[60];
	void LoadResourceBitmap();
	void LoadMenuBitmap();
	void LoadHurufbesarBitmap();
	void LoadHurufkecilBitmap();

	//Battle
	wxBitmap *background[6], *buttonKotak, *hp, *mp,
		*hpbar, *mpbar, *battlechibi, *hpbarenemy;
	wxBitmap *buttonatt, *buttondef, *buttonheal;
	void LoadBattleBitmap();

private:
	Resource();
	Resource(const Resource& obj);
	static Resource* inst;
};
