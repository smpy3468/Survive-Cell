#include "StdAfx.h"
#include "Monster.h"
#include "Player.h"
#include "Item.h"
#include "Potion.h"

Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 300;
	attackField = 125;
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
	rl = 1;
	SetOriginAttackRange(10);
	HP = 10;
	SetAttackRange(GetOriginAttackRange());

	originMoveSpeed = 3;
	SetMoveSpeed(GetOriginMoveSpeed());

	//SetWidth(100);
	//SetHeight(100);
	LoadAni();
}

void Monster::SetDefenseRange(int defenseRange) {
	this->defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
}

void Monster::SetRL(int rl) {
	this->rl = rl;
}

int Monster::GetRL() {
	return rl;
}

int Monster::GetdX(int point) {
	if (point == 0)
		return dX[0];
	else
		return dX[1];
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //下
	this->dY[1] = y + defenseRange;	//上
}

void Monster::AutoMove() {
	if (rl == LEFT && status == STANDBY) {			//如果GetLR == 0 , X 往左移動
		this->x = x - moveSpeed;
		currentAni = ANI_LEFT;					    //設定現在動畫為LEFT
	}
	else if (rl == RIGHT && status == STANDBY) {
		this->x = x + moveSpeed;					//如果GetLR == 1 , X 往右移動
		currentAni = ANI_RIGHT;						//設定現在動畫為RIGHT
	}

	ani[currentAni]->OnMove();						//顯示動畫

	if (x <= dX[0] && rl != 0)       //GetdX[0]左邊警戒範圍，如果超過左邊 改右邊移動
		this->rl = RIGHT;

	else if (x >= dX[1] && rl != 0) //GetdX[1]右邊警戒範圍，如果超過右邊 改左邊移動
		this->rl = LEFT;
}

bool Monster::IsInAttackField(int playerX, int playerY, int right_fix, int left_fix, int up_fix, int down_fix) {
	int attackXField_Left = x - attackField - left_fix, attackXField_Right = x + attackField + right_fix;
	int attackYField_down = y + attackField + down_fix, attackYField_up = y - attackField - up_fix;

	if (playerX >= attackXField_Left && playerX <= attackXField_Right &&
		playerY >= attackYField_up && playerY <= attackYField_down)
		return true;

	return false;
}

bool Monster::IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix) {
	int RIGHT_EDGE = x + width / 2 + right_fix, LEFT_EDGE = x - width / 2 - left_fix,
		UP_EDGE = y - height / 2 - up_fix, DOWN_EDGE = y + height / 2 + down_fix;

	int OB_X = player->GetX(), OB_Y = player->GetY(), OB_WIDTH = player->GetWidth(), OB_HEIGHT = player->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH / 2, OB_LEFT_EDGE = OB_X - OB_WIDTH / 2,
		OB_UP_EDGE = OB_Y - OB_HEIGHT / 2, OB_DOWN_EDGE = OB_Y + OB_HEIGHT / 2;

	if (OB_RIGHT_EDGE >= LEFT_EDGE && PlaceRelativePlayer(player) == RIGHT)        //人在左, 怪物在右
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE && PlaceRelativePlayer(player) == LEFT)  //人在右, 怪物在左
		return true;
	/*else if (OB_DOWN_EDGE > UP_EDGE)       //人在下, 怪物在上
			return true;
	else if (OB_UP_EDGE < DOWN_EDGE)	   //人在上, 怪物在下
			return true;*/
	return false;
}

int  Monster::PlaceRelativePlayer(Player* player) {
	if (x >= player->GetX())
		return RIGHT;
	else
		return LEFT;
}

void Monster::Attack() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	const int ATTACK_SPEED = 4;

	if (IsInAttackField(player->GetX(), player->GetY(), 100, -20, 0, 0)) {  //Player在怪物攻擊領域內 跟隨  #要增加跟隨感應距離改AttackField
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsPlayerInRange(player, 50, -20, 0, 0) == false) {	//如果怪物還沒撞到腳色

			if (PlaceRelativePlayer(player) == RIGHT) {		//如果怪物在人的右邊 
				x -= moveSpeed;
				currentAni = ANI_LEFT;
			}
			else if (PlaceRelativePlayer(player) == LEFT) {  //如果怪物在人的左邊
				x += moveSpeed;
				currentAni = ANI_RIGHT;     //設定往右的動畫
			}
		}
		else {
			if (PlaceRelativePlayer(player) == RIGHT)	//如果怪物在人的右邊
				currentAni = ANI_LEFT;      //設定往左的動畫

			else if (PlaceRelativePlayer(player) == LEFT)  //如果怪物在人的左邊
				currentAni = ANI_RIGHT;     //設定往右的動畫
		}
	}
	else {												 //脫離警戒領域 回復來回走動
		if (PlaceRelativePlayer(player) == RIGHT)
			currentAni = ANI_RIGHT;
		else if (PlaceRelativePlayer(player) == LEFT)
			currentAni = ANI_LEFT;

		status = STANDBY;
		moveSpeed = originMoveSpeed;
	}	
}

void Monster::ShowBitMap()
{
	ani[currentAni]->OnShow();
}

void Monster::Dead()
{
	GameSystem::AddGameObject(new Potion("Potion", x, y + height, 20, 10, IDB_CELL_GREEN));//產生一個細胞道具

	GameSystem::DeleteGameObject(this);
}

void Monster::LoadAni()
{
	char* aniIdle[1] = { ".\\res\\demon_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI_IDLE, 1);

	char* aniLeft[6] = { ".\\res\\demon_left_0.bmp",".\\res\\demon_left_1.bmp" ,".\\res\\demon_left_2.bmp"
									,".\\res\\demon_left_3.bmp" ,".\\res\\demon_left_4.bmp" ,".\\res\\demon_left_5.bmp" };
	AddAniBitMaps(aniLeft, ANI_LEFT, 6);

	char* aniRight[6] = { ".\\res\\demon_right_0.bmp", ".\\res\\demon_right_1.bmp" ,".\\res\\demon_right_2.bmp" ,
									".\\res\\demon_right_3.bmp" ,".\\res\\demon_right_4.bmp" ,".\\res\\demon_right_5.bmp" };
	AddAniBitMaps(aniRight, ANI_RIGHT, 6);
}
