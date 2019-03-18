#include "StdAfx.h"
#include "Character.h"

Character::Character():GameObject()
{
	tag = "Character";
}

Character::Character(string tag, int x, int y, int width, int height, int pictureID):GameObject(tag, x, y, width, height, pictureID)
{
	tag = "Character";
	originMoveSpeed = 3;
	SetMoveSpeed(GetOriginMoveSpeed());
}

void Character::SetMaxHP(int maxHp)
{
	this->maxHP = maxHp;
}

void Character::SetHP(int hp)
{
	this->HP = hp;
}

void Character::SetOriginMoveSpeed(int originMoveSpeed)
{
	this->originMoveSpeed = originMoveSpeed;
}

void Character::SetMoveSpeed(int moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Character::SetOriginAttack(int originAttack)
{
	this->originAttack = originAttack;
}

void Character::SetAttack(int attack)
{
	this->attack = attack;
}

void Character::SetOriginAttackSpeed(int originAttackSpeed)
{
	this->originAttackSpeed = originAttackSpeed;
}

void Character::SetAttackSpeed(int attackSpeed)
{
	this->attackSpeed = attackSpeed;
}

void Character::SetOriginAttackRange(int originAttackRange)
{
	this->originAttackRange = originAttackRange;
}

void Character::SetAttackRange(int attackRange)
{
	this->attackRange = attackRange;
}

void Character::SetIsDead(bool isDead)
{
	this->isDead = isDead;
}

int Character::GetMaxHP()
{
	return this->maxHP;
}

int Character::GetHP()
{
	return this->HP;
}

int Character::GetOriginMoveSpeed()
{
	return this->originMoveSpeed;
}

int Character::GetMoveSpeed()
{
	return this->moveSpeed;
}

int Character::GetOriginAttack()
{
	return this->originAttack;
}

int Character::GetAttack()
{
	return this->attack;
}

int Character::GetOriginAttackRange()
{
	return this->originAttackRange;
}

int Character::GetAttackRange()
{
	return this->attackRange;
}

bool Character::IsDead()
{
	return this->isDead;
}

void Character::DecreaseHP(int dhp)
{
	this->HP -= dhp;
	if (this->HP <= 0)//¦º¤`
	{
		HP = 0;
		isDead = true;

	}
}
