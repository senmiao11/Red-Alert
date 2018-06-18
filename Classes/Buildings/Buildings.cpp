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
		//building->attacker = NULL;
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
		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x01);
		body->setCollisionBitmask(0x02);
		building->setPhysicsBody(body);

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