#include "StdAfx.h"
#include "GameObject.h"
#include "Map.h"
#include "Monster.h"


GameObject::GameObject()
{
	tag = "GameObject";
	x = 0;
	y = 0;
	width = 10;
	height = 10;
}

GameObject::GameObject(string tag, int x, int y, int width, int height, int pictureID)
{
	this->tag = tag;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->pictureID = pictureID;
	this->LoadBitMap(pictureID);//¸ü¤J¹Ï¤ù
}

string GameObject::GetTag()
{
	return tag;
}

int GameObject::GetX()
{
	return this->x;
}

int GameObject::GetY()
{
	return this->y;
}

void GameObject::SetTag(string tag)
{
	this->tag = tag;
}

void GameObject::SetX(int x)
{
	this->x = x;
}

void GameObject::SetY(int y)
{
	this->y = y;
}

void GameObject::SetWidth(int width)
{
	this->width = width;
}

void GameObject::SetHeight(int height)
{
	this->height = height;
}

int GameObject::GetWidth()
{
	return width;
}

int GameObject::GetHeight()
{
	return height;
}

void GameObject::LoadBitMap(char* pictureAddress)
{
	objectPic.LoadBitmap(pictureAddress);
}

void GameObject::LoadBitMap(int pictureID)
{
	objectPic.LoadBitmap(pictureID);
}

void GameObject::SetBitMapPosition()
{
	objectPic.SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void GameObject::ShowBitMap()
{
	objectPic.ShowBitmap();
}

bool GameObject::IsAnthorObjectInRange(GameObject* object) {
	const int RIGHT_EDGE = x + width, LEFT_EDGE = x - width,
		UP_EDGE = y - height, DOWN_EDGE = y - height;

	const int OB_X = object->GetX(), OB_Y = object->GetY(), OB_WIDTH = object->GetWidth(), OB_HEIGHT = object->GetHeight();
	const int OB_RIGHT_EDGE = OB_X - OB_WIDTH, OB_LEFT_EDGE = OB_X + OB_WIDTH,
		OB_UP_EDGE = OB_Y - OB_HEIGHT, OB_DOWN_EDGE = OB_Y + OB_HEIGHT;

	if (OB_LEFT_EDGE < RIGHT_EDGE && OB_LEFT_EDGE > LEFT_EDGE)
		return true;
	else if (OB_RIGHT_EDGE < RIGHT_EDGE && OB_RIGHT_EDGE > LEFT_EDGE)
		return true;
	else if (OB_DOWN_EDGE > UP_EDGE && OB_DOWN_EDGE < DOWN_EDGE)
		return true;
	else if (OB_UP_EDGE < DOWN_EDGE && OB_UP_EDGE > UP_EDGE)
		return true;
	return false;
}
