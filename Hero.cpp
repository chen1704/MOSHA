#include "Hero.h"

Hero::Hero()
{
	skillatt = 1; skilldef = 1; skillheal = 1;
	bondshi = 0; bondhij = 3; bondsak = 6;
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

