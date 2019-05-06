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
	~Monster();
	Monster::Monster(string tag, int x, int y, int width, int height);
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
	void Fall(int perDisplacement);			  //���U
	void Up();								  //�Ǫ����W�a��

	//----------------��������---------------------//
	bool IsInAttackField(int playerX, int playerY, int right_fix, int left_fix, int up_fix, int down_fix);   //Player�O�_�bAttackField��, �O���ܡA�ĦV�D�� 
	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix);			//��̪��ϧάO�_��Ĳ�I��
	int  PlaceRelativePlayer(Player* player); //�Ǫ��۹��}�⪺��m
	
	virtual void Attack();//��Player�i�J���u�ϡA�����L
	void PlayerAttack(int damage);

	//-----------------Animation------------------///
	void ShowBitMap()override;
	int GetAttackAniNumber();

	virtual void Act();   //�զX�U�ذʧ@(ISATTACK, AUTOMOVE, ATTACK)

protected:
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ATTACK = 3, FALL = 4, ISATTACK=5; //�Ǫ������A
	int status ;													   //�{�b���A
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");				//�`�Ψ�N���O���U��
	
	int fallDisplacement = 0;
	int currentAni = 0;                                            //�{�b����o�ʵe  
	enum ANI
	{
		ANI_IDLE = 0,		   //��a
		ANI_LEFT,			   //�����ʰʵe
		ANI_RIGHT,			   //�k���ʰʵe
		ANI_ATTACK_LEFT,	   //��������ʵe
		ANI_ATTACK_RIGHT,	   //�k������ʵe
		ANI_ISATTACK_RIGHT,	   //�Q�����k��ʵe
		ANI_ISATTACK_LEFT		   //�Q��������ʵe
	};

	

private:

	int dX[2], dY[2];											   //0��1�k�B0�W1�U
	int rl;														   //�{�b�����䨫	
	int defenseRange, attackField;								   //defenseRange �Ӧ^���ʪ��d��, attackfield�ĹL�h�����D�����d��
	

	void Dead()override;										   //���`
};