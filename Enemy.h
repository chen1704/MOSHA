#pragma once
#include <string>
using namespace std;

class Enemy
{
public:
	Enemy();
	int hp, attack;
	int hpmax;
	string name;
	~Enemy();
};

