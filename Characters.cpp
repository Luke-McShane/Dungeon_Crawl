#include "stdafx.h"
#include "Characters.h"


Characters::Characters(string name) : name(name)
{
	if (name == "Rob") {

	}

}

void Characters::setWeapon(bool weaponStatus) {
	weapon = weaponStatus;
}

bool Characters::getWeapon() {
	return weapon;
}

void Characters::changeHP(int hp) {
	lifePoints += hp;
}

int Characters::getHP() {
	return lifePoints;
}

Characters::~Characters()
{
}
