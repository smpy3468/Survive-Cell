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
	rl = 1;

}

void Monster::SetDefenseRange(int defenseRange) {
	this->defenseRange = defenseRange;
}

void Monster::SetRL(int rl) {
	this->rl = rl;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //左邊
	dX[1] = x + defenseRange;	//右邊
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //下
	this->dY[1] = y + defenseRange;	//上
}

void Monster::SetAttackField(int attackField){
	this->attackField = attackField;
}

void Monster::SetAttackRange(int attackRange) {
	this->attackRange = attackRange;
}

//-----------------------------------GET------------------------------------------------//
int Monster::GetDefenseRange() {
	return defenseRange;
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



int Monster::GetStatus() {
	return status;
}

//--------------------------OTHER FUNCTION-----------------------------------//
void Monster::AutoMove() {}

void Monster::Move(int dx, int dy)
{
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

	if (OB_RIGHT_EDGE >= LEFT_EDGE - attackRange && PlaceRelativePlayer(player) == RIGHT)        //人在左, 怪物在右
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE +attackRange && PlaceRelativePlayer(player) == LEFT)  //人在右, 怪物在左
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

void Monster::Attack() {}



void Monster::ShowBitMap()
{	
	ani[currentAni]->OnMove();
	ani[currentAni]->OnShow(); 
}

void Monster::Dead()
{
	GameSystem::AddGameObject(new Potion("Potion", x, y + height, 20, 10, IDB_CELL_GREEN));//產生一個細胞道具

	GameSystem::DeleteGameObject(this);
}

int Monster::GetAttackAniNumber() {
	if(currentAni == ANI_ATTACK_LEFT || currentAni ==ANI_ATTACK_RIGHT)
		return ani[currentAni]->GetCurrentBitmapNumber();
	return 0;
}

