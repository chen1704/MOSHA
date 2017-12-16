//Hero as SINGLETON >> Jadi bisa didefine dimana-mana
#pragma once
#include "wx\wx.h"
#include <string>
using namespace std;

class Hero
{
public:
	~Hero();

	static Hero *getInstance();

	string name;
	int level, money;
	int hpmax, mpmax, HP, MP;
	int skillatt, skilldef, skillheal;
	int mpatt, mpdef, mpheal; //mp requirement
	int itmlog, itmbrick, itmstone, itmearth, itmdia, itmwood;
	int bondshi, bondhij, bondsak; //bond with prince

	//mirai walking
	wxBitmap *mw[10];
	//mirai healing
	wxBitmap *mh[25];
	//mirai attack
	wxBitmap *ma[20];
	//mirai defense
	wxBitmap *md[25];

	void LoadSpriteMiraiBitmap();

private:
	Hero();
	Hero(const Hero& obj);
	static Hero* instance;
};

