#include "StdAfx.h"
#include "GameObject.h"
#include "GameSystem.h"
#include "Player.h"

class Effect :public GameObject{
public:
	Effect(string tag, int x, int y, int width, int height, int pictureID);
	
	void SetHit(int hit);														//�]�w�O�_������(�C�@�հʵe�u��y���@���ˮ`)
	virtual void ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber);				//��ܰʵe�S��

	bool IsPlayerInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);//�P�_�ʵe�O�_�Y����
protected:
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
	void SetBitMapPosition()override;											//�]�w�ʵe���W��

	
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");	
	int currentAni = 0;															//�{�b������Ӱʵe	(����:0, �k��:1)
	int hit = 0;																//�C�@�������K�u��y���@���ˮ`
	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//E�����ʵe

	virtual void SetXY(int hostX, int hostY, int hostCurrentAni);					//�H�۾֦��̲��� �]�wXY
	virtual void LoadAni();														//���J�ʵe
	vector<CAnimation*> ani;													//�ʵe��

};
