#pragma once

//Item
//�D��
//�~��GameObject

#include "GameSystem.h"
#include "GameObject.h"

class Item :public GameObject
{
public:
	Item();
	Item(string tag, int x, int y, int width, int height, int pictureID);

	virtual void Picked();//�Q�߰_
private:
	void Dead()override;
};