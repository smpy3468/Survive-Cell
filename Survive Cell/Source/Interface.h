#include "StdAfx.h"
#include "GameObject.h"
#include "GameSystem.h"

class Interface :public GameObject{
	public:
		Interface(string tag, int x, int y ,int width, int height, int pictureID);

	protected:
		vector<CAnimation*> ani;
		void AddAniBitMaps(char* pic[], int aniType, int picCount);					//�W�[�h�i�ʵe�Ϥ�
		void AddAniBitMap(char* pic, int aniType);									//�W�[�ʵe�Ϥ�
		virtual void LoadAni();														//���J�ʵe
};

