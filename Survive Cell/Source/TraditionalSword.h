#include "StdAfx.h"
#include "Item.h"

class TraditionalSword:public Item{
	public:
		TraditionalSword();
		TraditionalSword(string tag, int x, int y, int width, int height, int pictureID);
	private:
		void LoadAni()override;
		void ShowBitMap()override;
		void Picked()override;
		enum ANI {
			ANI_IDLE = 0,
		};
};