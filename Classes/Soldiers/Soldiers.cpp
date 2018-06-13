#include"Soldiers.h"

EventListenerTouchOneByOne * Soldiers::touchSoldierListener;
EventDispatcher * Soldiers::eventDispatcher;

Soldiers::Soldiers(SoldierTypes soldierType)
{
	this->soldiertype = soldierType;
	this->health = 0;
	this->price = 0;
	this->ifselect = SELECT_OFF;
	this->maxHealth = 0;
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
			soldier->maxHealth = MINER_HEALTH;
			soldier->speed = MINER_SPEED;
			break;
		}
		case START_POLICEMAN:
		{
			soldierName = POLICEMAN;
			soldier->health = POLICEMAN_HEALTH;
			soldier->price = POLICEMAN_PRICE;
			soldier->ifselect = SELECT_OFF;
			soldier->maxHealth = POLICEMAN_HEALTH;
			soldier->speed = POLICEMAN_SPEED;
			break;
		}
		case START_TANK:
		{
			soldierName = TANK;
			soldier->health = TANK_HEALTH;
			soldier->price = TANK_PRICE;
			soldier->ifselect = SELECT_OFF;
			soldier->maxHealth = TANK_HEALTH;
			soldier->speed = TANK_SPEED;
		}
			
	    /*´ýÌí¼Ó*/
		//ÒÑ²¹³äpolice.tankµÄhealthÓëprice

	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
		touchSoldierListener = EventListenerTouchOneByOne::create();
		//touchSoldierListener->setSwallowTouches(true);
		touchSoldierListener->onTouchBegan = [&](Touch *touch, Event *event)
		{
			log("soldier");
			/*auto target = dynamic_cast<Soldiers *>(event->getCurrentTarget());
			if (!target->getifSelect())
			{
				return false;
			}*/
			return true;
		};
		touchSoldierListener->onTouchEnded = [](Touch *touch, Event *event)
		{
			auto origin = Director::getInstance()->getVisibleOrigin();
			//auto target = dynamic_cast<Soldiers *>(event->getCurrentTarget());
			Rect rect = GameScene::getSelectRect();
			for (auto &sprite : GameScene::gettiledMap()->getChildren())
			{
				/*if (!rect.containsPoint(sprite->getPosition()))
				{
					continue;
				}*/
				if (sprite->getTag() == GameSceneNodeTagSoldier)
				{
					auto target = dynamic_cast<Soldiers *>(sprite);
					if (target->getifSelect())
					{
						auto start = turnToApoint(target->getPosition());
						auto end = turnToApoint(GameScene::gettiledMap()->convertTouchToNodeSpace(touch));
						Astar pathFinder(100, 100, start, end);
						pathFinder.findPath();
						vector<Apoint *> path = pathFinder.getPath();
						vector<Vec2> moveToPath;
						for (int i = path.size() - 1; i >= 0; i--)
						{
							float x = (path[i]->getX()) * (GameScene::gettiledMap()->getTileSize().width);
							float y = (GameScene::gettiledMap()->getMapSize().height - path[i]->getY()) 
								* (GameScene::gettiledMap()->getTileSize().height);

							moveToPath.push_back(Vec2(x, y));
						}
						for (auto &p : moveToPath)
						{
							float distance = sqrt(pow(target->getPosition().x - p.x, 2) 
								+ pow(target->getPosition().y - p.y, 2));

							MoveTo *soldierMove = MoveTo::create(distance / target->getSpeed(), p);
							target->runAction(soldierMove);
						}
						
						/*auto pos1 = GameScene::gettiledMap()->convertTouchToNodeSpace(touch);
						auto pos2 = target->getPosition();
						float distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
						MoveTo *soldierMove = MoveTo::create(distance/target->speed, pos1);
						target->runAction(soldierMove);
						target->setifSelect(SELECT_OFF);*/
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

Apoint Soldiers::turnToApoint(Vec2 vecPoint)
{
	auto temp = GameScene::gettiledMap();
	int x = vecPoint.x / temp->getTileSize().width;
	int y = ((temp->getMapSize().height*temp->getTileSize().height) - vecPoint.y) / temp->getTileSize().height;
	return Apoint(x, y);
}

void Soldiers::createBar()
{
	hpBar = Bar::create();
	float bar_width = this->getContentSize().width;
	float bar_height = this->getContentSize().height;
	hpBar->setLength(bar_width);
	hpBar->setHeight(2);
	hpBar->setVisible(false);
	addChild(hpBar, 20);
	hpBar->setPosition(Point(0, bar_height + 5));
}

void Soldiers::displayHpBar()
{
	if (hpBar)
	{
		hpBar->schedule(schedule_selector(Bar::update));
		hpBar->setVisible(true);
	}
}

void Soldiers::hideHpBar()
{
	if (hpBar)
	{
		hpBar->unschedule(schedule_selector(Bar::update));
		hpBar->setVisible(false);
	}
}
