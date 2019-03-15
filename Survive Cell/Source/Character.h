#pragma once

//Character
//����
//�~��GameObject

#include <vector>
#include "GameObject.h"
#include "Buff.h"

class Character :public GameObject
{
public:
	Character();
	Character::Character(string tag, int x, int y, int width, int height, int pictureID);
	void SetMaxHP(int maxHp);//�]�w�̤j��q
	void SetHP(int hp);//�]�w�ثe��q
	void SetOriginMoveSpeed(int originMoveSpeed);//�]�w��l���ʳt��
	void SetMoveSpeed(int moveSpeed);//�]�w�ثe���ʳt��
	void SetOriginAttack(int originAttack);//�]�w��l�����O
	void SetAttack(int attack);//�]�w�ثe�����O
	void SetOriginAttackSpeed(int originAttackSpeed);//�]�w��l�����t��
	void SetAttackSpeed(int attackSpeed);//�]�w�ثe�����t��
	void SetOriginAttackRange(int originAttackRange);//�]�w��l�����d��
	void SetAttackRange(int attackRange);//�]�w�ثe�����d��
	void SetIsDead(bool isDead);//�]�w�O�_���`

	int GetMaxHP();//���o�̤j��q
	int GetHP();//���o�ثe��q
	int GetOriginMoveSpeed();//���o��l���ʳt��
	int GetMoveSpeed();//���o�ثe���ʳt��
	int GetOriginAttack();//���o��l�����O
	int GetAttack();//���o�ثe�����O
	int GetOriginAttackRange();//���o��l�����d��
	int GetAttackRange();//���o�����d��
	bool IsDead();//�T�{�O�_���`

	virtual void Move(int dx, int dy) = 0;

protected:
	int maxHP, HP;//�̤j��q�B�ثe��q
	int originMoveSpeed, moveSpeed;//��l���ʳt�סB�ثe���ʳt��
	int originAttack, attack;//��l�����O�B�ثe�����O
	int	originAttackSpeed, attackSpeed;//��l�����t�סB�ثe�����t��
	int originAttackRange, attackRange;//��l�����d��B�ثe�����d��

	vector<Buff> buff;//�M�Τ���BUFF
	bool isDead;//�O�_���`
};