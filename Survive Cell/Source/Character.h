#pragma once

//Character
//角色
//繼承GameObject

#include <vector>
#include "GameObject.h"
#include "Buff.h"

class Character :public GameObject
{
public:
	Character();
	Character::Character(string tag, int x, int y, int width, int height, int pictureID);

	void SetMaxHP(int maxHp);//設定最大血量
	void SetHP(int hp);//設定目前血量
	void SetOriginMoveSpeed(int originMoveSpeed);//設定原始移動速度
	void SetMoveSpeed(int moveSpeed);//設定目前移動速度
	void SetOriginAttackDamage(int originAttack);//設定原始攻擊力
	void SetAttackDamage(int attack);//設定目前攻擊力
	void SetOriginAttackSpeed(int originAttackSpeed);//設定原始攻擊速度
	void SetAttackSpeed(int attackSpeed);//設定目前攻擊速度
	void SetOriginAttackRange(int originAttackRange);//設定原始攻擊範圍
	void SetAttackRange(int attackRange);//設定目前攻擊範圍
	void SetIsDead(bool isDead);//設定是否死亡

	int GetMaxHP();//取得最大血量
	int GetHP();//取得目前血量
	int GetOriginMoveSpeed();//取得原始移動速度
	int GetMoveSpeed();//取得目前移動速度
	int GetOriginAttackDamage();//取得原始攻擊力
	int GetAttackDamage();//取得目前攻擊力
	int GetOriginAttackRange();//取得原始攻擊範圍
	int GetAttackRange();//取得攻擊範圍
	bool IsDead();//確認是否死亡

	void SetBitMapPosition()override;//設定動畫位置

	void DecreaseHP(int dhp);//扣血
	void IncreaseHP(int ihp);//加血
	virtual void Attack() = 0;//攻擊
	virtual void Move(int dx, int dy) = 0;

protected:
	int maxHP, HP;//最大血量、目前血量
	int originMoveSpeed, moveSpeed;//原始移動速度、目前移動速度
	int originAttackDamage, attackDamage;//原始攻擊力、目前攻擊力
	int	originAttackSpeed, attackSpeed;//原始攻擊速度、目前攻擊速度
	int originAttackRange, attackRange;//原始攻擊範圍、目前攻擊範圍

	vector<Buff> buff;//套用中的BUFF
	bool isDead;//是否死亡
	void Dead()override;//死亡時呼叫

	vector<CAnimation*> ani;//動畫
	virtual void LoadAni(); //載入動畫
	void AddAniBitMaps(char* pic[], int aniType, int picCount);//增加多張動畫圖片
	void AddAniBitMap(char* pic, int aniType);//增加動畫圖片
};