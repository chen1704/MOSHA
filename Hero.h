//Hero as SINGLETON >> jadi bisa didefine dimana-mana
#pragma once
#include "wx\wx.h"

class Hero
{
public:
	~Hero();
	static Hero *getInstance();
	wxString name;

private:
	Hero();
	Hero(const Hero& obj);
	static Hero* instance;
};

