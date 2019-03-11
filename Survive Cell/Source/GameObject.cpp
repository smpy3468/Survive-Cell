#include "StdAfx.h"
#include "GameObject.h"
#include "Map.h"


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
	objectPic.SetTopLeft(x - this->width / 2 - Map::GetSX(), y - this->height / 2 - Map::GetSY());
}

void GameObject::ShowBitMap()
{
	objectPic.ShowBitmap();
}
