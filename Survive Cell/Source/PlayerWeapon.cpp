#include "StdAfx.h"
#include "PlayerWeapon.h"
PlayerWeapon::PlayerWeapon() {
	
}

PlayerWeapon::PlayerWeapon(ItemWeapon rhs) :PlayerEquipment(rhs) {
	playerCurrentAni = 0;		
	playerAniNumber = 0;
}

