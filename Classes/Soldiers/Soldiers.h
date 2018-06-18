#ifndef __Soldiers_H_
#define __Soldiers_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Buildings/Buildings.h"
#include"Bar.h"
#include"Astar.h"
USING_NS_CC;

class Attackeffect :public ParticleFire
{
public:
	bool init();
	CREATE_FUNC(Attackeffect);

	void setAtkPath(Vec2 from, Vec2 to);

private:
	Vec2 From;
	Vec2 To;
	Vec2 moveFromTo;
	int moveSpeed = 3;
	void updateAtkEffect(float dt);
};

class Explosioneffect :public ParticleFire
{
public:
	bool init();
	CREATE_FUNC(Explosioneffect);
private:
	void updateRemove(float dt);
};

class Soldiers :public Sprite
{
	friend class Buildings;
	friend class Bar;
	friend class Astar;
	friend class Apoint;
public:
	Soldiers(SoldierTypes soldierType);        //通过枚举类来判段需产生什么建筑物
	//~Soldiers();
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);
	
	void update(float dt);
private:
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
	CC_SYNTHESIZE(float, speed, Speed);
	CC_SYNTHESIZE(int, power, Power);
	CC_SYNTHESIZE(int, atkRadius, AtkRadius);
	
private:
	CC_SYNTHESIZE(bool, ifAttack, IfAttack);
	int attackCD = 30;
	CC_SYNTHESIZE(Soldiers *, sEnemy, SoldierEnemy);
	CC_SYNTHESIZE(Buildings *, bEnemy, BuildingEnemy);
	CC_SYNTHESIZE_RETAIN(Soldiers *, attacker, Attacker);
	//CC_SYNTHESIZE(int, attackerPower, AttackerPower);
public:
	void findEnemy();
	void attack();


	//移动相关方法
	vector<Vec2> moveToPath;
	void soldierAutoMove();

	//血条
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();
};


#endif //!__Soldiers_H_


