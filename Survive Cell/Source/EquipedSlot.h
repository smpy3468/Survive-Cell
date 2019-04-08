#pragma once

#include "UInterface.h"

class EquipedSlot :public UInterface {
	public:
		EquipedSlot(string tag, int x, int y, int width, int height);

		bool GetIsEquipmentPicSet();

		void SetEquipmentPicture(char* pictureAddress, int x, int y);	//��˳�picked �]�wquipment�Ϥ�
		void ShowBitMap()override;										//��ܲ{���Ϥ�(�i��u��UI)
	private:
		CMovingBitmap equipmentPicture;
		bool isEquipmentPicSet = false;
};