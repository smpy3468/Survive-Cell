#pragma once

//Player
//���a
//�~��Character
#include "StdAfx.h"
#include "Character.h"
#include "Item.h"
#include "ItemWeapon.h"
#include "PlayerEquipment.h"
#include "GameSystem.h"
class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height);

	void AdjustPositionOnBegin();//���J�C���ɷL�ժ��a��m�A�קK���a��a�O���|

	void DecreaseHP(int dhp);

	//----------------�������---------------------//
	void SetIsMoveLeft(bool isMoveLeft);//�]�w�O�_�V������
	void SetIsMoveRight(bool isMoveRight);//�]�w�O�_�V�k����
	void SetIsGrounded(bool isGrounded);//�]�w�O�_�b�a�W
	void SetIsJump(bool isJump);//�]�w�O�_���U���D
	void SetIsDownJump(bool isDownJump);//�]�w�O�_�U��
	void SetIsAttack(bool isAttack);//�]�w�O�_���U����
	void SetIsRoll(bool isRoll);//�]�w�O�_���U½�u
	void SetIsSquat(bool isSquat);//�]�w�O�_�ۤU
	
	void SetIsUnconquered(bool isUnconquered);//�]�w�O�_�L��

	bool HasWeapon();//�O�_���Z��

	//----------------�ʧ@����---------------------//
	void Act();//���U������
	void Fall();//�U��
	void Jump();//���D
	void DownJump();//�U��
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
	bool isDownJump;//�O�_���b�U��
	bool isFall;//�O�_���b�U��
	bool isAttack;//�O�_���b����
	bool isRoll;//�O�_���b½�u
	bool isRollKeyDown;//�O�_���U½�u
	bool isSquatKeyDown;//�O�_���U�ۤU
	bool isSquat;//�O�_�ۤU
	bool isUnconquered;//�O�_�L��

	int currentState = 0, nextState = 0;//�{�A,���A
	enum STATE//���A��
	{
		STATE_IDLE=0,
		STATE_MOVE_LEFT,
		STATE_MOVE_RIGHT,
		STATE_JUMP,
		STATE_DOWN_JUMP,
		STATE_ATTACK,
		STATE_ROLL,
		STATE_SQUAT
	};

	//---------------���D����---------------//
	int fallDisplacement;//�U���첾�q(���ʨ�S���a�O����m�|�Ψ�)
	int originJumpDisplacement, jumpDisplacement;//���D�첾�q
	bool isGrounded;//�O�_�b�a�W
	int jumpCount = 0;//���D�q�ƭp��
	const int MAX_JUMP_COUNT = 10;//�̦h��X�q��

	//---------------�ۤU����---------------//
	void ChangeHeight(int height);//���e���ܤ@��

	//---------------�U������---------------//
	bool IsFloorOnGround();//�a�O��̩��h�a�O��n�K�X�A�N����U��
	bool HasSpaceToDownJump();//�U�観���������ץi�H�e�Ǫ��a

	void CalculateAbility(PlayerEquipment* equipment);//�p���O��

	void Dead()override;//���`�ɩI�s

	//---------------½�u����---------------//
	void Roll();//½�u
	int originRollDisplacement, rollDisplacement;//½�u�첾�q
	int originWidth, originHeight;//½�u�ɨ���O�ˤU���A�e���|�����A��origin�ܼ��x�s�쥻���e��
	void FlipWidthHeight();//��ռe��
	void AdjustY(int dy);//�վ�y�y��

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
		ANI_GET_HIT_RIGHT,
		ANI_ROLL_LEFT,
		ANI_ROLL_RIGHT,
		ANI_SQUAT_LEFT,
		ANI_SQUAT_RIGHT
	};

	vector<PlayerEquipment*> equipments;//�˳�
	PlayerEquipment* weapon;//�Z��

	//�ۿA�[��
	//Item* equipment;
	bool hasWeapon = false;
};