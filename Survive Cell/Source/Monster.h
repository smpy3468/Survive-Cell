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
	void SetDefenseRange(int defenseRange);		//�]�w�Ӧ^���ʶZ��
	void SetRL(int rl);							//�]�w�������k
	void SetdX();								//�]�w�������u���
	void SetdY();								//�]�w�������u���
	void SetAttackField(int attackField);		//�]�wĲ�o���H���Z��
	void SetAttackRange(int attackRange);		//�]�w�����Z��;


	int GetDefenseRange();						//���o�Ӧ^���ʶZ��(�q���������)
	int GetRL();								//���o�{�b�O���k�����٬O��������
	int GetdX(int point);						//GetdX(0)���o���䨾�u��u, GetdX(1)���o�k�䨾�u��u
	int GetStatus();							//���o�Ǫ��{�b���A STANDBY:0, LEFT:1, RIGTH:2, ATTACK = 3 


	//----------------���ʬ���---------------------//
	virtual void AutoMove(); //�b���u�ϰ줺�Ӧ^����
	void Move(int dx, int dy)override;

	//----------------��������---------------------//
	bool IsInAttackField(int playerX, int playerY, int right_fix, int left_fix, int up_fix, int down_fix);   //Player�O�_�bAttackField��, �O���ܡA�ĦV�D�� 
	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix);			//��̪��ϧάO�_��Ĳ�I��
	int  PlaceRelativePlayer(Player* player); //�Ǫ��۹��}�⪺��m

	virtual void Attack();//��Player�i�J���u�ϡA�����L

	//-----------------Animation------------------///
	void ShowBitMap()override;
	int GetAttackAniNumber();

protected:
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ATTACK = 2; //�Ǫ������A
	int status;													   //
	int currentAni = 0;                                            //�{�b����o�ʵe

	const int ANI_IDLE = 0;										   //��a
	const int ANI_LEFT = 1;										   //�����ʰʵe
	const int ANI_RIGHT = 2;									   //�k���ʰʵe
	const int ANI_ATTACK_LEFT = 3;								   //��������ʵe
	const int ANI_ATTACK_RIGHT = 4;							       //�k������ʵe
private:

	int dX[2], dY[2];											   //0��1�k�B0�W1�U
	int rl;														   //�{�b�����䨫	
	int defenseRange, attackField;								   //defenseRange �Ӧ^���ʪ��d��, attackfield�ĹL�h�����D�����d��

	void Dead()override;										   //���`
};