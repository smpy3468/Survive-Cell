#include "StdAfx.h"
#include "EquipedSlot.h"

EquipedSlot::EquipedSlot(string tag, int x, int y, int width, int height, int ID):UInterface(tag, x, y, width, height)
{	
	this->tag = "EquipedSlot";
	LoadBitMap(".\\res\\equiped_slot.bmp");
	equipmentPicture = new CMovingBitmap();
	UIpicture.SetTopLeft(x, y);
	isEquipmentPicSet = false;
	this->ID = ID;
}

EquipedSlot::~EquipedSlot()
{
	delete equipmentPicture;
}

int EquipedSlot::GetID()
{
	return this->ID;
}

bool EquipedSlot::GetIsEquipmentPicSet()
{
	return this->isEquipmentPicSet;
}

void EquipedSlot::SetEquipmentPicture(char* pictureAddress, int x, int y) {
	if (isEquipmentPicSet == false) {
		equipmentPicture->LoadBitmap(pictureAddress);
		equipmentPicture->SetTopLeft(x, y);
		isEquipmentPicSet = true;
	}
	else {
		delete equipmentPicture;
		equipmentPicture = new CMovingBitmap();
		equipmentPicture->LoadBitmap(pictureAddress);
		equipmentPicture->SetTopLeft(x, y);
		isEquipmentPicSet = true;
	}
}

void EquipedSlot::ShowBitMap() {
	UIpicture.ShowBitmap();
	if(isEquipmentPicSet==true)
		equipmentPicture->ShowBitmap();
}