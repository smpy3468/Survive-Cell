#include "StdAfx.h"
#include "PlayerEquipment.h"
#include "Player.h"

PlayerEquipment::PlayerEquipment()
{
	tag = "PlayerEquipment";
}

PlayerEquipment::~PlayerEquipment()
{
	for (unsigned int i = 0; i < ani.size(); i++)
	{
		delete ani[i];
	}
	ani.clear();
}

PlayerEquipment::PlayerEquipment(ItemWeapon* rhs):PlayerEquipment()
{	
	player = GameSystem::GetGameObjectWithTag<Player>("Player");				//常用到就先記錄下來
	tag = "PlayerEquipment";
	operator=(rhs);
}

PlayerEquipment* PlayerEquipment::operator=(ItemWeapon* rhs)
{	
	attackDamage = rhs->GetAttackDamage();
	attackRange = rhs->GetAttackRange();
	defense = rhs->GetDefense();
	pic = rhs->objectPic;
	return this;
}

void PlayerEquipment::SetX(int x)
{
	this->x = x;
}

void PlayerEquipment::SetY(int y)
{
	this->y = y;
}

string PlayerEquipment::GetTag()
{
	return tag;
}

int PlayerEquipment::GetAttackDamage()
{
	return attackDamage;
}

int PlayerEquipment::GetAttackRange()
{
	return attackRange;
}

int PlayerEquipment::GetDefense()
{
	return defense;
}

void PlayerEquipment::SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber) {

	this->x = hostX;
	this->y = hostY;
}

void PlayerEquipment::ShowBitMap()
{
	pic.SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
	pic.ShowBitmap();
}


//-----------------------------PROTECTED-----------------------------------//
bool PlayerEquipment::IsObjectInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix) {

	int width = player->GetWidth(), height = player->GetHeight();

	int RIGHT_EDGE = x + player->GetWidth() + right_fix, LEFT_EDGE = x - left_fix,
		UP_EDGE = y - up_fix, DOWN_EDGE = y + height + down_fix;

	int OB_X = obj->GetX(), OB_Y = obj->GetY(), OB_WIDTH = obj->GetWidth(), OB_HEIGHT = obj->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH, OB_LEFT_EDGE = OB_X,
		OB_UP_EDGE = OB_Y, OB_DOWN_EDGE = OB_Y + OB_HEIGHT;

	if (OB_RIGHT_EDGE >= LEFT_EDGE && OB_RIGHT_EDGE <= RIGHT_EDGE)        //人在左, 火焰在右
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE && OB_LEFT_EDGE >= LEFT_EDGE)  //人在右, 火焰在左
		return true;
	return false;
}

void PlayerEquipment::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void PlayerEquipment::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector的大小不夠大
		ani.push_back(new CAnimation);//增加大小

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void PlayerEquipment::LoadBitMap(char* picAddress)
{
	pic.LoadBitmap(picAddress);
}

void PlayerEquipment::SetBitMapPosition()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}

void PlayerEquipment::LoadAni() {}