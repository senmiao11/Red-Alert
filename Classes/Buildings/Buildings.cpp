#include"Buildings.h"

EventListenerTouchOneByOne * Buildings::touchBuildingListener;
EventDispatcher * Buildings::eventDispatcher;

Buildings::Buildings(BuildingTypes buildingType)
{
	this->buildingtype = buildingType;
	this->health = 0;
	this->price = 0;
	this->if_move = CANNOT_MOVE;
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
		break;
	case CASERN:
		buildingName = BASE;//ÔÝ´ú±øÓªÍ¼Æ¬
		building->health = CASERN_HEALTH;
		building->price = CASERN_PRICE;
		building->if_move = CAN_MOVE;
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
			log("touch to building");
			auto target = static_cast<Buildings *>(event->getCurrentTarget());
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
			auto target = static_cast<Buildings *>(event->getCurrentTarget());
			target->setPosition(target->getPosition() + touch->getDelta());
		};
		touchBuildingListener->onTouchEnded = [](Touch *touch, Event *event)
		{
			log("touch to building end");
			auto target = static_cast<Buildings *>(event->getCurrentTarget());
			target->setifMove(CANNOT_MOVE);
		};
		eventDispatcher = Director::getInstance()->getEventDispatcher();
		eventDispatcher->addEventListenerWithSceneGraphPriority(touchBuildingListener, building);

		return building;
	}
	CC_SAFE_DELETE(building);
	return nullptr;
}