#include "StdAfx.h"
#include "Weapon.h"

Weapon::Weapon()
{
	tag = "Weapon";
}

Weapon::Weapon(string tag, int x, int y, int width, int height, int pictureID):Item(tag, x, y, width, height, pictureID){
	tag = "Weapon";
	
}
