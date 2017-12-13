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

	wxBitmap *buttonWindow, *map, *mapblur, *chibi;
	wxBitmap *bitmapstatus, *bitmapbonds, *bitmapinvent, *bitmapskill;
	wxBitmap *huruf[60];
	wxString fileLocation;
	void LoadResourceBitmap();
	void LoadMenuBitmap();
	void LoadHurufbesarBitmap();
	void LoadHurufkecilBitmap();

private:
	Resource();
	Resource(const Resource& obj);
	static Resource* inst;
};

