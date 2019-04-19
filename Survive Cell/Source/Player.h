#pragma once

//Player
//���a
//�~��Character
#include "StdAfx.h"
#include "Character.h"
#include "Item.h"
#include "ItemWeapon.h"

class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height);

	//----------------�������---------------------//
	void SetIsMoveLeft(bool isMoveLeft);//�]�w�O�_�V������
	void SetIsMoveRight(bool isMoveRight);//�]�w�O�_�V�k����
	void SetIsGrounded(bool isGrounded);//�]�w�O�_�b�a�W
	void SetIsJump(bool isJump);//�]�w�O�_���U���D
	void SetIsAttack(bool isAttack);//�]�w�O�_���U����

	bool HasWeapon();//�O�_���Z��
	
	//----------------�ʧ@����---------------------//
	void Move();//���U���䲾��
	void Fall();//�U��
	void Jump();//���D
	void Interact();//����
	void Move(int dx, int dy)override;//���ʯS�w�Z��
	void Attack()override;//����

	//----------------�ʵe����---------------------//
	void ShowBitMap()override;//��ܰʵe

	//-------------��ܪ��a��T------------------//
	void ShowInformation();//��ܪ��a��T
	
	//-------------�t�ά���------------------//
	template <class T> void AddEquipment(T* equipment)//�W�[�˳�
	{
		this->equipments.push_back(equipment);

		if (!this->hasWeapon)//�S���Z��
		{
			if (equipment->GetTag() == "PlayerWeapon")//�O�Z��
			{
				this->weapon = equipments[equipments.size() - 1];
				hasWeapon = true;//���Z���F
			}
		}

		CalculateAbility(equipment);//�p���O��
	}

private:
	bool isMoveLeft;//�O�_�V������
	bool isMoveRight;//�O�_�V�k����
	bool isJumpKeyDown;//�O�_���U���D
	bool isJump;//�O�_���b���D
	bool isFall;//�O�_���b�U��
	bool isAttack;//�O�_���b����

	int fallDisplacement;//�U���첾�q(���ʨ�S���a�O����m�|�Ψ�)
	int originJumpDisplacement, jumpDisplacement;//���D�첾�q
	bool isGrounded;//�O�_�b�a�W

	void CalculateAbility(PlayerEquipment* equipment);//�p���O��

	void Dead()override;//���`�ɩI�s

	//---------------�ʵe����---------------//
	void ShowWeapon();//��ܪZ��

	bool faceLR;//���V����έ��V�k��
	const bool FACE_LEFT = true;//���V����
	const bool FACE_RIGHT = false;//���V�k��

	void LoadAni()override;//���J�ʵe
	int currentAni = 0;//�ثe�ʵe
	enum ANI
	{
		ANI_IDLE = 0,
		ANI_LEFT,
		ANI_RIGHT,
		ANI_ATTACK_LEFT,
		ANI_ATTACK_RIGHT,
		ANI_JUMP_LEFT,
		ANI_JUMP_RIGHT,
		ANI_GET_HIT_LEFT,
		ANI_GET_HIT_RIGHT
	};

	vector<PlayerEquipment*> equipments;//�˳�
	PlayerEquipment* weapon;//�Z��

	//�ۿA�[��
	//Item* equipment;
	bool hasWeapon=false;
};