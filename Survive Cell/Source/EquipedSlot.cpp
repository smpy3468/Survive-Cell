#include "StdAfx.h"
#include "EquipedSlot.h"

EquipedSlot::EquipedSlot(string tag, int x, int y, int width, int height):UInterface(tag, x, y, width, height)
{	
	tag = "EquipmentSlot";
	LoadBitMap(".\\res\\equiped_slot.bmp");
	UIpicture.SetTopLeft(x, y);
}
