#pragma once
#include "StdAfx.h"

#include <string>
using namespace std;
#include "gamelib.h"
using namespace game_framework;
#include "resource.h"

class UInterface{
	public:
		UInterface();
		UInterface(string tag, int x, int y, int width, int height);

		void SetX(int x);													//�]�wUI��X�y��
		void SetY(int y);													//�]�wUI��Y�y��
		void SetWidth(int width);											//�]�wUI��width
		void SetHeight(int height);											//�]�wUI��Height

		string GetTag();													//�^��Tag
		int GetX();															//�^��UI��X�y��
		int GetY();															//�^��UI��Y�y��
		int GetWidth();													    //�^��UI��width
		int GetHeight();												    //�^��UI��height

		virtual void ShowBitMap();													//���UI�Ϥ�

	protected:
		CMovingBitmap UIpicture;											//�x�sUI�Ϥ�
		vector<string> UItexts;												//�x�sUI��r
		string tag;															//����tag
		int x, y;															//�y��	
		int width, height;													//�e�B��
		
		vector<CAnimation*> ani;											//�x�s�ʵe(�����n����)
		void AddAniBitMaps(char* pic[], int aniType, int picCount);			//�W�[�h�i�ʵe�Ϥ�(�����n����)
		void AddAniBitMap(char* pic, int aniType);							//�W�[�ʵe�Ϥ�(�����n����)
		void LoadBitMap(int pictureID);										//�[�JUI�Ϥ�-��k1
		void LoadBitMap(char* picAddress);									//�[�JUI�Ϥ�-��k
		
		virtual void LoadAni();												//���J�ʵe
		
};

