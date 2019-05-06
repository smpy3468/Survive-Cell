#pragma once
#include"Effect.h"
#include"GameSystem.h"
#include"Player.h"
class Fire :public Effect {
	public:
		Fire(string tag, int x, int y, int width, int height);		//Constructor
		~Fire();
		void ShowBitMap(int hostX, int hostY,  int hostCurrentAni, int attackAniNumber)override;						//��ܰʵe(������)
		

		//bool IsPlayerInRange(int right_fix, int left_fix, int up_fix, int down_fix);	//��̪��ϧάO�_��Ĳ�I��
	private:
		void LoadAni()override;								
		void SetXY(int hostX, int hostY, int hostCurrentAni)override;					//�H��Demon��s���K��m
		//void SetBitMapPosition()override;											//�]�w�ʵe���W��
		//vector<CAnimation*> ani;													//�ʵe��
		//Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		///int currentAni=0;															//�{�b������Ӱʵe	(������K:0, �k����K��:1)
		//int hit = 0;																//�C�@�������K�u��y���@���ˮ`

		enum ANI {
			ANI_FIRE_LEFT = 0,
			ANI_FIRE_RIGHT
		};

}; 