#pragma once

//GameObject
//遊戲物件
//場上所有物件的Base Class

#include "StdAfx.h"
#include <string>
using namespace std;

class GameObject
{
public:
	GameObject();
	string GetTag();
	void SetTag(string tag);
protected:
	string tag;//物件標籤
};