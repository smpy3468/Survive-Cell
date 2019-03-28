#include "Monster.h"
#include "Fire.h"
#include "Player.h"
//DefenseRange
class Demon:public Monster {
	public:
		Demon();
		Demon::Demon(string tag, int x, int y, int width, int height, int pictureID);
		void Attack()override;
		void AutoMove()override;
		void ShowBitMap()override;
	private:
		void LoadAni()override;
		Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
		Fire* fire;
};
