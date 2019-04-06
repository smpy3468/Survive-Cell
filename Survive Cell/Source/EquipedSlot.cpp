#include "StdAfx.h"
#include "EquipedSlot.h"

EquipedSlot::EquipedSlot(string tag, int x, int y, int width, int height):UInterface(tag, x, y, width, height)
{	
	this->tag = "EquipedSlot";
	LoadBitMap(".\\res\\equiped_slot.bmp");
	UIpicture.SetTopLeft(x, y);
	isEquipmentPicSet = false;
}

bool EquipedSlot::GetIsEquipmentPicSet()
{
	return this->isEquipmentPicSet;
}

void EquipedSlot::SetEquipmentPicture(char* pictureAddress, int x, int y) {
	equipmentPicture.LoadBitmap(pictureAddress);
	equipmentPicture.SetTopLeft(x, y);
	isEquipmentPicSet = true;
}

void EquipedSlot::ShowBitMap() {
	UIpicture.ShowBitmap();
	if(isEquipmentPicSet==true)
		equipmentPicture.ShowBitmap();
}