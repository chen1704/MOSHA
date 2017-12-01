#include "Hero.h"

Hero::Hero()
{
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

