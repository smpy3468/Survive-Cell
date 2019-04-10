#pragma once

//PlayerEquipment
//�D����۪��˳�
#include "Player.h"
#include "Item.h"
#include "ItemWeapon.h"
#include "GameSystem.h"


class PlayerEquipment
{
public:
	PlayerEquipment();
	PlayerEquipment(ItemWeapon* rhs);
	PlayerEquipment* operator=(ItemWeapon* rhs);//�W�[�˳Ʈɥi�����ഫ

	void SetX(int x);
	void SetY(int y);

	string GetTag();

	virtual void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber);	//
	virtual void ShowBitMap();//��ܹϤ�


protected:
	bool IsObjectInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//�P�_�ʵe�O�_�Y����
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
	void LoadBitMap(char* picAddress);											//���J�Ϥ�(CMovingBitamp pic)
	virtual void LoadAni();														//���J�ʵe(CAnimation ani)

	int currentAni = ANI_IDLE;     //IDLE �ʵe
	vector<CAnimation*> ani;//�ʵe

	enum ANI {
		ANI_IDLE = 0,
	};

	string tag;				//
	int x, y;
	int attackDamage;		//�����O
	int attackRange;		//�����d��
	int defense;			//���m�O
	CMovingBitmap pic;
};