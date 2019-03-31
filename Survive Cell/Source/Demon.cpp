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
	attackDamage = 100;
	SetAttackRange(GetOriginAttackRange());
	originMoveSpeed = 3;
	SetMoveSpeed(GetOriginMoveSpeed());

	aniSpeed = 5;
	LoadAni();
	fire = new Fire("Fire", x, y, 110, 75, IDB_0);
}

//-------------------------------------------------------------------------------------------------

void Demon::AutoMove() {
	if (GetRL() == LEFT && status == STANDBY ) {			//�p�GGetLR == LEFT 
		if (CanMoveLeft(moveSpeed)) {					//�p�G�����S���d��
			this->x = x - moveSpeed;					//X ��������
			currentAni = ANI_LEFT;					    //�]�w�{�b�ʵe��LEFT
		}
		else                                            //�p�G�����J���ê���B�a�Υd��
		{
			SetRL(RIGHT) ;								//�����k
		}	
	}
	else if (GetRL() == RIGHT && status == STANDBY) {	//�p�GGetLR == R ,
		if (CanMoveRight(moveSpeed)) {					//�p�G���k�S���d��
			this->x = x + moveSpeed;					 //X ���k����
			currentAni = ANI_RIGHT;						//�]�w�{�b�ʵe��RIGHT
		}
		else                                            //�p�G���k�J���ê���B�a�Υd��
		{
			SetRL(LEFT);								//������
		}
			
	}

	ani[currentAni]->OnMove();						//��ܰʵe

	if (x <= GetdX(0) && GetRL() != 0)       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		SetRL(RIGHT);

	else if (x >= GetdX(1) && GetRL() != 0) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		SetRL(LEFT);
}



void Demon::Attack() {
	const int ATTACK_SPEED = 4;
	int placeRelativePlayer = PlaceRelativePlayer(player);

	if (ani[ANI_ATTACK_RIGHT]->GetCurrentBitmapNumber() != 0) {
		currentAni = ANI_ATTACK_RIGHT;
	}
	else if (ani[ANI_ATTACK_LEFT]->GetCurrentBitmapNumber() != 0) {
		currentAni = ANI_ATTACK_LEFT;
	}
	else if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player�b�Ǫ�������줺 ���H  #�n�W�[���H�P���Z����AttackField
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 0, 0, 0, 0) == false) {	//�p�G�Ǫ��٨S����}��

			if (placeRelativePlayer == RIGHT) {		//�p�G�Ǫ��b�H���k�� 
				x -= moveSpeed;
				//fire->SetXY(x, y);
				currentAni = ANI_LEFT;
			}
			else if (placeRelativePlayer == LEFT) {  //�p�G�Ǫ��b�H������
				x += moveSpeed;
				//fire->SetXY(x, y);
				currentAni = ANI_RIGHT;     //�]�w���k���ʵe
			}
		}
		else {
			if (placeRelativePlayer == RIGHT) {	//�p�G�Ǫ��b�H���k��
				currentAni = ANI_ATTACK_LEFT;      //�]�w�����������ʵe
			}
			else if (placeRelativePlayer == LEFT) {  //�p�G�Ǫ��b�H������
				currentAni = ANI_ATTACK_RIGHT;		//�]�w���k�������ʵe
			}
		}
	}
	else {												 //����ĵ�ٻ�� �^�_�Ӧ^����
		if (placeRelativePlayer == RIGHT)
			currentAni = ANI_RIGHT;
		else if (placeRelativePlayer == LEFT)
			currentAni = ANI_LEFT;

		status = STANDBY;
		moveSpeed = originMoveSpeed;
	}
}


void Demon::ShowBitMap(){
 	fire->SetXY(x, y, currentAni);
	currentBitMapNumber = ani[currentAni]->GetCurrentBitmapNumber();
	fire->ShowBitMap(ani[currentAni]->GetCurrentBitmapNumber(), currentAni);
	ani[currentAni]->OnShow();
}

//-------------------------------------------------------------------------------------------------

void Demon::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\demon_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1, aniSpeed);

	char* aniLeft[6] = { ".\\res\\demon_left_0.bmp",".\\res\\demon_left_1.bmp" ,".\\res\\demon_left_2.bmp"
									,".\\res\\demon_left_3.bmp" ,".\\res\\demon_left_4.bmp" ,".\\res\\demon_left_5.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 6, aniSpeed);

	char* aniRight[6] = { ".\\res\\demon_right_0.bmp", ".\\res\\demon_right_1.bmp" ,".\\res\\demon_right_2.bmp" ,
									".\\res\\demon_right_3.bmp" ,".\\res\\demon_right_4.bmp" ,".\\res\\demon_right_5.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 6, aniSpeed);

	char* aniAttack_left[11] = { ".\\res\\demon_attackleft_0.bmp", ".\\res\\demon_attackleft_1.bmp", ".\\res\\demon_attackleft_2.bmp",
								".\\res\\demon_attackleft_3.bmp", ".\\res\\demon_attackleft_4.bmp", ".\\res\\demon_attackleft_5.bmp",
								".\\res\\demon_attackleft_6.bmp", ".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp",
								".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp" };
	AddAniBitMaps(aniAttack_left, ANI_ATTACK_LEFT, 11, aniSpeed);

	char* aniAttack_right[11] = { ".\\res\\demon_attackright_0.bmp", ".\\res\\demon_attackright_1.bmp", ".\\res\\demon_attackright_2.bmp",
							".\\res\\demon_attackright_3.bmp", ".\\res\\demon_attackright_4.bmp", ".\\res\\demon_attackright_5.bmp",
							".\\res\\demon_attackright_6.bmp", ".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp",
							".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp" };
	AddAniBitMaps(aniAttack_right, ANI_ATTACK_RIGHT, 11, aniSpeed);
}
