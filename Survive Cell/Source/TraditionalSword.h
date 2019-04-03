#include "StdAfx.h"
#include "Item.h"
#include "SwordWave.h"
class TraditionalSword:public Item{
	public:
		TraditionalSword();
		TraditionalSword(string tag, int x, int y, int width, int height, int pictureID);
	private:
		void LoadAni()override;							//���J�ʵe
		void ShowBitMap()override;						//��ܰʵe
		void Picked()override;							//�X�o�ĪG
		void SetXY(int hostX, int hostY, int playerCurrentAni, int  palyerAniNumber)override;	//��D�������ɧ��ܪZ������m �]���|�޷Q��S�Ī���m

		
		int playerCurrentAni=0, playerAniNumber=0;

		SwordWave* wave = new SwordWave("SwordWave", x, y, 77, 70, IDB_0);
		enum ANI {
			ANI_IDLE = 0,
			ANI_LEFT,
			ANI_RIGHT
		};
};