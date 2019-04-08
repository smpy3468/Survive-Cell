#include"StdAfx.h"
#include "ItemTraditionalSword.h"

ItemTraditionalSword::ItemTraditionalSword() {
	tag = "ItemWeapon";
}



ItemTraditionalSword::ItemTraditionalSword(string tag, int x, int y, int width, int height) :ItemWeapon(tag, x, y, width, height) {
	tag = "ItemWeapon";
	attackDamage = 100;
	attackRange = 100;
	defense = 2;
	LoadAni();
	LoadBitMap(".\\res\\sword_01d.bmp");
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
	
	//家佑測試的
	player->AddEquipment(this);

	//-----------玩家設定-----------------------//
	player->SetAttackDamage(attackDamage);
	player->SetAttackRange(attackRange);
	player->SetDefense(defense);

	//--------------UI設定--------------------------//
	vector<EquipedSlot*> equipedSlots = GameSystem::GetUInterfacesWithTag<EquipedSlot>("EquipedSlot");

	
	for (auto& i: equipedSlots)
	{
		if (i->GetIsEquipmentPicSet() == false)
		{
			i->SetEquipmentPicture(".\\res\\sword_01d.bmp",i->GetX()+15, i->GetY()+8);
			break;
		}
		//還有後續
	}

	//家佑註解掉的
	Dead();
}

/*void ItemTraditionalSword::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber) {

	this->x = hostX;
	this->y = hostY;
	this->playerCurrentAni = playerCurrentAni;
	this->playerAniNumber = playerAniNumber;
}*/

