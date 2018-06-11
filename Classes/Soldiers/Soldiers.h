#ifndef __Soldiers_H_
#define __Soldiers_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Bar.h"
USING_NS_CC;

class Soldiers :public Sprite
{
	friend class Bar;
public:
	Soldiers(SoldierTypes soldierType);        //通过枚举类来判段需产生什么建筑物
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);
	

private:
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
	CC_SYNTHESIZE(int, speed, Speed);
	//兵种监听器
	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher * eventDispatcher;

	//血条
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();
};


#endif //!__Soldiers_H_


