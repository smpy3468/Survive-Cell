#pragma once

//Player
//���a
//�~��Character

#include "Character.h"

class Player :public Character
{
public:
	Player();
	Player(string tag, int x, int y, int width, int height, int pictureID);
	void Move(int dx, int dy)override;//���ʯS�w�Z��

	void SetIsMoveUp(bool isMoveUp);//�]�w�O�_�V�W����
	void SetIsMoveDown(bool isMoveDown);//�]�w�O�_�V�U����
	void SetIsMoveLeft(bool isMoveLeft);//�]�w�O�_�V������
	void SetIsMoveRight(bool isMoveRight);//�]�w�O�_�V�k����
	void Move();//���ʤ�V
private:
	bool isMoveUp;//�O�_�V�W����
	bool isMoveDown;//�O�_�V�U����
	bool isMoveLeft;//�O�_�V������
	bool isMoveRight;//�O�_�V�k����
};