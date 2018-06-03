#ifndef __Buildings_H_
#define __Buildings_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"

USING_NS_CC;


////////////////////////////////////
//建筑物的血量减少和摧毁方法待添加
////////////////////////////////////


class Buildings :public Sprite
{
public:
	Buildings(BuildingTypes buildingType);        //通过枚举类来判段需产生什么建筑物

	static Buildings *creatWithBuildingTypes(BuildingTypes buildingType);

private:
	CC_SYNTHESIZE(BuildingTypes, buildingtype, BuildingType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, if_move, ifMove);

	//建筑物监听器
	static EventListenerTouchOneByOne *touchBuildingListener;
	static EventDispatcher *eventDispatcher;
};




#endif // !__Buildings_H_



