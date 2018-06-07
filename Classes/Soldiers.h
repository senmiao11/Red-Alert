#ifndef __SOLDIERS_H_
#define __SOLDIERS_H_
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
USING_NS_CC;

class Soldiers :public Sprite
{
public:
	friend class GameScenne;

	Soldiers(SoldierTypes soldierType);
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);

private:
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, Health);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);

	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher *eventDispatcher;
};


#endif // !__SOLDIERS_H_
