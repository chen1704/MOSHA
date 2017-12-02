#include "Hero.h"

Hero::Hero()
{
	skillatt = 1; skilldef = 1; skillheal = 1;
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

