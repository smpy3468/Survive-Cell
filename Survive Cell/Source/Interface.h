#include "StdAfx.h"
#include "GameObject.h"
#include "GameSystem.h"

class Interface :public GameObject{
	public:
		Interface(string tag, int x, int y ,int width, int height, int pictureID);

	protected:
		vector<CAnimation*> ani;
		void AddAniBitMaps(char* pic[], int aniType, int picCount);					//增加多張動畫圖片
		void AddAniBitMap(char* pic, int aniType);									//增加動畫圖片
		virtual void LoadAni();														//載入動畫
};

