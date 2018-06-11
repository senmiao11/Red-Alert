#ifndef __Soldiers_H_
#define __Soldiers_H_
#include"cocos2d.h"
#include<iostream>
#include"cocos2d.h"
#include"ConstUtil.h"
#include"GameScene.h"
#include"Bar.h"
<<<<<<< HEAD
=======

>>>>>>> xiaorui
USING_NS_CC;

class Soldiers :public Sprite
{
<<<<<<< HEAD
	friend class Bar;
public:
	Soldiers(SoldierTypes soldierType);        //Í¨¹ýÃ¶¾ÙÀàÀ´ÅÐ¶ÎÐè²úÉúÊ²Ã´½¨ÖþÎï
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);
	

=======

	friend class Bar;
public:
	Soldiers(SoldierTypes soldierType);        //é€šè¿‡æžšä¸¾ç±»æ¥åˆ¤æ®µéœ€äº§ç”Ÿä»€ä¹ˆå»ºç­‘ç‰©
	static Soldiers *createWithSoldierTypes(SoldierTypes soldierType);
	


>>>>>>> xiaorui
private:
	CC_SYNTHESIZE(SoldierTypes, soldiertype, SoldierType);
	CC_SYNTHESIZE(int, health, currentHealth);
	CC_SYNTHESIZE(int, price, Price);
	CC_SYNTHESIZE(bool, ifselect, ifSelect);
<<<<<<< HEAD
	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
	CC_SYNTHESIZE(int, speed, Speed);
	//±øÖÖ¼àÌýÆ÷
	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher * eventDispatcher;

	//ÑªÌõ
=======

	CC_SYNTHESIZE(int, maxHealth, MaxHealth);
	//å…µç§ç›‘å¬å™¨
	static EventListenerTouchOneByOne *touchSoldierListener;
	static EventDispatcher * eventDispatcher;

	//è¡€æ¡
>>>>>>> xiaorui
	Bar *hpBar = nullptr;
	void createBar();
	void displayHpBar();
	void hideHpBar();
<<<<<<< HEAD
=======

>>>>>>> xiaorui
};


#endif //!__Soldiers_H_


