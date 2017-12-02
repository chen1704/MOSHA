//Hero as SINGLETON >> jadi bisa didefine dimana-mana
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
	int HP, level;
	int skillatt, skilldef, skillheal;
	int itmlog, itmbrick, itmstone, itmearth, itmdia, itmwood;
	int bondshi, bondhij, bondsak;

private:
	Hero();
	Hero(const Hero& obj);
	static Hero* instance;
//	string name;
};

