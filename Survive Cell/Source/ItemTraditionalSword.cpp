#include"StdAfx.h"
#include "ItemTraditionalSword.h"

ItemTraditionalSword::ItemTraditionalSword() {
	tag = "TraditionalSword";
}



ItemTraditionalSword::ItemTraditionalSword(string tag, int x, int y, int width, int height, int pictureID) :ItemWeapon(tag, x, y, width, height, pictureID) {
	tag = "TraditionalSword";
	attackDamage = 100;
	attackRange = 100;
	defense = 2;
	LoadAni();
}



void ItemTraditionalSword::LoadAni() {
	char* aniIdle[1] = { ".\\res\\sword_01d.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);
}

/*void TraditionalSword::ShowBitMap() {

	wave->ShowBitMap(x, y, playerCurrentAni, playerAniNumber);  //int hostX, int hostY, int hostCurrentAni, int attackAniNumber
	ani[currentAni]->OnShow();
}*/

void ItemTraditionalSword::Picked() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	
	//�a�����ժ�
	player->AddEquipment(this);

	//-----------���a�]�w-----------------------//
	player->SetAttackDamage(attackDamage);
	player->SetAttackRange(attackRange);
	player->SetDefense(defense);

	//--------------UI�]�w--------------------------//
	vector<EquipedSlot*> equipedSlots = GameSystem::GetUInterfacesWithTag<EquipedSlot>("EquipedSlot");

	
	for (auto& i: equipedSlots)
	{
		if (i->GetIsEquipmentPicSet() == false)
		{
			i->SetEquipmentPicture(".\\res\\sword_01d.bmp",i->GetX()+15, i->GetY()+8);
			break;
		}
		//�٦�����
	}

	//�a�����ѱ���
	Dead();
}

/*void ItemTraditionalSword::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber) {

	this->x = hostX;
	this->y = hostY;
	this->playerCurrentAni = playerCurrentAni;
	this->playerAniNumber = playerAniNumber;
}*/

