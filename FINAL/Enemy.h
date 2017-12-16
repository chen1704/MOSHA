#pragma once
#include "wx\wx.h"
#include <string>
using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();

	int hp, hpmax, attack;
	string name;


//	wxBitmap *mw[5], *ma[20]; //battle1, battle4 [mage]
/*
	wxBitmap *ww[5], *wa[15]; //battle2, battle5 [warrior]
	wxBitmap *cw[10], *ca[28]; //battle3, battle6 [chitose]
*/
	wxString fileLocation;

//	void LoadMageBitmap();
/*
	void LoadWarriorBitmap();
	void LoadChitoseBitmap();
*/
};

