#include"Soldiers.h"

EventListenerTouchOneByOne * Soldiers::touchSoldierListener;
EventDispatcher * Soldiers::eventDispatcher;


Soldiers::Soldiers(SoldierTypes soldierType)
{
	this->soldiertype = soldierType;
	this->health = 0;
	this->price = 0;
	this->ifselect = false;
}

Soldiers * Soldiers::createWithSoldierTypes(SoldierTypes soldierType)
{
	Soldiers *soldier = new Soldiers(soldierType);
	const char *soldierName = "soldiername";
	switch (soldierType) {
	case MINER:
		soldierName = MINER_IMAGE;
		soldier->setHealth(MINER_HEALTH);
		soldier->price = MINER_PRICE;
		soldier->ifselect = false;
		break;
	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
		touchSoldierListener = EventListenerTouchOneByOne::create();
		touchSoldierListener->setSwallowTouches(true);
		touchSoldierListener->onTouchBegan = [](Touch *touch, Event *event)

		{
			return true;
		};

		touchSoldierListener->onTouchEnded = [](Touch *touch, Event *event)
		{
			auto origin = Director::getInstance()->getVisibleOrigin();
			auto target = (Sprite*)event->getCurrentTarget();
			auto pos = GameScene::gettiledMap()->convertTouchToNodeSpace(touch);
			//auto pos = GameScene::gettiledMap()->convertToNodeSpace(touch->getLocation());
			//auto pos = touch->getLocation();
			//Vec2 pos = target->convertToNodeSpace(touch->getLocation());
			//pos = Director::getInstance()->convertToUI(pos);
			MoveTo *soldierMove = MoveTo::create(1.0f, pos);
			target->runAction(soldierMove);
		};
		eventDispatcher = Director::getInstance()->getEventDispatcher();
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchSoldierListener, soldier);

		return soldier;

	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}