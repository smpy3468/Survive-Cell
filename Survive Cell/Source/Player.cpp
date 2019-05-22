#include "StdAfx.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Item.h"
#include "PlayerTradationalSword.h"
#include "Floor.h"
#include "Door.h"
#include "Goal.h"
#include "Portal.h"

Player::Player()
{
	tag = "Player";
}

Player::~Player()
{
	for (unsigned int i = 0; i < equipments.size(); i++)
	{
		delete equipments[i];
	}
	equipments.clear();
}

Player::Player(string tag, int x, int y, int width, int height) :Character(tag, x, y, width, height)
{
	tag = "Player";

	maxHP = 1000;
	HP = maxHP;

	originWidth = width;
	originHeight = height;

	originMoveSpeed = 5;
	moveSpeed = originMoveSpeed;

	fallDisplacement = 0;

	originJumpDisplacement = 15;
	jumpDisplacement = originJumpDisplacement;

	originRollDisplacement = 15;
	rollDisplacement = originRollDisplacement;

	attackRange = 10;
	attackDamage = 10;
	attackSpeed = 5;
	defense = 0;
	destinationX = 0;
	destinationY = 0;

	isMoveLeft = false;
	isMoveRight = false;

	isJumpKeyDown = false;
	isJump = false;
	isFall = false;
	isGrounded = false;
	isRollKeyDown = false;
	isRoll = false;
	isSquatKeyDown = false;
	isSquat = false;
	isUnconquered = false;
	isDownJump = false;
	isPortaling = false;
	isAttack = false;
	isGetHit = false;

	faceLR = FACE_RIGHT;

	currentAni = ANI::ANI_IDLE;

	layer = GameSystem::LAYER::LAYER_PLAYER;

	LoadAni();
}

void Player::AdjustPositionOnBegin()
{
	while (Map::HasObject(x, y + this->height + 1))
	{
		this->y--;
	}
}

void Player::DecreaseHP(int dhp)
{
	//if (isUnconquered == false)
	{
		isGetHit = true;
		HP -= dhp;
	}
	if (HP <= 0)
	{
		HP = 0;
		isDead = true;

		Dead();
	}
}


void Player::Move(int dx, int dy)
{
	if ((dx > 0 && CanMoveRight(moveSpeed)) || (dx < 0 && CanMoveLeft(moveSpeed)))//x�첾�q���k�ӥB�k��S�F�� �Ϊ� x�첾�q�����ӥB����S�F��
	{
		this->x += dx;//���ax����
	}

	this->y += dy;//���ay����

	if (dx > 0 && this->x + this->width / 2 >= Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//�ù�����
	else if (dx < 0 && this->x + this->width / 2 < Map::GetSX() + SIZE_X / 2)
		Map::MoveScreenTopLeft(dx, 0);//�ù�����

	if (dy > 0 && this->y + this->height / 2 >= Map::GetSY() + SIZE_Y * 3 / 4)
		Map::MoveScreenTopLeft(0, dy);//�ù�����
	else if (dy < 0 && this->y + this->height / 2 < Map::GetSY() + SIZE_Y / 4)
		Map::MoveScreenTopLeft(0, dy);//�ù�����
}

void Player::MoveTo(int x, int y)
{
	Character::MoveTo(x, y);
	Map::SetSX(x - SIZE_X / 2);
	Map::SetSY(y - SIZE_Y / 2);
}

void Player::SetIsMoveLeft(bool isMoveLeft)
{
	this->isMoveLeft = isMoveLeft;
}

void Player::SetIsMoveRight(bool isMoveRight)
{
	this->isMoveRight = isMoveRight;
}

void Player::SetIsJump(bool isJump)
{
	this->isJumpKeyDown = isJump;
}

void Player::SetIsDownJump(bool isDownJump)
{
	this->isDownJump = isDownJump;
}

void Player::SetIsAttack(bool isAttack)
{
	this->isAttack = isAttack;
}

void Player::SetIsRoll(bool isRoll)
{
	this->isRollKeyDown = isRoll;
}

void Player::SetIsSquat(bool isSquat)
{
	this->isSquatKeyDown = isSquat;
}

void Player::SetIsUnconquered(bool isUnconquered)
{
	this->isUnconquered = isUnconquered;
}

bool Player::GetIsJump()
{
	return isJump;
}

void Player::SetIsPortaling(bool isPortaling, int destX, int destY)
{
	this->isPortaling = isPortaling;
	this->destinationX = destX;
	this->destinationY = destY;
}

bool Player::HasWeapon()
{
	return hasWeapon;
}

void Player::SetIsGrounded(bool isGrounded)
{
	this->isGrounded = isGrounded;
}

void Player::Act()//���
{
	/*switch (currentState)
	{
	case STATE_IDLE:
		if (isMoveLeft)
			nextState = STATE_MOVE_LEFT;
		if (isMoveRight)
			nextState = STATE_MOVE_RIGHT;
		if (isSquat)
		{
			if (isJumpKeyDown)
				nextState = STATE_DOWN_JUMP;
			else
				nextState = STATE_SQUAT;
		}
		if (isJumpKeyDown)
			nextState = STATE_JUMP;
		if (isAttack)
			nextState = STATE_ATTACK;
		break;

	case STATE_MOVE_LEFT:
		faceLR = FACE_LEFT;
		Move(-moveSpeed, 0);
		break;

	case STATE_MOVE_RIGHT:
		faceLR = FACE_RIGHT;
		Move(moveSpeed, 0);
		break;

	case STATE_ATTACK:
		Attack();
		break;

	case STATE_JUMP:
		Jump();
		break;

	case STATE_DOWN_JUMP:
		DownJump();
		break;

	case STATE_ROLL:
		Roll();
		break;

	case STATE_SQUAT:
		ChangeHeight(originHeight / 2);//�N�����ܬ��@�b
		SetMoveSpeed(originMoveSpeed / 2);//�t���ܬ��@�b
		break;
	}

	if(isJump == false)
		Fall();
	currentState = nextState;*/


	if (isRoll == true || isSquat)//½�u�����ۤU���������
		isAttack = false;


	if (isAttack == false)//�S�b����
	{
		if (isRollKeyDown)//���U½�u
		{
			isRollKeyDown = false;

			if (isGrounded && isRoll == false)//�b�a�W�~��}�l½�A�ӥB�ثe�٨S½�u(½��e���u��½��@��)
			{
				isUnconquered = true;//½�u�ɵL��
				isRoll = true;
				FlipWidthHeight();//½��e��
			}
		}
		else if (isRoll == false)
		{
			if (this->isSquatKeyDown)//�ۤU
			{
				//isSquatKeyDown = false;
				if (isGrounded)
				{
					isSquat = true;//�����ۤU���A

					//if(height == originHeight)//���׸�쥻�@��
					ChangeHeight(originHeight / 2);//�N�����ܬ��@�b
					SetMoveSpeed(originMoveSpeed / 2);//�t���ܬ��@�b
				//else
					//ChangeHeight(originHeight);//�N�����٭�
				}
			}
			else
			{
				if (CanStand())
				{
					isSquat = false;
					ChangeHeight(originHeight);//�N�����٭�
					SetMoveSpeed(originMoveSpeed);//�N�t���٭�
				}
			}

			if (this->isMoveLeft)
			{
				if (this->x > 0)
				{
					faceLR = FACE_LEFT;//���V����
					Move(-moveSpeed, 0);
				}
			}

			if (this->isMoveRight)
			{
				if (this->x + this->width < Map::WORLD_SIZE_X)
				{
					faceLR = FACE_RIGHT;//���V�k��
					Move(moveSpeed, 0);
				}
			}
		}

		if (this->isJumpKeyDown)//�p�G���U���D
		{
			isJumpKeyDown = false;//���D�䤣��������

			if (isRoll == false)//½�u��������D
			{
				if (isGrounded)//�p�G�b�a�W
				{
					if (isSquat)//�ۤU�B���D�A�i��U��
					{
						SetIsDownJump(true);//�U��
						isSquat = false;//�U���ɤ��A�ۤU
						ChangeHeight(originHeight);//�N�����٭�
						SetMoveSpeed(originMoveSpeed);//�N�t���٭�
					}
					else
					{
						isJump = true;//���b���D
					}
					isGrounded = false;//�S�b�a�W
				}

				if (!isDownJump)//�S���U���~��h�q��
				{
					if (jumpCount < MAX_JUMP_COUNT)//�p��̤j���D�q��
					{
						jumpCount++;//�p�ƥثe�O�X�q��
						jumpDisplacement = originJumpDisplacement;//���m���D�첾�q�A�e�{�G�q�����ĪG

						//�H�U�O:�Y�b�U�������U�G�q��
						isFall = false;//�p�G�쥻�b�U���A�h���A�U��
						fallDisplacement = 0;//�U���첾�q���m
						isJump = true;//���s���W�����D
					}
				}
			}
		}
	}

	if (isRoll)
		Roll();

	if (isPortaling)
		Portaling();

	else if (isDownJump)
	{
		DownJump();
	}
	else
	{
		if (isJump)
			Jump();//���D
		else
			Fall();//�U��
	}
}

void Player::Fall()
{
	if (CanMoveDown(fallDisplacement))//�p�G�}�U�S�F��
	{
		isFall = true;//���b�U��
		isGrounded = false;//���b�a�W
		fallDisplacement++;
		Move(0, fallDisplacement);
	}
	else
	{
		while (CanMoveDown(1))//�A�~��ΤU���첾�q�U���A�N�|�d�i�a�O�A�ҥH�@���V�U�첾1�i��L��
			Move(0, 1);

		fallDisplacement = 0;
		isGrounded = true;//�b�a�W
		isFall = false;//�S�b�U��
		jumpCount = 0;//���D�q�ƭ��m

		if (currentAni == ANI::ANI_JUMP_LEFT)//�N���D�ʵe�٭�
			currentAni = ANI::ANI_LEFT;
		else if (currentAni == ANI::ANI_JUMP_RIGHT)
			currentAni = ANI::ANI_RIGHT;
	}
}

void Player::Jump()
{
	if (isGrounded == false && isFall == false)//�p�G�S�b�a�W�B�S�b�U��
	{
		jumpDisplacement--;//�첾�q�H�ۮɶ�����

		if (jumpDisplacement >= 0)//���W��
		{
			if (CanMoveUp(jumpDisplacement))//�i�V�W����
				Move(0, -jumpDisplacement);
			else
				jumpDisplacement = 0;//�}�l���U��
		}
		else//���U��
		{
			isJump = false;
			isFall = true;
			jumpDisplacement = originJumpDisplacement;//���D�첾�q�٭�
		}
	}
}

void Player::DownJump()
{
	Move(0, fallDisplacement);//�V�U����
	fallDisplacement++;

	if (IsInFloor() == false//���b�a�O��
		//|| y + height + 1 >= GameSystem::GetGameObjectWithTag<Floor>("Ground")->GetY()//�w�b�̩��h�a�O
		//|| IsFloorOnGround()//�a�O��̩��h�a�O��n�K�X�A�N����U��
		|| !HasSpaceToDownJump())//�U��S���������Ŷ��i�H�U��
	{
		isDownJump = false;//�S���U��
	}
}

bool Player::HasSpaceToDownJump()
{
	int returnValue = true;//�^�ǭ�

	for (int i = x; i < x + width; i++)
	{
		int cy = y + height + 1;//���a�}������m

		while (Map::HasObject(i, cy))//���B���a�O
		{
			cy++;//cy���U���ʪ���S���a�O

			if (cy >= Map::WORLD_SIZE_Y)//cy�w�W�X�a�Ͻd��
			{
				return false;//�S���Ŷ��i�H�U��
			}
		}

		int h = 0;//�T�{���׬O�_���������a�i�J

		while (!Map::HasObject(i, cy))//���B�S���a�O
		{
			h++;//���׼W�[
			cy++;//cy���U����
		}

		if (h < height)//�S������������
		{
			return false;//����U��
		}
	}
	return true;
}

void Player::ChangeHeight(int height)
{
	AdjustY(this->height - height);
	this->height = height;
}

bool Player::CanStand()
{
	for (int i = x; i < x + width; i++)
	{
		int h = 0;//�p�Ⱚ��
		int cy = y + h;//�q���a�}���}�l

		while (!Map::HasObject(i, cy) && h < height)//���W�p�Ⱚ�צ��h��
		{
			cy--;
			h++;
		}

		if (h < height)//���פ���
			return false;
	}

	return true;//�C��x�y�ФW�誺���׳���
}

/*bool Player::IsFloorOnGround()
{
	int cy = y + height + 1;//���a�}������m

	for (int i = x; i < x + width; i++)
	{
		while (Map::HasObject(i, cy))//���B���a�O
		{
			cy++;//�~�򩹤U�T�{�O�_�٬O�a�O
			if (cy >= GameSystem::GetGameObjectWithTag<Floor>("Ground")->GetY())//�p�G�w��F�̩��h�a�O
			{
				return true;
			}
		}
	}
	return false;
}*/

void Player::Interact()
{
	//�Y���h�ӯ�����ʪ������|�A�h����D�㤬�ʡA�A�������
	vector<Item*> itemList;//�D��
	vector<Goal*> goalList;//���I����
	vector<Portal*> portalList;//�ǰe��

	for (auto&i : GameSystem::GetAllGameObject())//�N����������[�J�������C��
	{
		if (dynamic_cast<Item*>(i) != NULL)//�D��
			itemList.push_back(dynamic_cast<Item*>(i));

		else if (dynamic_cast<Goal*>(i) != NULL)//���I
			goalList.push_back(dynamic_cast<Goal*>(i));

		else if (dynamic_cast<Portal*>(i) != NULL)//�ǰe��
			portalList.push_back(dynamic_cast<Portal*>(i));
	}

	for (auto& i : itemList)//��D�㤬��
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Item*>(i)->Picked();
			return;
		}
	}

	for (auto& i : goalList)//����I����
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Goal*>(i)->Picked();
			return;
		}
	}

	for (auto& i : portalList)//��ǰe������
	{
		if (i->GetX() + i->GetWidth() > this->x && i->GetX() < this->x + this->width
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height) {
			static_cast<Portal*>(i)->Used();
			return;
		}
	}
}

void Player::Attack()
{
	vector<Monster*>monsters = GameSystem::GetGameObjectsWithType<Monster>();
	//vector<Monster*> monsters = GameSystem::GetGameObjectsWithTag<Monster>("Monster");

	for (auto& i : monsters)//��Ǫ�����
	{
		if (i->GetX() + i->GetWidth() > this->x - attackRange && i->GetX() < this->x + this->width + attackRange
			&& i->GetY() + i->GetHeight() > this->y && i->GetY() < this->y + this->height)//�Ǫ��b�����d��
		{
			i->PlayerAttack(attackDamage);
			GameSystem::ShowText(to_string(GetAttackDamage()), i->GetX() - Map::GetSX() + 10, i->GetY() - Map::GetSY() - 30, i->GetX() + i->GetWidth() - Map::GetSX(), i->GetY() + i->GetHeight() - Map::GetSY(), GameSystem::ALIGN_CENTER, GameSystem::ALIGN_TOP, 20, RGB(255, 0, 0));
		}
	}

	isAttack = false;//��������
}

void Player::Portaling()		//�ǰe
{
	int dX = (destinationX - x) / 4;//�|�i�ʵe �C�i�ʵe�o�첾�q
	int dY = (destinationY - y) / 4;


	if (x != destinationX && dX > 0)
	{
		x += dX;
		Map::MoveScreenTopLeft(dX, 0);
	}
	else if (x != destinationX && dX < 0)
	{
		x += dX;
		Map::MoveScreenTopLeft(dX, 0);
	}

	if (y != destinationY && dY < 0)
	{
		y += dY;
		Map::MoveScreenTopLeft(0, dY);
	}
	else if (y != destinationY && dY > 0)
	{
		y += dY;
		Map::MoveScreenTopLeft(0, dY);
	}

	if (abs(x - destinationX) <= 30 && abs(y - destinationY) <= 30)
		isPortaling = false;
}

void Player::ShowBitMap()
{
	if (isGetHit)//�Q����
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI_GET_HIT_LEFT;
		}
		else
		{
			currentAni = ANI_GET_HIT_RIGHT;
		}

		ani[currentAni]->OnMove();

		if (ani[currentAni]->IsEnd())
			isGetHit = false;
	}
	else if (isAttack)
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_ATTACK_LEFT;
			ani[ANI::ANI_ATTACK_LEFT]->OnMove();
		}
		else
		{
			currentAni = ANI::ANI_ATTACK_RIGHT;
			ani[ANI::ANI_ATTACK_RIGHT]->OnMove();
		}

		if (ani[currentAni]->IsEnd())
		{
			Attack();
		}
	}
	else if (isRoll)//½�u�ʵe
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_ROLL_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_ROLL_RIGHT;
		}
	}
	else if (isSquat)
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_SQUAT_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_SQUAT_RIGHT;
		}
	}

	else if (isJump || isFall || isDownJump)//���D�ʵe
	{
		if (faceLR == FACE_LEFT)
		{
			currentAni = ANI::ANI_JUMP_LEFT;
		}
		else
		{
			currentAni = ANI::ANI_JUMP_RIGHT;
		}
	}
	else if (isPortaling)
	{
		currentAni = ANI::ANI_PORTALING;
		ani[ANI::ANI_PORTALING]->OnMove();
	}
	else if (isMoveLeft)//�����ʵe
	{
		currentAni = ANI::ANI_LEFT;
		ani[ANI::ANI_LEFT]->OnMove();
	}
	else if (isMoveRight)//�k���ʵe
	{
		currentAni = ANI::ANI_RIGHT;
		ani[ANI::ANI_RIGHT]->OnMove();
	}
	else
	{
		for (auto& i : ani)
		{
			i->Reset();//���m�Ҧ��ʵe
		}

		if (faceLR == FACE_LEFT)
			currentAni = ANI::ANI_LEFT;
		else
			currentAni = ANI::ANI_RIGHT;
	}
	ani[currentAni]->OnShow();

	if (hasWeapon)//���Z���N��ܪZ��
	{
		ShowWeapon();
	}
}

void Player::ShowInformation()
{
	/*
	string information = "Attack" + to_string(attackDamage)
		+ "\nAttackSpeed:" + to_string(attackSpeed) + "\nAttackRange:" + to_string(attackRange)
		+ "\nMoveSpeed:" + to_string(moveSpeed) + "\nDefense:" + to_string(defense)
		+ "\nUnconquered:" + to_string(isUnconquered)
		+ "\nHP:" + to_string(HP);

		GameSystem::ShowText(information, 0, 0, SIZE_X, SIZE_Y, GameSystem::ALIGN_LEFT, GameSystem::ALIGN_TOP, 8, RGB(0, 0, 0));
	*/
}

void Player::CalculateAbility(PlayerEquipment* equipment)
{
	//�����O�P���m�֥[�W�h
	this->attackDamage = equipment->GetAttackDamage();
	this->defense = equipment->GetDefense();

	//�����Z���ϥΪZ���������Z��
	this->attackRange = equipment->GetAttackRange();
}

void Player::Dead()
{
	GameSystem::SetGameOver();//�C������
	//GameSystem::DeleteGameObject(this);
}

void Player::Roll()
{
	if (faceLR == FACE_LEFT)
	{
		Move(-rollDisplacement, 0);
	}
	else
	{
		Move(rollDisplacement, 0);
	}

	for (auto& i : GameSystem::GetGameObjectsWithTag<Door>("Door"))//½�u�ɽ��
	{
		if (i->GetX() < this->x + this->width && i->GetX() + i->GetWidth() > this->x
			&& i->GetY() < this->y + this->height && i->GetY() + i->GetHeight() > this->y && !i->GetRuin())//���b���a�d�� 
		{
			i->Kicked();//���
			break;
		}


	}

	if (rollDisplacement-- <= 0)
	{
		isUnconquered = false;//�L�ĵ���
		isRoll = false;//½�u����
		rollDisplacement = originRollDisplacement;

		FlipWidthHeight();//�٭�e��

		if (CanStand() == false)//½�u�����᪺��m�L�k���_
		{
			isSquat = true;//�ܬ��ۤU���A
			ChangeHeight(originHeight / 2);//�N�����ܬ��@�b
			SetMoveSpeed(originMoveSpeed / 2);//�t���ܬ��@�b
		}
	}
}

void Player::FlipWidthHeight()
{
	int temp = width;
	width = height;
	height = temp;

	AdjustY(width - height);
}

void Player::AdjustY(int dy)
{
	y += dy;
}

void Player::ShowWeapon()
{
	if (faceLR == FACE_LEFT)
	{
		weapon->SetXY(x, y, ANI_ATTACK_LEFT, ani[ANI::ANI_ATTACK_LEFT]->GetCurrentBitmapNumber());
		weapon->ShowBitMap();
	}
	else
	{
		weapon->SetXY(x, y, ANI_ATTACK_RIGHT, ani[ANI::ANI_ATTACK_RIGHT]->GetCurrentBitmapNumber());
		weapon->ShowBitMap();
	}
}

void Player::LoadAni()
{
	objectPic.LoadBitmap(".\\res\\player.bmp");

	//---------------�R��
	char* aniIdle[1] = { ".\\res\\player_idle.bmp" };
	AddAniBitMaps(aniIdle, ANI::ANI_IDLE, 1);

	//---------------����
	char* aniLeft[4] = { ".\\res\\player_left_0.bmp", ".\\res\\player_left_1.bmp", ".\\res\\player_left_2.bmp", ".\\res\\player_left_3.bmp" };
	AddAniBitMaps(aniLeft, ANI::ANI_LEFT, 4);

	//---------------�k��
	char* aniRight[4] = { ".\\res\\player_right_0.bmp", ".\\res\\player_right_1.bmp", ".\\res\\player_right_2.bmp", ".\\res\\player_right_3.bmp" };
	AddAniBitMaps(aniRight, ANI::ANI_RIGHT, 4);

	//---------------����
	char* aniJumpLeft = ".\\res\\player_jump_left.bmp";
	AddAniBitMap(aniJumpLeft, ANI::ANI_JUMP_LEFT);

	//---------------�k��
	char* aniJumpRight = ".\\res\\player_jump_right.bmp";
	AddAniBitMap(aniJumpRight, ANI::ANI_JUMP_RIGHT);

	//---------------����
	char* aniAttackLeft[3] = { ".\\res\\player_attack_left_0.bmp", ".\\res\\player_attack_left_1.bmp", ".\\res\\player_attack_left_2.bmp" };
	AddAniBitMaps(aniAttackLeft, ANI::ANI_ATTACK_LEFT, 3, 5);

	//---------------�k��
	char* aniAttackRight[3] = { ".\\res\\player_attack_right_0.bmp", ".\\res\\player_attack_right_1.bmp", ".\\res\\player_attack_right_2.bmp" };
	AddAniBitMaps(aniAttackRight, ANI::ANI_ATTACK_RIGHT, 3, 5);

	//---------------���Q��
	char* aniGetHitLeft = ".\\res\\player_get_hit_left.bmp";
	AddAniBitMap(aniGetHitLeft, ANI::ANI_GET_HIT_LEFT);

	//---------------�k�Q��
	char* aniGetHitRight = ".\\res\\player_get_hit_right.bmp";
	AddAniBitMap(aniGetHitRight, ANI::ANI_GET_HIT_RIGHT);

	//---------------��½�u
	char* aniRollLeft = ".\\res\\player_roll_left.bmp";
	AddAniBitMap(aniRollLeft, ANI::ANI_ROLL_LEFT);

	//---------------�k½�u
	char* aniRollRight = ".\\res\\player_roll_right.bmp";
	AddAniBitMap(aniRollRight, ANI::ANI_ROLL_RIGHT);

	//���ۤU
	char* aniSquatLeft = ".\\res\\player_squat_left.bmp";
	AddAniBitMap(aniSquatLeft, ANI::ANI_SQUAT_LEFT);

	//�k�ۤU
	char* aniSquatRight = ".\\res\\player_squat_right.bmp";
	AddAniBitMap(aniSquatRight, ANI::ANI_SQUAT_RIGHT);

	//�ǰe
	char* aniPortaling[4] = { ".\\res\\portaling0.bmp",  ".\\res\\portaling1.bmp" , ".\\res\\portaling2.bmp" ,".\\res\\portaling0.bmp" };
	AddAniBitMaps(aniPortaling, ANI::ANI_PORTALING, 4, 2);
}
