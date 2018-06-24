
#ifndef __Soldiers_H_
#define __Soldiers_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include"GameScene.h"
#include"Bar.h"
#include"Astar.h"
#include"network/GameManager.h"
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
	friend class Bar;
	friend class Astar;
	friend class Apoint;
	friend class Buildings;
	friend class GameManager;
public:
	Soldiers(SoldierTypes soldierType);        //通过枚举类来判段需产生什么建筑物
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType, char *soldierName);
	void update(float dt);
	void findEnemy();
	void attack();
	vector<Soldiers *> &getAttackers();
	void remove();

	//移动相关方法
	vector<Vec2> moveToPath;
	void soldierAutoMove();
	void minerAutoMoveInMap_1();
	void minerAutoMoveInMap_2();
	void minerRemoveAndAddMoney();
	//血条
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();

private:
	int attackCD = 60;
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
	CC_SYNTHESIZE(float, speed, Speed);
	CC_SYNTHESIZE(int, player_id, playerID);
	CC_SYNTHESIZE(int, id, ID);
	CC_SYNTHESIZE(int, power, Power);
	CC_SYNTHESIZE(int, atkRadius, AtkRadius);
	CC_SYNTHESIZE(bool, ifAttack, IfAttack);
	CC_SYNTHESIZE(Soldiers *, sEnemy, SoldierEnemy);
	CC_SYNTHESIZE(Buildings *, bEnemy, BuildingEnemy);
	CC_SYNTHESIZE(bool, ifmoving, ifMoving);
	vector<Soldiers *> attackers;
	//CC_SYNTHESIZE_RETAIN(Soldiers *, attacker, Attacker);

};


#endif    //!__Soldiers_H_


