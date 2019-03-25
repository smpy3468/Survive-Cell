#pragma once

//Monster
//�Ǫ�
//�~��Character

#include "Character.h"
#include "GameSystem.h"
class Monster :public Character
{
public:
	Monster();
	Monster::Monster(string tag, int x, int y, int width, int height, int pictureID);
	void SetDefenseRange(int Rnage);
	void SetRL(int rl);

	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);

	void SetdX();
	void SetdY();

	void Move(int dx, int dy) {}

	void AutoMove(); //�b���u�ϰ줺�Ӧ^����
	bool IsInAttackField(int playerX, int playerY);   //�O���ܡA�ĦV�D��
	void Attack()override;//��Player�i�J���u�ϡA�����L

	void ShowBitMap()override;

private:	
	int defenseRange, attackField; //defenseRange �Ӧ^���ʪ��d��, attackfield�ĹL�h�����D�����d��
	int dX[2] ,dY[2]; //���k�B�W�U
	int rl,status;
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2;

	void LoadAni()override;

	int currentAni = 0;
	const int ANI_LEFT = 0;
};