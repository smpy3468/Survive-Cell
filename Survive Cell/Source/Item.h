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
    virtual void ShowBitMap();
	virtual void SetXY(int hostX, int hostY, int playerCurrentAni, int  playerAniNumber);	//�H�۾֦��̲��� �]�wXY
				
protected:	
	bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//�P�_�ʵe�O�_�Y����
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�

	virtual void Dead()override;
	virtual void LoadAni();

	void SetBitMapPosition()override;
	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//�����ʽs�X


	int currentAni = ANI_IDLE;     //IDLE �ʵe
	vector<CAnimation*> ani;//�ʵe
	enum ANI {
		ANI_IDLE = 0,
	};
};