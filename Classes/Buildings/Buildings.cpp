#include"Buildings.h"


Buildings::Buildings(BuildingTypes buildingType)
{
	this->buildingtype = buildingType;
	this->health = 0;
	this->price = 0;
	this->maxHealth = 0;
	//this->attacker = NULL;
}

/*Buildings::~Buildings()
{
	CC_SAFE_RELEASE(attacker);
}*/

Buildings * Buildings::creatWithBuildingTypes(BuildingTypes buildingType)
{
	Buildings *building = new Buildings(buildingType);
	const char *buildingName = "buildingname";
	switch (buildingType) {
	case START_BASE:
		buildingName = BASE;
		building->health = BASE_HEALTH;
		building->maxHealth = BASE_HEALTH;
		//building->attacker = NULL;
		break;
	case START_CASERN:
		buildingName = CASERN;
		building->health = CASERN_HEALTH;
		building->price = CASERN_PRICE;
		building->maxHealth = CASERN_HEALTH;
		//building->attacker = NULL;
		break;
	case START_ELECTRICSTATION:
		buildingName = ELECTRICSTATION;
		building->health = ELECTRICSTATION_HEALTH;
		building->price = ELECTRICSTATION_PRICE;
		building->maxHealth = ELECTRICSTATION_HEALTH;
		//building->attacker = NULL;
		break;
	case START_TANKFACTORY:
		buildingName = TANKFACTORY;
		building->health = TANKFACTORY_HEALTH;
		building->price = TANKFACTORY_PRICE;
		building->maxHealth = TANKFACTORY_HEALTH;
		//building->attacker = NULL;
		break;
	case START_OREYARD:
		buildingName = OREYARD;
		building->health = OREYARD_HEALTH;
		building->price = OREYARD_PRICE;
		building->maxHealth = OREYARD_HEALTH;
<<<<<<< HEAD
		//building->attacker = NULL;
=======
>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151
		break;
	}

	if (building && building->initWithFile(buildingName))
	{
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
=======
>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151
		case START_CASERN:
		{
			buildobj = group->getObject("casern1");
			float x1 = buildobj["x"].asFloat();
			float y1 = buildobj["y"].asFloat();
			float width1 = buildobj["width"].asFloat();
			float height1 = buildobj["height"].asFloat();
			PhysicsBody * phy1 = PhysicsBody::createBox(Size(width1, height1));
			phy1->setDynamic(false);
			Sprite * sp1 = Sprite::create();
			sp1->setPosition(Vec2(x1, y1));
			sp1->setAnchorPoint(ccp(0, 0));
			sp1->setContentSize(Size(width1, height1));
			sp1->setPhysicsBody(phy1);
			tiledmap->addChild(sp1);
			break;
		}
		case START_ELECTRICSTATION:
		{
			buildobj = group->getObject("electricStation1");
			float x2 = buildobj["x"].asFloat();
			float y2 = buildobj["y"].asFloat();
			float width2 = buildobj["width"].asFloat();
			float height2 = buildobj["height"].asFloat();
			PhysicsBody * phy2 = PhysicsBody::createBox(Size(width2, height2));
			phy2->setDynamic(false);
			Sprite * sp2 = Sprite::create();
			sp2->setPosition(Vec2(x2, y2));
			sp2->setAnchorPoint(ccp(0, 0));
			sp2->setContentSize(Size(width2, height2));
			sp2->setPhysicsBody(phy2);
			tiledmap->addChild(sp2);
			break;
		}
		case START_TANKFACTORY:
		{
			buildobj = group->getObject("tankFactory1");
			float x3 = buildobj["x"].asFloat();
			float y3 = buildobj["y"].asFloat();
			float width3 = buildobj["width"].asFloat();
			float height3 = buildobj["height"].asFloat();
			PhysicsBody * phy3 = PhysicsBody::createBox(Size(width3, height3));
			phy3->setDynamic(false);
			Sprite * sp3 = Sprite::create();
			sp3->setPosition(Vec2(x3, y3));
			sp3->setAnchorPoint(ccp(0, 0));
			sp3->setContentSize(Size(width3, height3));
			sp3->setPhysicsBody(phy3);
			tiledmap->addChild(sp3);
			break;
		}
		case START_OREYARD:
		{
			buildobj = group->getObject("oreyard1");
			float x4 = buildobj["x"].asFloat();
			float y4 = buildobj["y"].asFloat();
			float width4 = buildobj["width"].asFloat();
			float height4 = buildobj["height"].asFloat();
			PhysicsBody * phy4 = PhysicsBody::createBox(Size(width4, height4));
			phy4->setDynamic(false);
			Sprite * sp4 = Sprite::create();
			sp4->setPosition(Vec2(x4, y4));
			sp4->setAnchorPoint(ccp(0, 0));
			sp4->setContentSize(Size(width4, height4));
			sp4->setPhysicsBody(phy4);
			tiledmap->addChild(sp4);
			break;
		}
<<<<<<< HEAD
		float x = buildobj["width"].asFloat();
		float y = buildobj["height"].asFloat();
		auto body = PhysicsBody::createBox(Size(x, y));
		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x01);
		body->setCollisionBitmask(0x02);
		building->setPhysicsBody(body);
=======
		}

>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151

		return building;
	}
	CC_SAFE_DELETE(building);
	return nullptr;
}

void Buildings::update(float dt)
{
	if (getcurrentHealth() <= 0)
	{
		auto explosion = Explosioneffect::create();
		explosion->setPosition(getPosition());
		GameScene::gettiledMap()->addChild(explosion, 15);
		//getAttacker()->setIfAttack(false);
		auto it = find(GameScene::buildingSprites.begin(), GameScene::buildingSprites.end(), this);
		if (it != GameScene::buildingSprites.end())
		{
			GameScene::buildingSprites.erase(it);
		}
		removeFromParent();
		return;
	}
	/*if (getAttacker())
	{
		displayHpBar();
		setcurrentHealth(getcurrentHealth() - getAttacker()->getPower());
	}*/
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