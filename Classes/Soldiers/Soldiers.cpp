#include"Soldiers.h"

EventListenerTouchOneByOne * Soldiers::touchSoldierListener;
EventDispatcher * Soldiers::eventDispatcher;

Soldiers::Soldiers(SoldierTypes soldierType)
{
	this->soldiertype = soldierType;
	this->health = 0;
	this->price = 0;
}

Soldiers * Soldiers::createWithSoldierTypes(SoldierTypes soldierType)
{
	Soldiers *soldier = new Soldiers(soldierType);
	const char *soldierName = "soldiername";
	switch (soldierType)
	{
		case START_MINER:
			soldierName = MINER;
			soldier->health = MINER_HEALTH;
			break;
	    /*´ýÌí¼Ó*/

	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
		touchSoldierListener = EventListenerTouchOneByOne::create();
		//touchSoldierListener->setSwallowTouches(true);
		touchSoldierListener->onTouchBegan = [&](Touch *touch, Event *event)
		{
			return true;
		};
		touchSoldierListener->onTouchEnded = [&](Touch *touch, Event *event)
		{
			auto target = (Sprite*)event->getCurrentTarget();
			auto pos = touch->getLocation();
			//pos = Director::getInstance()->convertToUI(pos);
			MoveTo *soldierMove = MoveTo::create(1.0f, pos);
			target->runAction(soldierMove);
			return true;
		};

		eventDispatcher = Director::getInstance()->getEventDispatcher();
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchSoldierListener, soldier);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

void Soldiers::OnTouchBegan(Touch *touch, Event *unused_event)
{

}