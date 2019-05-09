#include"StdAfx.h"
#include"SwordWave.h"

SwordWave::SwordWave(string tag, int x, int y, int width, int height) :Effect(tag, x, y, width, height) {
	tag = "SwordWave";
	LoadAni();
	SetBitMapPosition(); 
	currentAni = ANI_SWORDWAVE_IDLE;
	LoadBitMap(".\\res\\swordwave_left_0.bmp");
}

SwordWave::~SwordWave()
{
}

void SwordWave::ShowBitMap(int hostX, int hostY, int hostCurrentAni, int attackAniNumber) {
	if(attackAniNumber == 0&&(hostCurrentAni== ANI_ATTACK_LEFT || hostCurrentAni == ANI_ATTACK_RIGHT)){
		SetXY(hostX, hostY, hostCurrentAni);
	}
	else if (attackAniNumber >= 1 && currentAni == ANI_SWORDWAVE_LEFT && CanMoveLeft(5) && isHit == 0) { //3�O���������A
		x -= 25;																//��Wave������
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		EffectAttackMonster(player->GetAttackDamage());
	} 
	else if (attackAniNumber >= 1 && currentAni == ANI_SWORDWAVE_RIGHT && CanMoveRight(5) && isHit == 0) {       //4�O�k�������A
		x += 25;																//��Wave���k��
		SetBitMapPosition();
		ani[currentAni]->OnMove();
		ani[currentAni]->OnShow();
		EffectAttackMonster(player->GetAttackDamage());

	}
	else {
		isHit = 0;
		currentAni = ANI_SWORDWAVE_IDLE;
	}
}

void SwordWave::SetXY(int hostX, int hostY, int hostCurrentAni) {
	if (hostCurrentAni == ANI_ATTACK_LEFT) {//���F�T�O�}������ܴ���V�� �S�Ĥ��|����V
		currentAni = ANI_SWORDWAVE_LEFT;
		this->x = hostX - 45;
		this->y = hostY;
	}
	else if (hostCurrentAni == ANI_ATTACK_RIGHT) { //���F�T�O�}������ܴ���V�� �S�Ĥ��|����V
		currentAni = ANI_SWORDWAVE_RIGHT;
		this->x = hostX + 45;
		this->y = hostY ;
	}
}



void SwordWave::LoadAni() {
	char* aniSwordWave_idle[1] = { ".\\res\\swordwave_left_0.bmp" };
	AddAniBitMaps(aniSwordWave_idle, ANI_SWORDWAVE_IDLE, 1);

	char* aniSwordWave_left[3] = { ".\\res\\swordwave_left_0.bmp", ".\\res\\swordwave_left_1.bmp", ".\\res\\swordwave_left_2.bmp" };
	AddAniBitMaps(aniSwordWave_left, ANI_SWORDWAVE_LEFT, 3);

	char* aniSwordWave_right[3] = { ".\\res\\swordwave_right_0.bmp", ".\\res\\swordwave_right_1.bmp",".\\res\\swordwave_right_2.bmp" };
	AddAniBitMaps(aniSwordWave_right, ANI_SWORDWAVE_RIGHT, 3);
}
