#ifndef __Buildings_H_
#define __Buildings_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Soldiers/Soldiers.h"
#include"Bar.h"
USING_NS_CC;


////////////////////////////////////
//建筑物的血量减少和摧毁方法待添加
////////////////////////////////////


class Buildings :public Sprite
{
	friend class Soldiers;
	friend class Bar;
public:
	Buildings(BuildingTypes buildingType);        //通过枚举类来判段需产生什么建筑物
	//~Buildings();

	static Buildings *creatWithBuildingTypes(BuildingTypes buildingType);
	void update(float dt);
private:
	CC_SYNTHESIZE(BuildingTypes, buildingtype, BuildingType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);

	//CC_SYNTHESIZE(Soldiers *, attacker, Attacker);

	//血条
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();
};




#endif // !__Buildings_H_



