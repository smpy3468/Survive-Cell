#include "StdAfx.h"
#include "Character.h"
#include "GameSystem.h"
#include "Item.h"

Character::Character() :GameObject()
{
	tag = "Character";
}

Character::Character(string tag, int x, int y, int width, int height, int pictureID) : GameObject(tag, x, y, width, height, pictureID)
{
	tag = "Character";
	isGetHit = false;
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

void Character::SetOriginAttackDamage(int originAttack)
{
	this->originAttackDamage = originAttack;
}

void Character::SetAttackDamage(int attack)
{
	this->attackDamage = attack;
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

void Character::SetDefense(int defense){
	this->defense = defense;
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

int Character::GetOriginAttackDamage()
{
	return this->originAttackDamage;
}

int Character::GetAttackDamage()
{
	return this->attackDamage;
}

int Character::GetOriginAttackSpeed()
{
	return originAttackSpeed;
}

int Character::GetAttackSpeed()
{
	return attackSpeed;
}

int Character::GetOriginAttackRange()
{
	return this->originAttackRange;
}

int Character::GetAttackRange()
{
	return this->attackRange;
}

int Character::GetDefense()
{
	return this->defense;
}

bool Character::IsDead()
{
	return this->isDead;
}

void Character::SetBitMapPosition()
{
	for (auto& i : ani)
	{
		i->SetTopLeft(this->x - Map::GetSX(), this->y - Map::GetSY());
	}
}

void Character::DecreaseHP(int dhp)
{
	isGetHit = true;

	this->HP -= dhp;
	if (this->HP <= 0)//���`
	{
		HP = 0;
		isDead = true;

		Dead();
	}
}

void Character::IncreaseHP(int ihp)
{
	this->HP += ihp;
	if (this->HP > this->maxHP)//�W�L�̤j��q
		this->HP = this->maxHP;		
}

void Character::Dead()
{
	GameSystem::DeleteGameObject(this);//�R��������
}

void Character::LoadAni()
{
}

void Character::AddAniBitMaps(char * pic[], int aniType, int picCount, int aniSpeed)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType, aniSpeed);
	}
}

void Character::AddAniBitMap(char* pic, int aniType, int aniSpeed)
{
	while ((int)ani.size() <= aniType)//vector���j�p�����j
		ani.push_back(new CAnimation(aniSpeed));//�W�[�j�p

	ani[aniType]->SetDelayCount(aniSpeed);//�]�w�ʵe�t��

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

bool Character::CanMoveLeft(int perDisplacement)
{
	bool canMoveLeft = true;
	for (int i = y; i < y + height; i++)
	{
		if (Map::HasObject(this->x - perDisplacement, i))//���b�䦳�F��
		{
			canMoveLeft = false;
			return canMoveLeft;
		}
	}
	return canMoveLeft;
}

bool Character::CanMoveRight(int perDisplacement)
{
	bool canMoveRight = true;
	for (int i = y; i < y + height; i++)
	{
		if (Map::HasObject(this->x + this->width + perDisplacement, i))//�k�b�䦳�F��
		{
			canMoveRight = false;
			return canMoveRight;
		}
	}
	return canMoveRight;
}

bool Character::CanMoveUp(int perDisplacement)
{
	bool canMoveUp = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y - perDisplacement) || y < 0)//�W�����F��
		{
			canMoveUp = false;
			return canMoveUp;
		}
	}
	return canMoveUp;
}

bool Character::CanMoveDown(int perDisplacement)
{
	bool canMoveDown = true;
	for (int i = x; i < x + width; i++)
	{
		if (Map::HasObject(i, y + height + perDisplacement))//�U�����F��
		{
			canMoveDown = false;
			return canMoveDown;
		}
	}
	return canMoveDown;
}