#include "StdAfx.h"
#include "Demon.h"


Demon::Demon() {
	tag = "Demon";

}

Demon::Demon(string tag, int x, int y, int width, int height, int pictureID):Monster(tag, x, y, width, height, pictureID) {
	tag = "Monster";
	SetDefenseRange(300);
	SetAttackField(125);
	SetdX(); //����
	SetdY();	//�k��
	SetOriginAttackRange(10);

	HP = 10;
	SetAttackRange(GetOriginAttackRange());
	originMoveSpeed = 3;
	SetMoveSpeed(GetOriginMoveSpeed());

	//SetWidth(100);
	//SetHeight(100);
	LoadAni();
}
void Demon::AutoMove() {
	if (GetRL() == LEFT && status == STANDBY) {			//�p�GGetLR == 0 , X ��������
		this->x = x - moveSpeed;
		currentAni = ANI_LEFT;					    //�]�w�{�b�ʵe��LEFT
	}
	else if (GetRL() == RIGHT && status == STANDBY) {
		this->x = x + moveSpeed;					//�p�GGetLR == 1 , X ���k����
		currentAni = ANI_RIGHT;						//�]�w�{�b�ʵe��RIGHT
	}

	ani[currentAni]->OnMove();						//��ܰʵe

	if (x <= GetdX(0) && GetRL() != 0)       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		SetRL(RIGHT);

	else if (x >= GetdX(1) && GetRL() != 0) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		SetRL(LEFT);
}



void Demon::Attack() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	const int ATTACK_SPEED = 4;
	if (ani[ANI_ATTACK_RIGHT]->GetCurrentBitmapNumber() != 0) {
		currentAni = ANI_ATTACK_RIGHT;
	}
	else if (ani[ANI_ATTACK_LEFT]->GetCurrentBitmapNumber() != 0) {
		currentAni = ANI_ATTACK_LEFT;
	}
	else if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player�b�Ǫ�������줺 ���H  #�n�W�[���H�P���Z����AttackField
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 50, -20, 0, 0) == false) {	//�p�G�Ǫ��٨S����}��

			if (PlaceRelativePlayer(player) == RIGHT) {		//�p�G�Ǫ��b�H���k�� 
				x -= moveSpeed;
				currentAni = ANI_LEFT;
			}
			else if (PlaceRelativePlayer(player) == LEFT) {  //�p�G�Ǫ��b�H������
				x += moveSpeed;
				currentAni = ANI_RIGHT;     //�]�w���k���ʵe
			}
		}
		else {
			if (PlaceRelativePlayer(player) == RIGHT) {	//�p�G�Ǫ��b�H���k��
				currentAni = ANI_ATTACK_LEFT;      //�]�w�����������ʵe
			}
			else if (PlaceRelativePlayer(player) == LEFT) {  //�p�G�Ǫ��b�H������
				currentAni = ANI_ATTACK_RIGHT;		//�]�w���k�������ʵe
			}
		}
	}
	else {												 //����ĵ�ٻ�� �^�_�Ӧ^����
		if (PlaceRelativePlayer(player) == RIGHT)
			currentAni = ANI_RIGHT;
		else if (PlaceRelativePlayer(player) == LEFT)
			currentAni = ANI_LEFT;

		status = STANDBY;
		moveSpeed = originMoveSpeed;
	}
}



void Demon::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\demon_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);

	char* aniLeft[6] = { ".\\res\\demon_left_0.bmp",".\\res\\demon_left_1.bmp" ,".\\res\\demon_left_2.bmp"
									,".\\res\\demon_left_3.bmp" ,".\\res\\demon_left_4.bmp" ,".\\res\\demon_left_5.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 6);

	char* aniRight[6] = { ".\\res\\demon_right_0.bmp", ".\\res\\demon_right_1.bmp" ,".\\res\\demon_right_2.bmp" ,
									".\\res\\demon_right_3.bmp" ,".\\res\\demon_right_4.bmp" ,".\\res\\demon_right_5.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 6);

	char* aniAttack_left[11] = { ".\\res\\demon_attackleft_0.bmp", ".\\res\\demon_attackleft_1.bmp", ".\\res\\demon_attackleft_2.bmp",
								".\\res\\demon_attackleft_3.bmp", ".\\res\\demon_attackleft_4.bmp", ".\\res\\demon_attackleft_5.bmp",
								".\\res\\demon_attackleft_6.bmp", ".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp",
								".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp" };
	AddAniBitMaps(aniAttack_left, ANI_ATTACK_LEFT, 11);

	char* aniAttack_right[11] = { ".\\res\\demon_attackright_0.bmp", ".\\res\\demon_attackright_1.bmp", ".\\res\\demon_attackright_2.bmp",
							".\\res\\demon_attackright_3.bmp", ".\\res\\demon_attackright_4.bmp", ".\\res\\demon_attackright_5.bmp",
							".\\res\\demon_attackright_6.bmp", ".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp",
							".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp" };
	AddAniBitMaps(aniAttack_right, ANI_ATTACK_RIGHT, 11);
}
