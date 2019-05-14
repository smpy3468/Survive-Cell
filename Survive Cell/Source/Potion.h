#pragma once

//Potion
//���W���ɫ~�D��
//�~��Item

#include "GameSystem.h"
#include "Item.h"
#include "Player.h"

class Potion :public Item
{
public:
	Potion();
	~Potion();
	Potion(string tag, int x, int y, int width, int height);

	void Picked()override;//�Q�ߨ�

private:
	virtual void Dead()override;

	int recoverHP;//HP�^�_�q
};