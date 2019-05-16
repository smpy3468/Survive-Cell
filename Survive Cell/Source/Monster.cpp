#pragma once
#include "StdAfx.h"
#include <ctime>
#include "Monster.h"
#include "Player.h"
#include "Item.h"
#include "Potion.h"
#include "ItemTraditionalSword.h"

Monster::Monster()
{
	tag = "Monster";
}

Monster::~Monster()
{
}


Monster::Monster(string tag, int x, int y, int width, int height) :Character(tag, x, y, width, height)
{
	tag = "Monster";
	rl = LEFT;
	layer = GameSystem::LAYER::LAYER_MONSTER;
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

void Monster::Move(int dx, int dy){ 
	this->x += dx;
	this->y += dy;
}

void Monster::Fall(int perDisplacement)
{
	if (CanMoveDown(fallDisplacement))//如果腳下沒東西
	{

		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//再繼續用下降位移量下降，將會卡進地板，所以一次向下位移1進行微調0
			Move(0, 1);
		fallDisplacement = 0;
		dX[0] = x - defenseRange;
		dX[1] = x + defenseRange;

	}
}

void Monster::Up() 
{
	while (Map::HasObject(x + width, y + height)) {
		y-=1;
	}
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
	int RIGHT_EDGE = x + width + right_fix, LEFT_EDGE = x - left_fix,
		UP_EDGE = y - up_fix, DOWN_EDGE = y + height + down_fix;

	int OB_X = player->GetX(), OB_Y = player->GetY(), OB_WIDTH = player->GetWidth(), OB_HEIGHT = player->GetHeight();

	int OB_RIGHT_EDGE = OB_X + OB_WIDTH , OB_LEFT_EDGE = OB_X,
		OB_UP_EDGE = OB_Y, OB_DOWN_EDGE = OB_Y + OB_HEIGHT;

	if (OB_RIGHT_EDGE >= LEFT_EDGE - attackRange && PlaceRelativePlayer(player) == RIGHT && OB_UP_EDGE> UP_EDGE && OB_UP_EDGE<DOWN_EDGE)        //人在左, 怪物在右
		return true;
	else if (OB_LEFT_EDGE <= RIGHT_EDGE +attackRange && PlaceRelativePlayer(player) == LEFT && OB_UP_EDGE> UP_EDGE && OB_UP_EDGE<DOWN_EDGE)  //人在右, 怪物在左
		return true;
	return false;
}

int  Monster::PlaceRelativePlayer(Player* player) {
	if (x >= player->GetX())
		return RIGHT;
	else
		return LEFT;
}


void Monster::PlayerAttack(int damage)
{
	DecreaseHP(damage);
	status = ISATTACK;
}


void Monster::ShowBitMap()
{	
	ani[currentAni]->OnMove();
	ani[currentAni]->OnShow(); 
}

void Monster::Dead()
{	
	int i = static_cast<int>(GameSystem::Rand(4));
	if(i>2)
		GameSystem::AddGameObject(new Potion("Potion", x  , y, 20, 10));//產生一個細胞道具
	else
		GameSystem::AddGameObject(new ItemTraditionalSword("ItemWeapon", x + width / 2, y, 32, 32,10,0));

	GameSystem::DeleteGameObject(this);
}

int Monster::GetAttackAniNumber() {
	if(currentAni == ANI::ANI_ATTACK_LEFT || currentAni ==ANI::ANI_ATTACK_RIGHT)
		return ani[currentAni]->GetCurrentBitmapNumber();
	return 0;
}

void Monster::Attack() {}
void Monster::Act(){}