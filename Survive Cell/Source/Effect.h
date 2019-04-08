#include "StdAfx.h"
#include "GameObject.h"
#include "GameSystem.h"
#include "Player.h"

class Effect :public GameObject{
public:
	Effect(string tag, int x, int y, int width, int height);
	
	void SetHit(int hit);														//�]�w�O�_������(�C�@�հʵe�u��y���@���ˮ`)

	virtual void SetXY(int hostX, int hostY, int hostCurrentAni);				//�H�۾֦��̲��� �]�wXY
	virtual void ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber);				//��ܰʵe�S��

protected:
	void EffectAttackMonster(int attackDamage);									//�S�Ĺ���~�y���ˮ`(�C�ӯS�ĥu��y���@���ˮ`(�d��))

	//-------------------------Picture And Animation------------------------------//
	void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
	void SetBitMapPosition()override;											//�]�w�ʵe���W��

	
	virtual void LoadAni();														//���J�ʵe

	//-----------------------------jedgment------------------------------------------------//
	bool IsObjectInRange(GameObject* obj, int right_fix, int left_fix, int up_fix, int down_fix);    //�P�_�ʵe�P����O�_���|
	bool CanMoveLeft(int perDisplacement);//�i�H�V�����ʡAperDisplacement:�C�����첾�q�O�h��
	bool CanMoveRight(int perDisplacement);//�i�H�V�k����
	bool CanMoveUp(int perDisplacement);//�i�H�V�W����
	bool CanMoveDown(int perDisplacement);//�i�H�V�U����

	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	int currentAni = 0;															//�{�b������Ӱʵe	(����:0, �k��:1)
	bool isHit = false;															//�C�@�������K�u��y���@���ˮ`
	const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//E�����ʵe
	vector<CAnimation*> ani;													//�ʵe��
};
