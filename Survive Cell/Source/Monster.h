#pragma once

//Monster
//怪物
//繼承Character

#include "Character.h"
#include "GameSystem.h"
#include "Player.h"

class Monster :public Character
{
public:
	Monster();
	~Monster();
	Monster::Monster(string tag, int x, int y, int width, int height);
	void SetDefenseRange(int defenseRange);		//設定來回走動距離
	void SetRL(int rl);							//設定往左往右
	void SetdX();								//設定水平防守邊界
	void SetdY();								//設定垂直防守邊界
	void SetAttackField(int attackField);		//設定觸發跟隨的距離
	void SetAttackRange(int attackRange);		//設定攻擊距離;

	int GetDefenseRange();						//取得來回走動距離(從中間到兩邊)
	int GetRL();								//取得現在是往右移動還是往左移動
	int GetdX(int point);						//GetdX(0)取得左邊防守邊線, GetdX(1)取得右邊防守邊線
	int GetStatus();							//取得怪物現在狀態 STANDBY:0, LEFT:1, RIGTH:2, ATTACK = 3 


	//----------------移動相關---------------------//
	virtual void AutoMove(); //在防守區域內來回走動
	void Move(int dx, int dy)override;		   
	void Fall(int perDisplacement);			  //落下
	void Up();								  //怪物走上地形

	//----------------攻擊相關---------------------//
	bool IsInAttackField(int playerX, int playerY, int right_fix, int left_fix, int up_fix, int down_fix);   //Player是否在AttackField內, 是的話，衝向主角 
	bool IsPlayerInRange(Player* player, int right_fix, int left_fix, int up_fix, int down_fix);			//兩者的圖形是否有觸碰到
	int  PlaceRelativePlayer(Player* player); //怪物相對於腳色的位置
	
	virtual void Attack();//當Player進入防守區，攻擊他
	void PlayerAttack(int damage);

	//-----------------Animation------------------///
	void ShowBitMap()override;
	int GetAttackAniNumber();

	virtual void Act();   //組合各種動作(ISATTACK, AUTOMOVE, ATTACK)

protected:
	static const int LEFT = 1, RIGHT = 2, STANDBY = 0, ATTACK = 3, FALL = 4, ISATTACK=5; //怪物的狀態
	int status ;													   //現在狀態
	Player* player = GameSystem::GetGameObjectWithTag<Player>("Player");				//常用到就先記錄下來
	
	int fallDisplacement = 0;
	int currentAni = 0;                                            //現在執行得動畫  
	enum ANI
	{
		ANI_IDLE = 0,		   //原地
		ANI_LEFT,			   //左移動動畫
		ANI_RIGHT,			   //右移動動畫
		ANI_ATTACK_LEFT,	   //左邊攻擊動畫
		ANI_ATTACK_RIGHT,	   //右邊攻擊動畫
		ANI_ISATTACK_RIGHT,	   //被攻擊右邊動畫
		ANI_ISATTACK_LEFT		   //被攻擊左邊動畫
	};

	

private:

	int dX[2], dY[2];											   //0左1右、0上1下
	int rl;														   //現在往哪邊走	
	int defenseRange, attackField;								   //defenseRange 來回走動的範圍, attackfield衝過去攻擊主角的範圍
	

	void Dead()override;										   //死亡
};