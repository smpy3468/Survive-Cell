#include "StdAfx.h"
#include "Demon.h"

Demon::Demon() {
	tag = "Monster";
}

Demon::~Demon()
{
	delete fire;
}

Demon::Demon(string tag, int x, int y, int width, int height) :Monster(tag, x, y, width, height) {
	tag = "Monster";
	SetDefenseRange(300);
	SetAttackField(125);
	SetdX(); //����
	SetdY();	//�k��
	SetOriginAttackRange(10);

	maxHP = 50;
	HP = maxHP;
	attackDamage = 1;
	SetAttackRange(GetOriginAttackRange());
	originMoveSpeed = 3;
	SetMoveSpeed(GetOriginMoveSpeed());
	SetDefense(0);

	status = STANDBY;
	aniDelay = 5;
	LoadAni();
	LoadBitMap(".\\res\\demon_idle.bmp");
	fire = new Fire("Fire", x, y, 154, 105);
}

void Demon::AutoMove() {

	if (GetRL() == LEFT) {			//�p�GGetLR == LEFT 
		if (CanMoveLeft(moveSpeed)) {					//�p�G�����S���d��
			this->x = x - moveSpeed;					//X ��������
			if (CanMoveDown(moveSpeed)) {			    //�����|���U�h 
				this->x = x + moveSpeed;
				SetRL(RIGHT);//�����k
			}
			currentAni = ANI_LEFT;					    //�]�w�{�b�ʵe��LEFT
		}
		else                                            //�p�G�����J���ê���B�a�Υd��
		{
			SetRL(RIGHT);								//�����k
			status = RIGHT;
		}
	}
	else if (GetRL() == RIGHT) {	//�p�GGetLR == R ,
		if (CanMoveRight(moveSpeed)) {					//�p�G���k�S���d��
			this->x = x + moveSpeed;					//X ���k����
			if (CanMoveDown(moveSpeed)) {				//���k�|���U�h 
				this->x = x - moveSpeed;
				SetRL(LEFT);							//������
			}
			currentAni = ANI_RIGHT;						//�]�w�{�b�ʵe��RIGHT
		}
		else                                            //�p�G���k�J���ê���B�a�Υd��
		{
			SetRL(LEFT);								//������
			status = LEFT;
		}
	}

	if (x <= GetdX(0) && GetRL() != 0)       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		SetRL(RIGHT);

	else if (x >= GetdX(1) && GetRL() != 0) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		SetRL(LEFT);
}

void Demon::Attack() {
	const int ATTACK_SPEED = 4;
	int placeRelativePlayer = PlaceRelativePlayer(player);

	if (ani[ANI_ATTACK_RIGHT]->GetCurrentBitmapNumber() != 0) {
		status = ATTACK;
		currentAni = ANI_ATTACK_RIGHT;
	}
	else if (ani[ANI_ATTACK_LEFT]->GetCurrentBitmapNumber() != 0) {
		status = ATTACK;
		currentAni = ANI_ATTACK_LEFT;
	}
	else if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player�b�Ǫ�������줺 ���H  #�n�W�[���H�P���Z����AttackField
		status = ATTACK;
		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 0, 0, 25, 5) == false) {	//�p�G�Ǫ��٨S����}��

			if (placeRelativePlayer == RIGHT)		//�p�G�Ǫ��b�H���k��
			{
				if (!CanMoveLeft(moveSpeed))			//�i�H�����l
				{
					Monster::Up();			//�Ǫ����W��(���D�a�ΤW)
				}

				x -= moveSpeed;
				currentAni = ANI_LEFT;
			}
			else if (placeRelativePlayer == LEFT)  //�p�G�Ǫ��b�H������
			{
				if (!CanMoveRight(moveSpeed))			//�i�H���k�l
				{

					Monster::Up();		//�Ǫ����W��(���D�a�ΤW)	
				}

				x += moveSpeed;
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

void Demon::IsAttack()
{
	int placeRelativePlayer = PlaceRelativePlayer(player);

	if (currentAni != ANI_ISATTACK_LEFT && currentAni != ANI_ATTACK_RIGHT)
	{
		if (placeRelativePlayer == RIGHT)				//�M�w�Q�������ʵe��V
		{
			status = ISATTACK;
			currentAni = ANI_ISATTACK_LEFT;
		}

		else if (placeRelativePlayer == LEFT)	    //�M�w�Q�������ʵe��V
		{
			status = ISATTACK;
			currentAni = ANI_ISATTACK_RIGHT;
		}
	}

	if (!ani[currentAni]->IsEnd()) {		//reset state;(GetCurrentBitmapNumber()�n�bShowBitMap�~�|��)
		status = ISATTACK;
	}
	else
	{
		ani[ANI_ATTACK_RIGHT]->Reset();
		ani[ANI_ATTACK_LEFT]->Reset();
		status = STANDBY;
	}
}

void Demon::Act()											//�զX�U�ذʧ@(ISATTACK, AUTOMOVE, ATTACK)
{
	Fall(moveSpeed);

	if (status == ISATTACK) {
		IsAttack();
	}
	if (status != ISATTACK) {
		Attack();
	}

	if (status == STANDBY || status == LEFT || status == RIGHT) {
		AutoMove();
	}

	ani[currentAni]->OnMove();						//��ܰʵe
}

void Demon::ShowBitMap() {
	currentBitMapNumber = ani[currentAni]->GetCurrentBitmapNumber();
	fire->ShowBitMap(x, y, currentAni, ani[currentAni]->GetCurrentBitmapNumber());
	ani[currentAni]->OnShow();

}

void Demon::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\demon_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1, aniDelay);

	char* aniLeft[6] = { ".\\res\\demon_left_0.bmp",".\\res\\demon_left_1.bmp" ,".\\res\\demon_left_2.bmp"
									,".\\res\\demon_left_3.bmp" ,".\\res\\demon_left_4.bmp" ,".\\res\\demon_left_5.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 6, aniDelay);

	char* aniRight[6] = { ".\\res\\demon_right_0.bmp", ".\\res\\demon_right_1.bmp" ,".\\res\\demon_right_2.bmp" ,
									".\\res\\demon_right_3.bmp" ,".\\res\\demon_right_4.bmp" ,".\\res\\demon_right_5.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 6, aniDelay);

	char* aniAttack_left[11] = { ".\\res\\demon_attackleft_0.bmp", ".\\res\\demon_attackleft_1.bmp", ".\\res\\demon_attackleft_2.bmp",
								".\\res\\demon_attackleft_3.bmp", ".\\res\\demon_attackleft_4.bmp", ".\\res\\demon_attackleft_5.bmp",
								".\\res\\demon_attackleft_6.bmp", ".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp",
								".\\res\\demon_attackleft_7.bmp", ".\\res\\demon_attackleft_7.bmp" };
	AddAniBitMaps(aniAttack_left, ANI_ATTACK_LEFT, 11, aniDelay);

	char* aniAttack_right[11] = { ".\\res\\demon_attackright_0.bmp", ".\\res\\demon_attackright_1.bmp", ".\\res\\demon_attackright_2.bmp",
							".\\res\\demon_attackright_3.bmp", ".\\res\\demon_attackright_4.bmp", ".\\res\\demon_attackright_5.bmp",
							".\\res\\demon_attackright_6.bmp", ".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp",
							".\\res\\demon_attackright_7.bmp", ".\\res\\demon_attackright_7.bmp" };
	AddAniBitMaps(aniAttack_right, ANI_ATTACK_RIGHT, 11, aniDelay);

	char* aniIsAttack_right[7] = { ".\\res\\isattack_right_0.bmp", ".\\res\\isattack_right_1.bmp", ".\\res\\isattack_right_2.bmp",".\\res\\isattack_right_2.bmp",
									".\\res\\isattack_right_2.bmp",".\\res\\isattack_right_2.bmp",".\\res\\isattack_right_2.bmp" };
	AddAniBitMaps(aniIsAttack_right, ANI_ISATTACK_RIGHT, 7, aniDelay);

	char* aniIsAttack_left[7] = { ".\\res\\isattack_left_0.bmp", ".\\res\\isattack_left_1.bmp", ".\\res\\isattack_left_2.bmp",
								".\\res\\isattack_left_2.bmp", ".\\res\\isattack_left_2.bmp",".\\res\\isattack_left_2.bmp",".\\res\\isattack_left_2.bmp "};
	AddAniBitMaps(aniIsAttack_left, ANI_ISATTACK_LEFT, 7, aniDelay);
}