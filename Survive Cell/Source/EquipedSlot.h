#pragma once

#include "UInterface.h"

class EquipedSlot :public UInterface {
	public:
		EquipedSlot(string tag, int x, int y, int width, int height);

		bool GetIsEquipmentPicSet();

		void SetEquipmentPicture(char* pictureAddress, int x, int y);	//當裝備picked 設定quipment圖片
		void ShowBitMap()override;										//顯示現有圖片(可能只有UI)
	private:
		CMovingBitmap equipmentPicture;
		bool isEquipmentPicSet = false;
};