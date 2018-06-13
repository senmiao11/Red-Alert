#include"Buildings.h"


Buildings::Buildings(BuildingTypes buildingType)
{
	this->buildingtype = buildingType;
	this->health = 0;
	this->price = 0;
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
		building->maxHealth = BASE_HEALTH;
		break;
	case START_CASERN:
		buildingName = CASERN;
		building->health = CASERN_HEALTH;
		building->price = CASERN_PRICE;
		building->maxHealth = CASERN_HEALTH;
		break;
	case START_ELECTRICSTATION:
		buildingName = ELECTRICSTATION;
		building->health = ELECTRICSTATION_HEALTH;
		building->price = ELECTRICSTATION_PRICE;
		building->maxHealth = ELECTRICSTATION_HEALTH;
		break;
	case START_TANKFACTORY:
		buildingName = TANKFACTORY;
		building->health = TANKFACTORY_HEALTH;
		building->price = TANKFACTORY_PRICE;
		building->maxHealth = TANKFACTORY_HEALTH;
		break;
	case START_OREYARD:
		buildingName = OREYARD;
		building->health = OREYARD_HEALTH;
		building->price = OREYARD_PRICE;
		building->maxHealth = OREYARD_HEALTH;
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
		break;
	}

	if (building && building->initWithFile(buildingName))
	{
		//½¨ÖþÎï¼àÌýÆ÷
		building->autorelease();
		auto tiledmap = GameScene::gettiledMap();
		auto group = tiledmap->getObjectGroup("Buildings");
		ValueMap buildobj;
		switch (building->getBuildingType())
		{
<<<<<<< HEAD
		case START_BASE:
			buildobj = group->getObject("base1");
			break;
		case START_CASERN:
			buildobj = group->getObject("casern1");
			break;
		case START_ELECTRICSTATION:
			buildobj = group->getObject("electricStation1");
			break;
		case START_TANKFACTORY:
			buildobj = group->getObject("tankFactory1");
			break;
		case START_OREYARD:
			buildobj = group->getObject("oreyard1");
			break;
		}
		float x = buildobj["width"].asFloat();
		float y = buildobj["height"].asFloat();
		auto body = PhysicsBody::createBox(Size(x, y));
=======
			log("touch to building move");
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
			log("building move");
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
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
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
	hpBar->setPosition(Vec2(0, bar_height));
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