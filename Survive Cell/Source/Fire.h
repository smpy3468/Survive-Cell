#pragma once
#include"GameObject.h"


class Fire :public GameObject {
	public:
		Fire(string tag, int x, int y, int width, int height, int pictureID);
		void ShowBitMap()override;
	private:
		void LoadAni();
		void AddAniBitMaps(char* pic[], int aniType, int picCount);//�W�[�h�i�ʵe�Ϥ�
		void AddAniBitMap(char* pic, int aniType);//�W�[�ʵe�Ϥ�

		void SetBitMapPosition()override; //�]�w�ʵe���W��
		vector<CAnimation*> ani;//�ʵe
		int currentAni=0;

		const int ANI_FIRE_LEFT = 0;
		const int ANI_FIRE_RIGHT = 1;
		const int LEFT = 1, RIGHT = 2;
}; 