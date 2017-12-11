#include "Hero.h"

Hero::Hero()
{
	hpmax = 40; mpmax = 30; HP = 40; MP = 30; level = 1;
	skillatt = 1; skilldef = 1; skillheal = 1;
	bondshi = 0; bondhij = 3; bondsak = 6;
	itmlog = 0; itmstone = 0; itmbrick = 0;
	itmdia = 5; itmearth = 6; itmwood = 0;
	money = 100;
	name = "Mirai Suenaga";

	skillatt = 5; skilldef = 10; skillheal = 5;
	//attack -> enemy HP -15
	//def -> reduce mirai HP only 2% of total enemy attack
	//heal -> mirai HP +10
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

