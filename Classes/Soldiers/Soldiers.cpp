#include"Soldiers.h"

EventListenerTouchOneByOne * Soldiers::touchSoldierListener;
EventDispatcher * Soldiers::eventDispatcher;

Soldiers::Soldiers(SoldierTypes soldierType)
{
	this->soldiertype = soldierType;
	this->health = 0;
	this->price = 0;
	this->ifselect = SELECT_OFF;
}

Soldiers * Soldiers::createWithSoldierTypes(SoldierTypes soldierType)
{
	Soldiers *soldier = new Soldiers(soldierType);
	const char *soldierName = "soldiername";
	switch (soldierType)
	{
		case START_MINER:
		{
			soldierName = MINER;
			soldier->health = MINER_HEALTH;
			soldier->price = MINER_PRICE;
			soldier->ifselect = SELECT_OFF;
			break;
		}
		case START_POLICEMAN:
		{
			soldierName = POLICEMAN;
			soldier->health = POLICEMAN_HEALTH;
			soldier->price = POLICEMAN_PRICE;
			break;
		}
		case START_TANK:
		{
			soldierName = TANK;
			soldier->health = TANK_HEALTH;
			soldier->price = TANK_PRICE;
		}
			
	    /*待添加*/
		//已补充police.tank的health与price

	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
		touchSoldierListener = EventListenerTouchOneByOne::create();
		//touchSoldierListener->setSwallowTouches(true);
		touchSoldierListener->onTouchBegan = [&](Touch *touch, Event *event)
		{
			log("soldier");
			auto target = dynamic_cast<Soldiers *>(event->getCurrentTarget());
			if (!target->getifSelect())
			{
				return false;
			}
			return true;
		};
		touchSoldierListener->onTouchEnded = [](Touch *touch, Event *event)
		{
			auto origin = Director::getInstance()->getVisibleOrigin();
			//auto target = dynamic_cast<Soldiers *>(event->getCurrentTarget());
			Rect rect = GameScene::getSelectRect();
			for (auto &sprite : GameScene::gettiledMap()->getChildren())
			{
				if (!rect.containsPoint(sprite->getPosition()))
				{
					continue;
				}
				if (sprite->getTag() == GameSceneNodeTagSoldier)
				{
					auto target = dynamic_cast<Soldiers *>(sprite);
					if (target->getifSelect())
					{
						auto pos = GameScene::gettiledMap()->convertTouchToNodeSpace(touch);
						MoveTo *soldierMove = MoveTo::create(1.0f, pos);
						target->runAction(soldierMove);
						target->setifSelect(SELECT_OFF);
					}
				}
			}
		};

		eventDispatcher = Director::getInstance()->getEventDispatcher();
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchSoldierListener, soldier);

		auto body = PhysicsBody::createBox((soldier->getContentSize()));
		body->setCategoryBitmask(0x02);
		body->setContactTestBitmask(0x02);
		body->setCollisionBitmask(0x04);
		soldier->setPhysicsBody(body);

		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}
