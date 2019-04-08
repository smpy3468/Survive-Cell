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
	Character::Character(string tag, int x, int y, int width, int height); //No PictureID 的 Contructor

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
	void SetDefense(int defense);
	void SetIsDead(bool isDead);//設定是否死亡

	int GetMaxHP();//取得最大血量
	int GetHP();//取得目前血量
	int GetOriginMoveSpeed();//取得原始移動速度
	int GetMoveSpeed();//取得目前移動速度
	int GetOriginAttackDamage();//取得原始攻擊力
	int GetAttackDamage();//取得目前攻擊力
	int GetOriginAttackSpeed();//取得原始攻擊速度
	int GetAttackSpeed();//取得攻擊速度
	int GetOriginAttackRange();//取得原始攻擊範圍
	int GetAttackRange();//取得攻擊範圍
	int GetDefense();
	bool IsDead();//確認是否死亡

	void SetBitMapPosition()override;//設定動畫位置

	void DecreaseHP(int dhp);//扣血
	void IncreaseHP(int ihp);//加血
	virtual void Attack() = 0;//攻擊
	virtual void Move(int dx, int dy) = 0;//移動

protected:
	int maxHP, HP;//最大血量、目前血量
	int originMoveSpeed, moveSpeed;//原始移動速度、目前移動速度
	int originAttackDamage, attackDamage;//原始攻擊力、目前攻擊力
	int	originAttackSpeed, attackSpeed;//原始攻擊速度、目前攻擊速度
	int originAttackRange, attackRange;//原始攻擊範圍、目前攻擊範圍
	int originDefense, defense;//原始防禦力、目前防禦力

	bool isGetHit;//被擊

	vector<Buff> buff;//套用中的BUFF
	bool isDead;//是否死亡
	void Dead()override;//死亡時呼叫

	vector<CAnimation*> ani;//動畫
	virtual void LoadAni(); //載入動畫
	int aniSpeed = 10;//動畫播放速度
	void AddAniBitMaps(char* pic[], int aniType, int picCount, int aniSpeed=10);//增加多張動畫圖片
	void AddAniBitMap(char* pic, int aniType, int aniSpeed=10);//增加動畫圖片

	bool CanMoveLeft(int perDisplacement);//可以向左移動，perDisplacement:每次的位移量是多少
	bool CanMoveRight(int perDisplacement);//可以向右移動
	bool CanMoveUp(int perDisplacement);//可以向上移動
	bool CanMoveDown(int perDisplacement);//可以向下移動
};