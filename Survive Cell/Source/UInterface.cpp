
#include "StdAfx.h"
#include"UInterface.h"

UInterface::UInterface() {
	this->tag = "UInterface";
	x = 0;
	y = 0;
	width = 32;
	height = 32;
}

UInterface::~UInterface()
{
	for (unsigned int i = 0; i < ani.size(); i++)
	{
		delete ani[i];
	}
	ani.clear();
}

UInterface::UInterface(string tag, int x, int y, int width, int height){
	this->tag = "UInterface";
	this->x = x;
	this->y = y;
	this->width=width;
	this->height=height;
}
//-----------------------SET-----------------------------//
void UInterface::SetX(int x) {
	this->x = x;
}
void UInterface::SetY(int y) {
	this->y = y;
}
void UInterface::SetWidth(int width) {
	this->width = width;
}
void UInterface::SetHeight(int height) {
	this->height = height;
}


//-----------------GET----------------------------------//
string UInterface::GetTag() {
	return this->tag;
}

int UInterface::GetX() {
	return this->x;
}

int UInterface::GetY() {
	return this->y;
}

int UInterface::GetWidth() {
	return this->width;
}
//-----------------other-------------------------------//
int UInterface::GetHeight() {
	return this->height;
}

void UInterface::ShowBitMap() {
}

//-----------------PROTECTED-----------------------------//
void UInterface::AddAniBitMaps(char * pic[], int aniType, int picCount)
{
	for (int i = 0; i < picCount; i++)
	{
		AddAniBitMap(pic[i], aniType);
	}
}

void UInterface::AddAniBitMap(char* pic, int aniType)
{
	while ((int)ani.size() <= aniType)//vector的大小不夠大
		ani.push_back(new CAnimation);//增加大小

	ani[aniType]->AddBitmap(pic, RGB(255, 255, 255));
}

void UInterface::LoadAni(){}

void UInterface::LoadBitMap(int pictureID) {
	UIpicture.LoadBitmap(pictureID, RGB(255, 255, 255));
}

void UInterface::LoadBitMap(char* pictureAddress) {
	UIpicture.LoadBitmap(pictureAddress, RGB(255, 255, 255));
}
