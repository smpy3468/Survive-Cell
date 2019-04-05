#include"StdAfx.h"
#include"SwordWave.h"

SwordWave::SwordWave(string tag, int x, int y, int width, int height, int pictureID) :Effect(tag, x, y, width, height, pictureID) {
	tag = "SwordWave";
	LoadAni();
	SetBitMapPosition(); 
	currentAni = ANI_SWORDWAVE_IDLE;
}

void SwordWave::ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber) {
	if(attackAniNumber == 0&&(hostCurrentAni== ANI_ATTACK_LEFT || hostCurrentAni == ANI_ATTACK_RIGHT)){
		SetXY(hostX, hostY, hostCurrentAni);
	}
	else if (attackAniNumber >= 1 && currentAni == ANI_SWORDWAVE_LEFT && CanMoveLeft(5)) { //3是左攻擊狀態
		x -= 5;																//讓Wave往左飛
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player, 0, 0, 0, 0) && ani[currentAni]->GetCurrentBitmapNumber() >= 2 && hit == 0) {
			player->DecreaseHP(1);
			hit = 1;
		}
	}
	else if (attackAniNumber >= 1 && currentAni == ANI_SWORDWAVE_RIGHT && CanMoveRight(5)) {       //4是右攻擊狀態
		x += 5;																//讓Wave往右飛
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		if (IsObjectInRange(player, 0, 0, 0, 0) && ani[currentAni]->GetCurrentBitmapNumber() >= 0 && hit == 0) {
			player->DecreaseHP(1);
			hit = 1;
		}
	}
	else {
		hit = 0;
		currentAni = ANI_SWORDWAVE_IDLE;
	}
}

void SwordWave::SetXY(int hostX, int hostY, int hostCurrentAni) {
	if (hostCurrentAni == ANI_ATTACK_LEFT) {//為了確保腳色攻擊變換方向時 特效不會換方向
		currentAni = ANI_SWORDWAVE_LEFT;
		this->x = hostX - 45;
		this->y = hostY;
	}
	else if (hostCurrentAni == ANI_ATTACK_RIGHT) { //為了確保腳色攻擊變換方向時 特效不會換方向
		currentAni = ANI_SWORDWAVE_RIGHT;
		this->x = hostX + 45;
		this->y = hostY ;
	}
}


/*void SwordWave::FlyAni(int waveX, int waveY, int) {

}*/


void SwordWave::LoadAni() {
	char* aniSwordWave_idle[1] = { ".\\res\\swordwave_left_0.bmp" };
	AddAniBitMaps(aniSwordWave_idle, ANI_SWORDWAVE_IDLE, 1);
	char* aniSwordWave_left[3] = { ".\\res\\swordwave_left_0.bmp", ".\\res\\swordwave_left_1.bmp", ".\\res\\swordwave_left_2.bmp" };
	AddAniBitMaps(aniSwordWave_left, ANI_SWORDWAVE_LEFT, 3);

	char* aniSwordWave_right[3] = { ".\\res\\swordwave_right_0.bmp", ".\\res\\swordwave_right_1.bmp",".\\res\\swordwave_right_2.bmp" };
	AddAniBitMaps(aniSwordWave_right, ANI_SWORDWAVE_RIGHT, 3);
}
