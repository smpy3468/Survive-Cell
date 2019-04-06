#include"StdAfx.h"
#include"Effect.h"
class SwordWave :public Effect {
	public:
		SwordWave(string tag, int x, int y, int width, int height, int pictureI);
		void ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber)override;	//顯示動畫
		void SetXY(int hostX, int hostY, int hostCurrentAni)override;							//跟著擁有者移動
	private:
		void LoadAni()override;

		enum ANI{
			ANI_SWORDWAVE_IDLE =0,
			ANI_SWORDWAVE_LEFT,
			ANI_SWORDWAVE_RIGHT
		};
};