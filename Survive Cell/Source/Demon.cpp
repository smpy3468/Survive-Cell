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
	SetdX(); //左邊
	SetdY();	//右邊
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

	if (GetRL() == LEFT) {			//如果GetLR == LEFT 
		if (CanMoveLeft(moveSpeed)) {					//如果往左沒有卡住
			this->x = x - moveSpeed;					//X 往左移動
			if (CanMoveDown(moveSpeed)) {			    //往左會掉下去 
				this->x = x + moveSpeed;
				SetRL(RIGHT);//換往右
			}
			currentAni = ANI_LEFT;					    //設定現在動畫為LEFT
		}
		else                                            //如果往左遇到障礙物、地形卡住
		{
			SetRL(RIGHT);								//換往右
			status = RIGHT;
		}
	}
	else if (GetRL() == RIGHT) {	//如果GetLR == R ,
		if (CanMoveRight(moveSpeed)) {					//如果往右沒有卡住
			this->x = x + moveSpeed;					//X 往右移動
			if (CanMoveDown(moveSpeed)) {				//往右會掉下去 
				this->x = x - moveSpeed;
				SetRL(LEFT);							//換往左
			}
			currentAni = ANI_RIGHT;						//設定現在動畫為RIGHT
		}
		else                                            //如果往右遇到障礙物、地形卡住
		{
			SetRL(LEFT);								//換往左
			status = LEFT;
		}
	}

	if (x <= GetdX(0) && GetRL() != 0)       //GetdX[0]左邊警戒範圍，如果超過左邊 改右邊移動
		SetRL(RIGHT);

	else if (x >= GetdX(1) && GetRL() != 0) //GetdX[1]右邊警戒範圍，如果超過右邊 改左邊移動
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
	else if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player在怪物攻擊領域內 跟隨  #要增加跟隨感應距離改AttackField
		status = ATTACK;
		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 0, 0, 25, 5) == false) {	//如果怪物還沒撞到腳色

			if (placeRelativePlayer == RIGHT)		//如果怪物在人的右邊
			{
				if (!CanMoveLeft(moveSpeed))			//可以往左追
				{
					Monster::Up();			//怪物往上移(走道地形上)
				}

				x -= moveSpeed;
				currentAni = ANI_LEFT;
			}
			else if (placeRelativePlayer == LEFT)  //如果怪物在人的左邊
			{
				if (!CanMoveRight(moveSpeed))			//可以往右追
				{

					Monster::Up();		//怪物往上移(走道地形上)	
				}

				x += moveSpeed;
				currentAni = ANI_RIGHT;     //設定往右的動畫
			}
		}
		else {
			if (placeRelativePlayer == RIGHT) {	//如果怪物在人的右邊
				currentAni = ANI_ATTACK_LEFT;      //設定往左攻擊的動畫
			}
			else if (placeRelativePlayer == LEFT) {  //如果怪物在人的左邊
				currentAni = ANI_ATTACK_RIGHT;		//設定往右攻擊的動畫
			}
		}
	}
	else {												 //脫離警戒領域 回復來回走動
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
		if (placeRelativePlayer == RIGHT)				//決定被攻擊的動畫方向
		{
			status = ISATTACK;
			currentAni = ANI_ISATTACK_LEFT;
		}

		else if (placeRelativePlayer == LEFT)	    //決定被攻擊的動畫方向
		{
			status = ISATTACK;
			currentAni = ANI_ISATTACK_RIGHT;
		}
	}

	if (!ani[currentAni]->IsEnd()) {		//reset state;(GetCurrentBitmapNumber()要在ShowBitMap才會動)
		status = ISATTACK;
	}
	else
	{
		ani[ANI_ATTACK_RIGHT]->Reset();
		ani[ANI_ATTACK_LEFT]->Reset();
		status = STANDBY;
	}
}

void Demon::Act()											//組合各種動作(ISATTACK, AUTOMOVE, ATTACK)
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

	ani[currentAni]->OnMove();						//顯示動畫
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