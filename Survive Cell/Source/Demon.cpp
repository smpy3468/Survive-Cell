#include "StdAfx.h"
#include "Demon.h"


Demon::Demon() {
	tag = "Demon";
}

Demon::Demon(string tag, int x, int y, int width, int height, int pictureID):Monster(tag, x, y, width, height, pictureID) {
	tag = "Monster";
	SetDefenseRange(300);
	SetAttackField(125);
	SetdX(); //左邊
	SetdY();	//右邊
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
	if (GetRL() == LEFT && status == STANDBY ) {			//如果GetLR == LEFT 
		if (CanMoveLeft(moveSpeed)) {					//如果往左沒有卡住
			this->x = x - moveSpeed;					//X 往左移動
			currentAni = ANI_LEFT;					    //設定現在動畫為LEFT
		}
		else                                            //如果往左遇到障礙物、地形卡住
		{
			SetRL(RIGHT) ;								//換往右
		}	
	}
	else if (GetRL() == RIGHT && status == STANDBY) {	//如果GetLR == R ,
		if (CanMoveRight(moveSpeed)) {					//如果往右沒有卡住
			this->x = x + moveSpeed;					 //X 往右移動
			currentAni = ANI_RIGHT;						//設定現在動畫為RIGHT
		}
		else                                            //如果往右遇到障礙物、地形卡住
		{
			SetRL(LEFT);								//換往左
		}
			
	}

	ani[currentAni]->OnMove();						//顯示動畫

	if (x <= GetdX(0) && GetRL() != 0)       //GetdX[0]左邊警戒範圍，如果超過左邊 改右邊移動
		SetRL(RIGHT);

	else if (x >= GetdX(1) && GetRL() != 0) //GetdX[1]右邊警戒範圍，如果超過右邊 改左邊移動
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
	else if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player在怪物攻擊領域內 跟隨  #要增加跟隨感應距離改AttackField
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 0, 0, 0, 0) == false) {	//如果怪物還沒撞到腳色

			if (placeRelativePlayer == RIGHT) {		//如果怪物在人的右邊 
				x -= moveSpeed;
				//fire->SetXY(x, y);
				currentAni = ANI_LEFT;
			}
			else if (placeRelativePlayer == LEFT) {  //如果怪物在人的左邊
				x += moveSpeed;
				//fire->SetXY(x, y);
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
