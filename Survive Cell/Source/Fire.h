#pragma once
#include"GameObject.h"
#include"GameSystem.h"
#include"Player.h"
class Fire :public GameObject {
	public:
		Fire(string tag, int x, int y, int width, int height, int pictureID);		//Constructor
		void ShowBitMap(int attackAniNumber, int curentAni);						//��ܰʵe(������)
		void SetXY(int demonX, int dmonY, int placeRelativePlayer);					//�H��Demon��s���K��m

		bool Fire::IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix);	//��̪��ϧάO�_��Ĳ�I��
	private:
		void LoadAni();								
		void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
		void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�

		void SetBitMapPosition()override;											//�]�w�ʵe���W��
		vector<CAnimation*> ani;													//�ʵe��
		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		int currentAni=0;															//�{�b������Ӱʵe	(������K:0, �k����K��:1)
		int hit = 0;																//�C�@�������K�u��y���@���ˮ`
		const int ANI_FIRE_LEFT = 0;												//������K��
		const int ANI_FIRE_RIGHT = 1;												//�k����K��
		const int ANI_ATTACK_LEFT = 3, ANI_ATTACK_RIGHT = 4;						//Demon�����ʵe

}; 