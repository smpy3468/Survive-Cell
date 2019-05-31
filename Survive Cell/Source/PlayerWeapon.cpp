#include "StdAfx.h"
#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon() {
	tag = "PlayerWeapon";
}

PlayerWeapon::~PlayerWeapon()
{
}

PlayerWeapon::PlayerWeapon(ItemWeapon* rhs) :PlayerEquipment(rhs) {
	tag = "PlayerWeapon";
	playerCurrentAni = 0;		
	playerAniNumber = 0;
}