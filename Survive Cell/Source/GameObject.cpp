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
	layer = 0;
}

GameObject::~GameObject()
{
	
}

GameObject::GameObject(string tag, int x, int y, int width, int height, int pictureID)
{
	this->tag = tag;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->pictureID = pictureID;
	this->LoadBitMap(pictureID);//載入圖片
}

GameObject::GameObject(string tag, int x, int y, int width, int height)  //沒有pictureID的Contructor
{
	this->tag = tag;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
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

int GameObject::GetLayer()
{
	return layer;
}

void GameObject::Act()
{

}

void GameObject::LoadBitMap(char* pictureAddress)
{
	objectPic.LoadBitmap(pictureAddress, RGB(255, 255, 255));
}

void GameObject::LoadBitMap(int pictureID)
{
	objectPic.LoadBitmap(pictureID, RGB(255, 255, 255));
}

void GameObject::SetBitMapPosition()
{
	objectPic.SetTopLeft(x - Map::GetSX(), y - Map::GetSY());
}

void GameObject::ShowBitMap()
{
	objectPic.ShowBitmap();
}

void GameObject::Dead()
{
	GameSystem::DeleteGameObject(this);//刪除此物件
}