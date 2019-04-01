#pragma once

//Item
//�D��
//�~��GameObject

#include "GameSystem.h"
#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);
	virtual void Picked();//�Q�߰_
	
				
protected:	
	bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//�P�_�ʵe�O�_�Y����
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
	virtual void Dead()override;
	virtual void LoadAni();
	virtual void ShowBitMap();
	void SetBitMapPosition()override;

	int currentAni = ANI_IDLE;     //IDLE �ʵe
	vector<CAnimation*> ani;//�ʵe
	int attackDamage;		//�����O
	int attackRange;		//�����d��
	int defense;			//���m�O
	int haveEffect;  //�ϧ_ ���S��;
	enum ANI {
		ANI_IDLE = 0,
	};
};