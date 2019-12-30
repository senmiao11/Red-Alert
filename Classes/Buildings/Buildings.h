#ifndef __Buildings_H_
#define __Buildings_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Bar.h"
USING_NS_CC;


////////////////////////////////////
//�������Ѫ�����ٺʹݻٷ���������
////////////////////////////////////


class Buildings :public Sprite
{
	friend class Bar;
public:
	friend class GameScene;

	Buildings(BuildingTypes buildingType);        //ͨ��ö�������ж������ʲô������
	static Buildings *creatWithBuildingTypes(BuildingTypes buildingType);

private:
	CC_SYNTHESIZE(BuildingTypes, buildingtype, BuildingType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);

	//Ѫ��
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();
};




#endif // !__Buildings_H_



