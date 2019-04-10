#pragma once

//PlayerEquipment
//主角穿著的裝備#include "GameSystem.h"
#include "ItemWeapon.h"

class Player;

class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(ItemWeapon* rhs);
	PlayerEquipment* operator=(ItemWeapon* rhs);//增加裝備時可直接轉換

	void SetX(int x);
	void SetY(int y);

	string GetTag();

	virtual void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber);	//
	virtual void ShowBitMap();//顯示圖片
	

protected:
	bool IsObjectInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//判斷動畫是否即擊中
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
	void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片
	void LoadBitMap(char* picAddress);											//載入圖片(CMovingBitamp pic)
	void SetBitMapPosition();									//設定動畫位置
	virtual void LoadAni();														//載入動畫(CAnimation ani)

	int currentAni = ANI_IDLE;     //IDLE 動畫
	vector<CAnimation*> ani;//動畫

	enum ANI {
		ANI_IDLE = 0,
	};

	string tag;				//
	int x, y;
	int attackDamage;		//攻擊力
	int attackRange;		//攻擊範圍
	int defense;			//防禦力
	CMovingBitmap pic;
	Player* player= GameSystem::GetGameObjectWithTag<Player>("Player"); 

};