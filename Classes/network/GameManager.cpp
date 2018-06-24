#include "GameManager.h"

bool GameManager::init()
{
	return true;
}

void GameManager::setTiledMap(TMXTiledMap* _tiledMap)
{
	tiledMap = _tiledMap;
}

void GameManager::setSocketClient(SocketClient* _socket_client)
{
	socket_client = _socket_client;
}

void GameManager::setPlayerID(int _player_id)
{
	player_id = _player_id;
	next_id = _player_id;
}

int GameManager::getPlayerID()
{
	return player_id;
}

void GameManager::setPlayernum(int _player_num)
{
	player_num = _player_num;
}

int GameManager::getPlayernum()
{
	return player_num;
}

int GameManager::getnextID()
{
	return next_id;
}

void GameManager::setMessageSet(GameMessageSet* _msgs)
{
	msgs = _msgs;
}

void GameManager::setGameScene(GameScene * _game_scene)
{
	game_scene = _game_scene;
}

void GameManager::setNotice(Notice * _notice)
{
	notice = _notice;
}

void GameManager::deleteAll(int _player_id)
{
	Map<int, Buildings*>::iterator elem;
	for (elem = bid_map.begin(); elem != bid_map.end(); )
	{
		if (bid_map.size() == 0)
		{
			break;
		}
		if (elem == bid_map.begin() && elem->first % 4 == _player_id%4)
		{
			Buildings * building = bid_map.at(elem->first);
			if (building)
			{
				building->remove();
				elem = bid_map.begin();
			}
		}
		else if (elem->first % 4 == _player_id%4)
		{
			Buildings * building = bid_map.at(elem->first);
			if (building)
			{
				elem++;
				building->remove();
			}
		}
		else
		{
			elem++;
		}
	}
	Map<int, Soldiers*>::iterator elems;
	for (elems = sid_map.begin(); elems != sid_map.end(); )
	{
		if (elems == sid_map.begin() && elems->first % 4 == _player_id % 4)
		{
			Soldiers *soldier = sid_map.at(elems->first);
			if (soldier)
			{
				soldier->stopAllActions();
				soldier->moveToPath.clear();
				soldier->remove();
				elems = sid_map.begin();
			}
		}
		else if (elems->first % 4 == _player_id % 4)
		{
			Soldiers *soldier = sid_map.at(elems->first);
			if (soldier)
			{
				elems++;
				soldier->stopAllActions();
				soldier->moveToPath.clear();
				soldier->remove();
			}
		}
		else
		{
			elems++;
		}
	}
}

void GameManager::produceBuildings(BuildingTypes buildingType, int _player_id, int _id)
{
	switch (buildingType)
	{
		case START_BASE:
		{
			auto group = tiledMap->getObjectGroup("Buildings");
			ValueMap buildobj;
			Buildings *building = Buildings::creatWithBuildingTypes(START_BASE);
			if (_player_id == 1)
			{
				buildobj = group->getObject("base1");
			}
			else if (_player_id == 2)
			{
				buildobj = group->getObject("base2");
			}
			else if (_player_id == 3)
			{
				buildobj = group->getObject("base3");
			}
			else if (_player_id == 4)
			{
				buildobj = group->getObject("base4");
			}
			float x = buildobj["x"].asFloat();
			float y = buildobj["y"].asFloat();
			float width = buildobj["width"].asFloat();
			float height = buildobj["height"].asFloat();
			PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
			phy->setDynamic(false);
			Sprite * sp = Sprite::create();
			sp->setPosition(Vec2(x, y));
			sp->setAnchorPoint(ccp(0, 0));
			sp->setContentSize(Size(width, height));
			sp->setPhysicsBody(phy);
			tiledMap->addChild(sp);
			building->setAnchorPoint(Vec2(0, 0));
			building->setScale(1);
			building->setPosition(Vec2(x, y));
			if (_player_id == 1)
			{
				building->setName("base1");
			}
			else if (_player_id == 2)
			{
				building->setName("base2");
			}
			else if (_player_id == 3)
			{
				building->setName("base3");
			}
			else if (_player_id == 4)
			{
				building->setName("base4");
			}
			building->createBar();
			building->hpBar->setPosition(building->hpBar->getPosition() - Vec2(10, 0));
			tiledMap->addChild(building, 10, GameSceneNodeTagBuilding);
			building->player_id = _player_id;
			building->id = _id;
			bid_map.insert(building->id, building);
			break;
		}
		case START_CASERN:
		{
			auto group = tiledMap->getObjectGroup("Buildings");
			ValueMap buildobj;
			Buildings *building = Buildings::creatWithBuildingTypes(START_CASERN);
			if (_player_id == 1)
			{
				buildobj = group->getObject("casern1");
			}
			else if (_player_id == 2)
			{
				buildobj = group->getObject("casern2");
			}
			else if (_player_id == 3)
			{
				buildobj = group->getObject("casern3");
			}
			else if (_player_id == 4)
			{
				buildobj = group->getObject("casern4");
			}
			float x = buildobj["x"].asFloat();
			float y = buildobj["y"].asFloat();
			float width = buildobj["width"].asFloat();
			float height = buildobj["height"].asFloat();
			PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
			phy->setDynamic(false);
			Sprite * sp = Sprite::create();
			sp->setPosition(Vec2(x, y));
			sp->setAnchorPoint(ccp(0, 0));
			sp->setContentSize(Size(width, height));
			sp->setPhysicsBody(phy);
			tiledMap->addChild(sp);
			building->setAnchorPoint(Vec2(0, 0));
			building->setScale(1);
			float building_x1 = building->getContentSize().width;
			float building_y1 = building->getContentSize().height;
			building->setPosition(Vec2(x, y));
			if (_player_id == 1)
			{
				building->setName("casern1");
			}
			else if (_player_id == 2)
			{
				building->setName("casern2");
			}
			else if (_player_id == 3)
			{
				building->setName("casern3");
			}
			else if (_player_id == 4)
			{
				building->setName("casern4");
			}
			building->createBar();
			tiledMap->addChild(building, 10, GameSceneNodeTagBuilding);
			building->player_id = _player_id;
			building->id = _id;
			bid_map.insert(building->id, building);
			break;
		}
		case START_ELECTRICSTATION:
		{
			auto group = tiledMap->getObjectGroup("Buildings");
			ValueMap buildobj;
			Buildings *building = Buildings::creatWithBuildingTypes(START_ELECTRICSTATION);
			if (_player_id == 1)
			{
				buildobj = group->getObject("electricStation1");
			}
			else if (_player_id == 2)
			{
				buildobj = group->getObject("electricStation2");
			}
			else if (_player_id == 3)
			{
				buildobj = group->getObject("electricStation3");
			}
			else if (_player_id == 4)
			{
				buildobj = group->getObject("electricStation4");
			}
			float x = buildobj["x"].asFloat();
			float y = buildobj["y"].asFloat();
			float width = buildobj["width"].asFloat();
			float height = buildobj["height"].asFloat();
			PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
			phy->setDynamic(false);
			Sprite * sp = Sprite::create();
			sp->setPosition(Vec2(x, y));
			sp->setAnchorPoint(ccp(0, 0));
			sp->setContentSize(Size(width, height));
			sp->setPhysicsBody(phy);
			tiledMap->addChild(sp);
			building->setAnchorPoint(Vec2(0, 0));
			building->setScale(1);
			float building_x1 = building->getContentSize().width;
			float building_y1 = building->getContentSize().height;
			building->setPosition(Vec2(x, y));
			if (_player_id == 1)
			{
				building->setName("electricStation1");
			}
			else if (_player_id == 2)
			{
				building->setName("electricStation2");
			}
			else if (_player_id == 3)
			{
				building->setName("electricStation3");
			}
			else if (_player_id == 4)
			{
				building->setName("electricStation4");
			}
			building->createBar();
			tiledMap->addChild(building, 10, GameSceneNodeTagBuilding);
			building->player_id = _player_id;
			building->id = _id;
			bid_map.insert(building->id, building);
			break;
		}
		case START_TANKFACTORY:
		{
			auto group = tiledMap->getObjectGroup("Buildings");
			ValueMap buildobj;
			Buildings *building = Buildings::creatWithBuildingTypes(START_TANKFACTORY);
			if (_player_id == 1)
			{
				buildobj = group->getObject("tankFactory1");
			}
			else if (_player_id == 2)
			{
				buildobj = group->getObject("tankFactory2");
			}
			else if (_player_id == 3)
			{
				buildobj = group->getObject("tankFactory3");
			}
			else if (_player_id == 4)
			{
				buildobj = group->getObject("tankFactory4");
			}
			float x = buildobj["x"].asFloat();
			float y = buildobj["y"].asFloat();
			float width = buildobj["width"].asFloat();
			float height = buildobj["height"].asFloat();
			PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
			phy->setDynamic(false);
			Sprite * sp = Sprite::create();
			sp->setPosition(Vec2(x, y));
			sp->setAnchorPoint(ccp(0, 0));
			sp->setContentSize(Size(width, height));
			sp->setPhysicsBody(phy);
			tiledMap->addChild(sp);
			building->setAnchorPoint(Vec2(0, 0));
			building->setScale(1);
			float building_x1 = building->getContentSize().width;
			float building_y1 = building->getContentSize().height;
			building->setPosition(Vec2(x, y));
			if (_player_id == 1)
			{
				building->setName("tankFactory1");
			}
			else if (_player_id == 2)
			{
				building->setName("tankFactory2");
			}
			else if (_player_id == 3)
			{
				building->setName("tankFactory3");
			}
			else if (_player_id == 4)
			{
				building->setName("tankFactory4");
			}
			building->createBar();
			tiledMap->addChild(building, 10, GameSceneNodeTagBuilding);
			building->player_id = _player_id;
			building->id = _id;
			bid_map.insert(building->id, building);
			break;
		}
		case START_OREYARD:
		{
			auto group = tiledMap->getObjectGroup("Buildings");
			ValueMap buildobj;
			Buildings *building = Buildings::creatWithBuildingTypes(START_OREYARD);
			if (_player_id == 1)
			{
				buildobj = group->getObject("oreyard1");
			}
			else if (_player_id == 2)
			{
				buildobj = group->getObject("oreyard2");
			}
			else if (_player_id == 3)
			{
				buildobj = group->getObject("oreyard3");
			}
			else if (_player_id == 4)
			{
				buildobj = group->getObject("oreyard4");
			}
			float x = buildobj["x"].asFloat();
			float y = buildobj["y"].asFloat();
			float width = buildobj["width"].asFloat();
			float height = buildobj["height"].asFloat();
			PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
			phy->setDynamic(false);
			Sprite * sp = Sprite::create();
			sp->setPosition(Vec2(x, y));
			sp->setAnchorPoint(ccp(0, 0));
			sp->setContentSize(Size(width, height));
			sp->setPhysicsBody(phy);
			tiledMap->addChild(sp);
			building->setAnchorPoint(Vec2(0, 0));
			building->setScale(1);
			float building_x1 = building->getContentSize().width;
			float building_y1 = building->getContentSize().height;
			building->setPosition(Vec2(x, y));
			if (_player_id == 1)
			{
				building->setName("oreyard1");
			}
			else if (_player_id == 2)
			{
				building->setName("oreyard2");
			}
			else if (_player_id == 3)
			{
				building->setName("oreyard3");
			}
			else if (_player_id == 4)
			{
				building->setName("oreyard4");
			}
			building->createBar();
			tiledMap->addChild(building, 10, GameSceneNodeTagBuilding);
			building->player_id = _player_id;
			building->id = _id;
			bid_map.insert(building->id, building);
			break;
		}
	}

}

void GameManager::produceSoldiers(SoldierTypes soldierType, int _player_id, int _id)
{
	switch (soldierType)
	{
		case START_MINER:
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			if (_player_id == 1)
			{
				auto soldier = Soldiers::createWithSoldierTypes(START_MINER,MINER1);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("oreyard1")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("oreyard1")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("miner1");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
				if (GameScene::mapType == 1)
				{
					soldier->minerAutoMoveInMap_1();
				}
				else
				{
					soldier->minerAutoMoveInMap_2();
				}
			}
			if (_player_id == 2)
			{
				auto soldier = Soldiers::createWithSoldierTypes(START_MINER, MINER2);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("oreyard2")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("oreyard2")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("miner2");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
				if (GameScene::mapType == 1)
				{
					soldier->minerAutoMoveInMap_1();
				}
				else
				{
					soldier->minerAutoMoveInMap_2();
				}

			}
			if (_player_id == 3)
			{
				auto soldier = Soldiers::createWithSoldierTypes(START_MINER, MINER3);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("oreyard3")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("oreyard3")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("miner3");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
				if (GameScene::mapType == 1)
				{
					soldier->minerAutoMoveInMap_1();
				}
				else
				{
					soldier->minerAutoMoveInMap_2();
				}
			}
			if (_player_id == 4)
			{
				auto soldier = Soldiers::createWithSoldierTypes(START_MINER, MINER4);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("oreyard4")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("oreyard4")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("miner4");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
				if (GameScene::mapType == 1)
				{
					soldier->minerAutoMoveInMap_1();
				}
				else
				{
					soldier->minerAutoMoveInMap_2();
				}
			}
			break;
		}
		case START_POLICEMAN:
		{
			if (_player_id == 1)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_POLICEMAN, POLICEMAN1);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern1")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern1")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("policeman1");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 2)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_POLICEMAN, POLICEMAN2);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern2")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern2")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("policeman2");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}			
			if (_player_id == 3)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_POLICEMAN, POLICEMAN3);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern3")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern3")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("policeman3");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}			
			if (_player_id == 4)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_POLICEMAN, POLICEMAN4);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern4")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern4")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("policeman4");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			break;
		}
		case START_WARRIOR:
		{
			if (_player_id == 1)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_WARRIOR,WARRIOR1);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern1")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern1")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("warrior1");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 2)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_WARRIOR, WARRIOR2);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern2")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern2")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("warrior2");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 3)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_WARRIOR, WARRIOR3);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern3")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern3")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("warrior3");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 4)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_WARRIOR, WARRIOR4);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("casern4")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("casern4")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("warrior4");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			break;
		}
		case START_TANK:
		{
			if (_player_id == 1)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_TANK, TANK1);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("tankFactory1")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("tankFactory1")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("tank1");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 2)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_TANK, TANK2);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("tankFactory2")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("tankFactory2")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("tank2");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 3)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_TANK, TANK3);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("tankFactory3")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("tankFactory3")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("tank3");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			if (_player_id == 4)
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				auto soldier = Soldiers::createWithSoldierTypes(START_TANK, TANK4);
				soldier->setAnchorPoint(Vec2(0.5, 0.5));
				soldier->setScale(1.2);
				float soldiers_x = soldier->getContentSize().width;
				float soldiers_y = soldier->getContentSize().height;
				Size s = tiledMap->getChildByName("tankFactory4")->getContentSize() * 0.3;
				Vec2 position = tiledMap->getChildByName("tankFactory4")->getPosition() + Vec2(s.width, 0);
				soldier->setPosition(position);
				soldier->setName("tank4");
				soldier->createBar();
				tiledMap->addChild(soldier, 10, GameSceneNodeTagSoldier);
				soldier->player_id = _player_id;
				soldier->id = _id;
				sid_map.insert(soldier->id, soldier);
			}
			break;
		}
	}
}

void GameManager::soldiersUpdate(int _player_id)
{
	for (auto elem : sid_map)
	{
		if (elem.first % 4 == _player_id % 4)
		{
			elem.second->setPower((elem.second->getPower())+2);
			elem.second->setMaxHealth(elem.second->getMaxHealth() + 20);
			elem.second->setcurrentHealth(elem.second->getcurrentHealth() + 20);
		}
	}
}

void GameManager::gobackMenu()
{
	Scene *sc = Scene::create();
	auto layer = MenuScene::create();
	sc->addChild(layer);
	auto reScene = TransitionSplitRows::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}

void GameManager::genSoldierUpdateMessage()
{
	vector<Vec2> a;
	a.clear();
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_SUDT, player_id, 0, 0, 0, a);
}

void GameManager::genCreateBuildingMessage(BuildingTypes buildingtype)
{
	int btype;
	switch (buildingtype)
	{
		case START_BASE:
		{
			btype = 1;
			break;
		}
		case START_CASERN:
		{
			btype = 2;
			break;
		}
		case START_ELECTRICSTATION:
		{
			btype = 3;
			break;
		}
		case START_TANKFACTORY:
		{
			btype = 4;
			break;
		}
		case START_OREYARD:
		{
			btype = 5;
			break;
		}
	}
	vector<Vec2> a;
	a.clear();
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_CRTB, player_id, next_id, btype, 0, a);
	next_id += 4;
}

void GameManager::genCreateSoldierMessage(SoldierTypes soldiertype)
{
	int stype;
	switch (soldiertype)
	{
		case START_MINER:
		{
			stype = 1;
			break;
		}
		case START_POLICEMAN:
		{
			stype = 2;
			break;
		}
		case START_WARRIOR:
		{
			stype = 3;
			break;
		}
		case START_TANK:
		{
			stype = 4;
			break;
		}
	}
	vector<Vec2> a;
	a.clear();
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_CRTS, player_id, next_id, 0, stype, a);
	next_id += 4;
}

void GameManager::genMoveMessage(vector<Vec2> moveToPath,int id,SoldierTypes soldiertype)
{
	int stype;
	if (soldiertype == START_MINER)
	{
		stype = 0;
	}
	else
	{
		stype = 1;
	}
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_MOV, player_id, id, 0, stype, moveToPath);
}

void GameManager::genGobackMessgage(int _player_id)
{
	vector<Vec2> a;
	a.clear();
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_EMP, _player_id, 0, 0, 0, a);
}

void GameManager::updateGameState()
{
	vector<Vec2> a;
	a.clear();
	msgs->add_game_message()->genGameMessage(GameMessage::CmdCode::GameMessage_CmdCode_EMP, 0, 0, 0, 0,a);
	auto sent_msg_str = msgs->SerializeAsString();
	socket_client->send_string(sent_msg_str);
	int sent_msg_num = msgs->game_message_size();
	if (sent_msg_num)
		log("Sent Message Num: %d, Sent Message string length: %d", sent_msg_num, sent_msg_str.length());

	auto msg_str = socket_client->get_string();
	msgs->ParseFromString(msg_str);
	int recv_msg_num = msgs->game_message_size();
	if (recv_msg_num)
		log("Received Message Num: %d, Received Message String Length: %d", recv_msg_num, msg_str.length());

	for (int i = 0; i < msgs->game_message_size(); i++)
	{
		const GameMessage&  msg = msgs->game_message(i);
		log("GameManager: Read Message %d Success", i);
		if (msg.cmd_code() == GameMessage::CmdCode::GameMessage_CmdCode_EMP)
		{
			int _player_id = msg.playerid();
			if (_player_id == 0)
			{
				log("Empty Message");
			}
			else
			{
				gobackMenu();
			}
		}
		else if (msg.cmd_code() == GameMessage::CmdCode::GameMessage_CmdCode_CRTB)
		{
			int _id = msg.id();
			int _player_id = msg.playerid();
			log("%d", _player_id);
			int buildingtype = msg.btype();
			if (buildingtype == 1)
			{
				produceBuildings(START_BASE,_player_id,_id);
			}
			else if (buildingtype == 2)
			{
				produceBuildings(START_CASERN, _player_id, _id);
			}
			else if (buildingtype == 3)
			{
				produceBuildings(START_ELECTRICSTATION, _player_id, _id);
			}
			else if (buildingtype == 4)
			{
				produceBuildings(START_TANKFACTORY, _player_id, _id);
			}
			else if (buildingtype == 5)
			{
				produceBuildings(START_OREYARD, _player_id, _id);
			}
		}
		else if (msg.cmd_code() == GameMessage::CmdCode::GameMessage_CmdCode_CRTS)
		{
			int _id = msg.id();
			int _player_id = msg.playerid();
			log("%d", _player_id);
			int soldiertype = msg.stype();
			if (soldiertype == 1)
			{
				produceSoldiers(START_MINER, _player_id, _id);
			}
			if (soldiertype == 2)
			{
				produceSoldiers(START_POLICEMAN, _player_id, _id);
			}
			if (soldiertype == 3)
			{
				produceSoldiers(START_WARRIOR, _player_id, _id);
			}
			if (soldiertype == 4)
			{
				produceSoldiers(START_TANK, _player_id, _id);
			}
		}
		else if (msg.cmd_code() == GameMessage::CmdCode::GameMessage_CmdCode_MOV)
		{
			int _id = msg.id();
			int _player_id = msg.playerid();
			int stype = msg.stype();
			if (stype == 0)
			{
				break;
			}
			int size = msg.movepath().vec_size();
			vector<Vec2> move_path(size);
			for (int i = 0; i < size; i++)
			{
				move_path[i].x = msg.movepath().vec(i).x();
				move_path[i].y = msg.movepath().vec(i).y();
			}
			Soldiers* soldier = sid_map.find(_id)->second;
			if (soldier)
			{
				soldier->moveToPath.clear();
				soldier->stopAllActions();
				soldier->moveToPath = move_path;
				soldier->soldierAutoMove();
			}
		}
		else if (msg.cmd_code() == GameMessage::CmdCode::GameMessage_CmdCode_SUDT)
		{
			int _player_id = msg.playerid();
			soldiersUpdate(_player_id);
		}
	}
	msgs->clear_game_message();
}


