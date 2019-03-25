#include "StdAfx.h"
#include "Monster.h"
#include "Player.h"
#include "Item.h"

Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 300;
	attackField = 50;
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
	rl = 1;
	SetOriginAttackRange(10);
	HP = 10;
	SetAttackRange(GetOriginAttackRange());

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

bool Monster::IsInAttackField(int playerX, int playerY) {
	int attackXField_Left = x - attackField, attackXField_Right = x + attackField;
	int attackYField_down = y + attackField, attackYField_up = y - attackField;

	if (playerX >= attackXField_Left && playerX <= attackXField_Right &&
		playerY >= attackYField_up && playerY <= attackYField_down)
		return true;

	return false;
}

void Monster::Attack() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	const int ATTACK_SPEED = 4;

	if (IsInAttackField(player->GetX(), player->GetY())) {  //怪物衝過去攻擊主角
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if (IsAnthorObjectInRange(player) == false) {	//如果怪物還沒撞到腳色
			if (x > player->GetX()) {		//如果怪物在人的右邊
				x -= moveSpeed;
				currentAni = ANI_LEFT;      //設定往左的動畫
			}
			else if (x < player->GetX()) {  //如果怪物在人的左邊
				x += moveSpeed;
				currentAni = ANI_RIGHT;     //設定往右的動畫
			}
		}
		else {
			currentAni = ANI_IDLE;  //待在原地
		}
	}
	else {
		status = STANDBY;
		moveSpeed = originMoveSpeed;
		currentAni = ANI_IDLE;  //待在原地
	}
}

void Monster::ShowBitMap()
{
	ani[currentAni]->OnShow();
}

void Monster::Dead()
{
	GameSystem::AddGameObject(new Item("Item", x + width / 2, y + height, 20, 10, IDB_CELL_GREEN));//產生一個細胞道具

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
