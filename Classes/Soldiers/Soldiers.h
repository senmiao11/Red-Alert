#ifndef __Soldiers_H_
#define __Soldiers_H_
#include"cocos2d.h"
#include<iostream>
#include<vector>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Bar.h"
<<<<<<< HEAD
#include"Findpath/Astar.h"
=======

>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
USING_NS_CC;
using namespace std;

class Soldiers :public Sprite
{

	friend class Bar;
	friend class Astar;
	friend class Apoint;
public:
	Soldiers(SoldierTypes soldierType);        //é€šè¿‡æšä¸¾ç±»æ¥åˆ¤æ®µéœ€äº§ç”Ÿä»€ä¹ˆå»ºç­‘ç‰©
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);
	


private:
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);

	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
<<<<<<< HEAD
	CC_SYNTHESIZE(int, speed, Speed);

	//±øÖÖ¼àÌıÆ÷
	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher * eventDispatcher;

	//ÏñËØ×ø±ê»»³ÉÍßÆ¬×ø±ê
	static Apoint turnToApoint(Vec2 vecPoint);

	//ÑªÌõ
=======
	//å…µç§ç›‘å¬å™¨
	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher * eventDispatcher;

	//è¡€æ¡
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();

};



#endif //!__Soldiers_H_


