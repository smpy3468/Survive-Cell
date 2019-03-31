#include "StdAfx.h"
#include "GameObject.h"
#include "GameSystem.h"
#include "Player.h"

class Effect :public GameObject{
public:
	Effect(string tag, int x, int y, int width, int height, int pictureID);
	virtual void SetXY(int demonX, int dmonY, int placeRelativePlayer);					//�H�۾֦��̲��� �]�wXY
	void SetHit(int hit);														//�]�w�O�_������(�C�@�հʵe�u��y���@���ˮ`)

	bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//�P�_�ʵe�O�_�Y����
protected:
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
	void SetBitMapPosition()override;											//�]�w�ʵe���W��
	
	//Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");	
	int currentAni = 0;															//�{�b������Ӱʵe	(������K:0, �k����K��:1)
	int hit = 0;																//�C�@�������K�u��y���@���ˮ`
	const int ANI_LEFT = 3, ANI_RIGHT = 4;						//E�����ʵe

	virtual void ShowBitMap(int attackAniNumber, int currentAni);
	virtual void LoadAni();
	vector<CAnimation*> ani;													//�ʵe��

};
