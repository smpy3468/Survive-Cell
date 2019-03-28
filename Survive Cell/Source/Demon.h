#include "Monster.h"
//DefenseRange
class Demon:public Monster {
	public:
		Demon();
		Demon::Demon(string tag, int x, int y, int width, int height, int pictureID);
		void Attack()override;
		void AutoMove()override;
	private:
		void LoadAni()override;
};
