#pragma once

//Monster
//�Ǫ�
//�~��Character

#include "Character.h"
#include "GameSystem.h"
#include "Player.h"
class Monster :public Character
{
public:
	Monster();
	Monster::Monster(string tag, int x, int y, int width, int height, int pictureID);
	void SetDefenseRange(int defenseRange);
	void SetRL(int rl);
	void SetdX();
	void SetdY();
	void SetAttackField(int attackField);
	void SetAttackRange(int attackRange);


	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);
	int GetStatus();


	void Move(int dx, int dy) {}

	//----------------���ʬ���---------------------//
	virtual void AutoMove(); //�b���u�ϰ줺�Ӧ^����

	//----------------��������---------------------//
	bool IsInAttackField(int playerX, int playerY,int right_fix, int left_fix, int up_fix, int down_fix);   //�O���ܡA�ĦV�D�� #�MIsPlayerInRange�@�ˤ���nvirtual
	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix);
	int  PlaceRelativePlayer(Player* player); //�Ǫ��۹��}�⪺��m

	virtual void Attack();//��Player�i�J���u�ϡA�����L
	
	//-----------------Animation------------------///
	void ShowBitMap()override;
	int GetAttackAniNumber();

protected:
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2; //�ثe�Ǫ������A
	int status;
	int currentAni = 0; //�{�b����o�ʵe

	const int ANI_IDLE = 0; //��a
	const int ANI_LEFT = 1; //�����ʰʵe
	const int ANI_RIGHT = 2; //�k���ʰʵe
	const int ANI_ATTACK_LEFT = 3;  //��������ʵe
	const int ANI_ATTACK_RIGHT = 4; //�k������ʵe
private:	
	//defenseRange �Ӧ^���ʪ��d��, attackfield�ĹL�h�����D�����d��
	int dX[2] ,dY[2]; //���k�B�W�U
	int rl;
	int defenseRange, attackField;

	void Dead()override;

	//void LoadAni()override; //���J�ʵe
	
};