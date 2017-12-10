#include "Hero.h"

Hero::Hero()
{
	skillatt = 1; skilldef = 1; skillheal = 1;
	bondshi = 0; bondhij = 3; bondsak = 6;
	itmlog = 10; itmstone = 10; itmbrick = 10;
	itmdia = 10; itmearth = 10; itmwood = 10;
	name = "Mirai Suenaga";
	hpmax = 40; mpmax = 40; HP = 40; MP = 40;
}


Hero::~Hero()
{
}

Hero * Hero::getInstance()
{
	if (!instance) {
		instance = new Hero();
	}
	return instance;
}

