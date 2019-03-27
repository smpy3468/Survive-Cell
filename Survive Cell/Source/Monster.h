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
	void SetDefenseRange(int Rnage);
	void SetRL(int rl);

	int GetDefenseRange();
    int GetRL();
	int GetdX(int point);

	void SetdX();
	void SetdY();

	void Move(int dx, int dy) {}

	void AutoMove(); //�b���u�ϰ줺�Ӧ^����
	bool IsInAttackField(int playerX, int playerY,int right_fix, int left_fix, int up_fix, int down_fix);   //�O���ܡA�ĦV�D�� #�MIsPlayerInRange�@�ˤ���nvirtual
	int  PlaceRelativePlayer(Player* player); //�Ǫ��۹��}�⪺��m
	void Attack()override;//��Player�i�J���u�ϡA�����L


	void ShowBitMap()override;

private:	
	int defenseRange, attackField; //defenseRange �Ӧ^���ʪ��d��, attackfield�ĹL�h�����D�����d��
	int dX[2] ,dY[2]; //���k�B�W�U
	int rl,status;
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ALERTNESS = 1, ATTACK = 2; //�ثe�Ǫ������A

	void Dead()override;

	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix); //�i�J�����Z���N���U��  #Attackfild�n���j�o�ӳ]�w�F�~����
	//����nvirtual �������P���ǰ��X�����d�򪺥���
	void LoadAni()override; //���J�ʵe
	int currentAni = 0; //�{�b����o�ʵe

	const int ANI_IDLE = 0; //��a
	const int ANI_LEFT = 1; //���ʵe
	const int ANI_RIGHT = 2; //�k�ʵe
};