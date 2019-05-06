#pragma once
#include "GameObject.h"
#include "GameSystem.h"
class Goal:public GameObject
{
public:
	Goal(string tag, int x, int y, int width, int height);
	~Goal();
	void Picked();
private:
};