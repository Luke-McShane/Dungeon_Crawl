#pragma once
#include <iostream>
using namespace std;

class Characters
{
public:
	Characters(string name);
	void setWeapon(bool weaponStatus);
	bool getWeapon();
	void changeHP(int hp);
	int getHP();
	~Characters();
private:
	string name;
	bool weapon = false;
	int lifePoints = 1;
	int movesAllowed;
};

