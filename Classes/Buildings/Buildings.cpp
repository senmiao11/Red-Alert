#include"Buildings.h"

EventListenerTouchOneByOne * Buildings::touchBuildingListener;
EventDispatcher * Buildings::eventDispatcher;

Buildings::Buildings(BuildingTypes buildingType)
{
	this->buildingtype = buildingType;
	this->health = 0;
	this->price = 0;
	this->if_move = CANNOT_MOVE;
	this->maxHealth = 0;
}

Buildings * Buildings::creatWithBuildingTypes(BuildingTypes buildingType)
{
	Buildings *building = new Buildings(buildingType);
	const char *buildingName = "buildingname";
	switch (buildingType) {
	case START_BASE:
		buildingName = BASE;
		building->health = BASE_HEALTH;
		building->if_move = CANNOT_MOVE;
		building->maxHealth = BASE_HEALTH;
		break;
	case START_CASERN:
		buildingName = CASERN;
		building->health = CASERN_HEALTH;
		building->price = CASERN_PRICE;
		building->if_move = CAN_MOVE;
		building->maxHealth = CASERN_HEALTH;
		break;
	case START_ELECTRICSTATION:
		buildingName = ELECTRICSTATION;
		building->health = ELECTRICSTATION_HEALTH;
		building->price = ELECTRICSTATION_PRICE;
		building->if_move = CAN_MOVE;
		building->maxHealth = ELECTRICSTATION_HEALTH;
		break;
	case START_TANKFACTORY:
		buildingName = TANKFACTORY;
		building->health = TANKFACTORY_HEALTH;
		building->price = TANKFACTORY_PRICE;
		building->if_move = CAN_MOVE;
		building->maxHealth = TANKFACTORY_HEALTH;
		break;
	case START_OREYARD:
		buildingName = OREYARD;
		building->health = OREYARD_HEALTH;
		building->price = OREYARD_PRICE;
		building->if_move = CAN_MOVE;
		building->maxHealth = OREYARD_HEALTH;
<<<<<<< HEAD
=======
		break;
	case START_TANKFACTORY:
		buildingName = TANKFACTORY;
		building->health = TANKFACTORY_HEALTH;
		building->price = TANKFACTORY_PRICE;
		building->if_move = CAN_MOVE;
		break;
	case START_OREYARD:
		buildingName = OREYARD;
		building->health = OREYARD_HEALTH;
		building->price = OREYARD_PRICE;
		building->if_move = CAN_MOVE;
>>>>>>> xiaorui
		break;
	}

	if (building && building->initWithFile(buildingName))
	{
		//½¨ÖþÎï¼àÌýÆ÷
		building->autorelease();
		touchBuildingListener = EventListenerTouchOneByOne::create();
		touchBuildingListener->setSwallowTouches(true);
		touchBuildingListener->onTouchBegan = [](Touch *touch, Event *event)
		{
<<<<<<< HEAD
			log("touch to building");
=======
			log("touch to building move");
>>>>>>> xiaorui
			auto target = dynamic_cast<Buildings *>(event->getCurrentTarget());
			if (!target->getifMove())
			{
				return false;
			}
			Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
			Size s = target->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);
			if (rect.containsPoint(locationInNode))
			{
				return true;
			}
			return false;
		};
		touchBuildingListener->onTouchMoved = [](Touch *touch, Event *event)
		{
<<<<<<< HEAD
			log("touch to building move");
=======
			log("building move");
>>>>>>> xiaorui
			auto target = dynamic_cast<Buildings *>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
		};
		touchBuildingListener->onTouchEnded = [](Touch *touch, Event *event)
		{
			log("touch to building end");
			auto target = dynamic_cast<Buildings *>(event->getCurrentTarget());
			if (GameScene::getIfBuild()->getTag())
			{
				target->setifMove(CAN_MOVE);
			}
			else
			{
				target->setifMove(CANNOT_MOVE);
			}
		};
		eventDispatcher = Director::getInstance()->getEventDispatcher();
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchBuildingListener, building);

		auto body = PhysicsBody::createBox((building->getContentSize()) * 0.75);
		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x01);
		body->setCollisionBitmask(0x02);
		building->setPhysicsBody(body);

		return building;
	}
	CC_SAFE_DELETE(building);
	return nullptr;
}

void Buildings::createBar()
{
	hpBar = Bar::create();
	float bar_width = this->getContentSize().width;
	float bar_height = this->getContentSize().height;
	hpBar->setLength(bar_width);
	hpBar->setHeight(4);
	hpBar->setVisible(false);
	addChild(hpBar, 20);
	hpBar->setPosition(Point(bar_width - 170, bar_height + 5));
}

void Buildings::displayHpBar()
{
	if (hpBar)
	{
		hpBar->schedule(schedule_selector(Bar::update));
		hpBar->setVisible(true);
	}
}

void Buildings::hideHpBar()
{
	if (hpBar)
	{
		hpBar->unschedule(schedule_selector(Bar::update));
		hpBar->setVisible(false);
	}
}