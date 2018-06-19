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
	}
	building->initWithFile(buildingName);
	building->autorelease();
	return building;
	CC_SAFE_DELETE(building);
	return nullptr;
}

vector<Soldiers *> & Buildings::getAttackers()
{
	return attackers;
}

void Buildings::update(float dt)
{
	if (getcurrentHealth() <= 0 && buildingtype != START_BASE)
	{
		for (auto &atker : attackers)
		{
			atker->setBuildingEnemy(NULL);
		}
		remove();
	}
	else if (getcurrentHealth() <= 0 && buildingtype == START_BASE)
	{
		GameScene::gamemanager->deleteAll(GameScene::gamemanager->getPlayerID());
	}
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

void Buildings::remove()
{
	auto explosion = Explosioneffect::create();
	explosion->setPosition(getPosition());
	GameScene::gettiledMap()->addChild(explosion, 15);
	removeFromParent();
	for (auto elem : GameScene::gamemanager->bid_map)
	{
		if (elem.first  == id)
		{
			GameScene::gamemanager->bid_map.erase(elem.first);
			break;
		}
	}
}