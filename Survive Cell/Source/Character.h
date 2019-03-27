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
	void SetOriginAttackDamage(int originAttack);//�]�w��l�����O
	void SetAttackDamage(int attack);//�]�w�ثe�����O
	void SetOriginAttackSpeed(int originAttackSpeed);//�]�w��l�����t��
	void SetAttackSpeed(int attackSpeed);//�]�w�ثe�����t��
	void SetOriginAttackRange(int originAttackRange);//�]�w��l�����d��
	void SetAttackRange(int attackRange);//�]�w�ثe�����d��
	void SetIsDead(bool isDead);//�]�w�O�_���`

	int GetMaxHP();//���o�̤j��q
	int GetHP();//���o�ثe��q
	int GetOriginMoveSpeed();//���o��l���ʳt��
	int GetMoveSpeed();//���o�ثe���ʳt��
	int GetOriginAttackDamage();//���o��l�����O
	int GetAttackDamage();//���o�ثe�����O
	int GetOriginAttackRange();//���o��l�����d��
	int GetAttackRange();//���o�����d��
	bool IsDead();//�T�{�O�_���`

	void SetBitMapPosition()override;//�]�w�ʵe��m

	void DecreaseHP(int dhp);//����
	void IncreaseHP(int ihp);//�[��
	virtual void Attack() = 0;//����
	virtual void Move(int dx, int dy) = 0;

protected:
	int maxHP, HP;//�̤j��q�B�ثe��q
	int originMoveSpeed, moveSpeed;//��l���ʳt�סB�ثe���ʳt��
	int originAttackDamage, attackDamage;//��l�����O�B�ثe�����O
	int	originAttackSpeed, attackSpeed;//��l�����t�סB�ثe�����t��
	int originAttackRange, attackRange;//��l�����d��B�ثe�����d��

	vector<Buff> buff;//�M�Τ���BUFF
	bool isDead;//�O�_���`
	void Dead()override;//���`�ɩI�s

	vector<CAnimation*> ani;//�ʵe
	virtual void LoadAni(); //���J�ʵe
	void AddAniBitMaps(char* pic[], int aniType, int picCount);//�W�[�h�i�ʵe�Ϥ�
	void AddAniBitMap(char* pic, int aniType);//�W�[�ʵe�Ϥ�
};