#include "StdAfx.h"
#include "Monster.h"
#include "Player.h"
Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 150;
	attackField = 30;
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
	rl = 1;
	SetOriginAttackRange(10);
	SetAttackRange(GetOriginAttackRange());
}

void Monster::SetDefenseRange(int defenseRange) {
	this->defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
}

void Monster::SetRL(int rl) {
	this->rl = rl;
}

int Monster::GetRL() {
	return rl;
}

int Monster::GetdX(int point) {
	if (point == 0)
		return dX[0];
	else
		return dX[1];
}

void Monster::SetdY() {
	this->dY[0] = y - defenseRange; //�U
	this->dY[1] = y + defenseRange;	//�W
}

void Monster::AutoMove() {
	if (rl == LEFT && status == STANDBY)							//�p�GGetLR == 0 , X ��������
		this->x = x - moveSpeed;

	else if (rl == RIGHT && status == STANDBY)
		this->x = x + moveSpeed;					//�p�GGetLR == 1 , X ���k����


	if (x <= dX[0] && rl != 0)       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
		this->rl = RIGHT;

	else if (x >= dX[1] && rl != 0) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
		this->rl = LEFT;
}

bool Monster::IsInAttackField	(int playerX, int playerY) {
	int attackXField_Left = x - attackField, attackXField_Right = x + attackField;
	int attackYField_down = y + attackField, attackYField_up = y - attackField;

	if (playerX >= attackXField_Left && playerX <= attackXField_Right &&
		playerY >= attackYField_up && playerY <= attackYField_down)
		return true;

	return false;
}

void Monster::AttackPlayer() {
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");
	const int ATTACK_SPEED = 4;

	if (IsInAttackField(player->GetX(), player->GetY())) {  //�Ǫ��ĹL�h�����D��
		status = ATTACK;

		moveSpeed = ATTACK_SPEED;
		if(IsAnthorObjectInRange(player) == false ) {
			if (x > player->GetX() )
				x -= moveSpeed;
			else if (x < player->GetX())
				x += moveSpeed;
		}

		/*moveSpeed = ATTACK_SPEED;
		if (x > player->GetX())
			x -= moveSpeed;
		else
			x += moveSpeed;
		if (y > player->GetX())
			y -= moveSpeed;
		else
			y += moveSpeed;*/

	}
	else{
		status = STANDBY;
		moveSpeed = originMoveSpeed;
	}
}