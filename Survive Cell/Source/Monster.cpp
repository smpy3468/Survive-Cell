#include "StdAfx.h"
#include "Monster.h"

Monster::Monster()
{
	tag = "Monster";
}


Monster::Monster(string tag, int x, int y, int width, int height, int pictureID) :Character(tag, x, y, width, height, pictureID)
{
	tag = "Monster";
	defenseRange = 5;
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
	rl = 1;
}

void Monster::SetDefenseRange(int defenseRange) {
	this -> defenseRange = defenseRange;
}

int Monster::GetDefenseRange() {
	return defenseRange;
}

void Monster::SetdX() {
	dX[0] = x - defenseRange; //����
	dX[1] = x + defenseRange;	//�k��
}

void Monster::SetRL(int rl) {
	this ->rl = rl;
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
	vector<Monster*> allMonster = GameSystem::GetGameObjectsWithTag("Monster");
	int monsterAmount = allMonster.size();
	
	for (int i = 0; i < monsterAmount; i++) {
		if (allMonster[i]-> GetRL() == 1)							//�p�GGetLR == 0 , X ��������
			allMonster[i]->SetX(allMonster[i]->GetX() - (1));

		else if (allMonster[i]->GetRL() == 2)
			allMonster[i]->SetX(allMonster[i]->GetX() + 1); //�p�GGetLR == 1 , X ���k����


		if (allMonster[i]->GetX() <= allMonster[i]->GetdX(0))       //GetdX[0]����ĵ�ٽd��A�p�G�W�L���� ��k�䲾��
			allMonster[i]->SetRL(1);

		else if (allMonster[i]->GetX() >= allMonster[i]->GetdX(1)) //GetdX[1]�k��ĵ�ٽd��A�p�G�W�L�k�� �索�䲾��
			allMonster[i]->SetRL(0);

		//GameSystem::GetGameObjectWithTag("Player")->SetX(GameSystem::GetGameObjectWithTag("Player")->GetX() - 10);
	}
}