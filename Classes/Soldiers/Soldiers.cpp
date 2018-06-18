#include"Soldiers.h"

bool Attackeffect::init()
{
	if (!ParticleFire::init())
	{
		return false;
	}
	setScale(0.1);
	setPositionType(PositionType::RELATIVE);
	return true;
}
void Attackeffect::setAtkPath(Vec2 from, Vec2 to)
{
	From = from;
	To = to;
	setPosition(From);
	moveFromTo = (To - From).getNormalized() * moveSpeed;
	schedule(schedule_selector(Attackeffect::updateAtkEffect));
}
void Attackeffect::updateAtkEffect(float dt)
{
	if (((abs(getPosition().x - To.x) < moveSpeed) && (abs(getPosition().y - To.y) < moveSpeed)))
	{
		removeFromParent();
	}
	else
	{
		setPosition(getPosition() + moveFromTo);
	}
}


bool Explosioneffect::init()
{
	if (!ParticleFire::init())
	{
		return false;
	}
	setScale(0.0000008);
	setDuration(1);
	auto action = ScaleBy::create(0.5, 500000);
	runAction(action);
	scheduleOnce(schedule_selector(Explosioneffect::updateRemove), 0.6);
	setPositionType(PositionType::RELATIVE);
	return true;
}
void Explosioneffect::updateRemove(float dt)
{
	removeFromParent();
}


Soldiers::Soldiers(SoldierTypes soldierType)
{
	this->soldiertype = soldierType;
	this->health = 0;
	this->price = 0;
	this->ifselect = SELECT_OFF;
	this->maxHealth = 0;
	this->power = 0;
	this->atkRadius = 0;
	this->sEnemy = NULL;
	this->bEnemy = NULL;
	this->attacker = NULL;
	//this->attackerPower = 0;
	this->ifAttack = false;
}

/*Soldiers::~Soldiers()
{
	CC_SAFE_RELEASE(sEnemy);
	CC_SAFE_RELEASE(bEnemy);
	CC_SAFE_RELEASE(attacker);
}*/

Soldiers * Soldiers::createWithSoldierTypes(SoldierTypes soldierType)
{
	Soldiers *soldier = new Soldiers(soldierType);
	const char *soldierName = "soldiername";
	switch (soldierType)
	{
<<<<<<< HEAD
		case START_MINER:
		{
			soldierName = MINER;
			soldier->health = MINER_HEALTH;
			soldier->price = MINER_PRICE;
			soldier->ifselect = SELECT_OFF;
			soldier->maxHealth = MINER_HEALTH;
			soldier->speed = MINER_SPEED;
			soldier->power = MINER_POWER;
			soldier->atkRadius = MINER_ATK_RADIUS;
			soldier->ifAttack = false;
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
			soldier->power = POLICEMAN_POWER;
			soldier->atkRadius = POLICEMAN_ATK_RADIUS;
			soldier->ifAttack = false;
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
			soldier->power = TANK_POWER;
			soldier->atkRadius = TANK_ATK_RADIUS;
			soldier->ifAttack = false;
			break;
		}
			
	    /*待添加*/
		//已补充police.tank的health与price
=======
	case START_MINER:
	{
		soldierName = MINER1;
		soldier->health = MINER_HEALTH;
		soldier->price = MINER_PRICE;
		soldier->ifselect = SELECT_OFF;
		soldier->maxHealth = MINER_HEALTH;
		soldier->speed = MINER_SPEED;
		break;
	}
	case START_POLICEMAN:
	{
		soldierName = POLICEMAN1;
		soldier->health = POLICEMAN_HEALTH;
		soldier->price = POLICEMAN_PRICE;
		soldier->ifselect = SELECT_OFF;
		soldier->maxHealth = POLICEMAN_HEALTH;
		soldier->speed = POLICEMAN_SPEED;
		break;
	}
	case START_WARRIOR:
	{
		soldierName = WARRIOR1;
		soldier->health = WARRIOR_HEALTH;
		soldier->price = WARRIOR_PRICE;
		soldier->ifselect = SELECT_OFF;
		soldier->maxHealth = WARRIOR_HEALTH;
		soldier->speed = WARRIOR_SPEED;
		break;
	}
	case START_TANK:
	{
		soldierName = TANK1;
		soldier->health = TANK_HEALTH;
		soldier->price = TANK_PRICE;
		soldier->ifselect = SELECT_OFF;
		soldier->maxHealth = TANK_HEALTH;
		soldier->speed = TANK_SPEED;
	}

>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151

	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
<<<<<<< HEAD
		

		auto body = PhysicsBody::createBox((soldier->getContentSize()) * 0.5);
		body->setCategoryBitmask(0x01);
=======
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
						auto pos1 = GameScene::gettiledMap()->convertTouchToNodeSpace(touch);
						auto pos2 = target->getPosition();
						float distance = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
						MoveTo *soldierMove = MoveTo::create(distance/target->speed, pos1);
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
>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151
		body->setContactTestBitmask(0x02);
		body->setCollisionBitmask(0x02);
		soldier->setPhysicsBody(body);

		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return nullptr;
}

void Soldiers::soldierAutoMove()
{
	if (moveToPath.empty())
	{
		return;
	}
	MoveTo *moveAction = MoveTo::create(this->getSpeed(), moveToPath[0]);
	//log("%f,%f", moveToPath[0].x, moveToPath[0].y);
	CallFunc *moveCallback = CallFunc::create(CC_CALLBACK_0(Soldiers::soldierAutoMove, this));
	moveToPath.erase(moveToPath.begin());
	this->runAction(Sequence::create(moveAction, moveCallback, nullptr));
}

void Soldiers::findEnemy()
{
	for (auto &s : GameScene::soldierSprites)
	{
		if (s == this)
		{
			continue;
		}
		auto distance = this->getPosition().getDistance(s->getPosition());
		if (distance <= this->getAtkRadius())
		{
			setSoldierEnemy(s);
			s->setAttacker(this);
			//s->setAttackerPower(this->getPower());
			setIfAttack(true);
			return;
		}
	}
	for (auto &b : GameScene::buildingSprites)
	{
		auto distance = this->getPosition().getDistance(b->getPosition());
		if (distance <= this->getAtkRadius())
		{
			setBuildingEnemy(b);
			//b->setAttacker(this);
			setIfAttack(true);
			return;
		}
	}
}
void Soldiers::attack()
{
	if (!sEnemy && !bEnemy)
	{
		setIfAttack(false);
		return;
	}
	if (sEnemy)
	{
		auto distance = this->getPosition().getDistance(sEnemy->getPosition());
		if (distance > this->getAtkRadius())
		{
			sEnemy->setAttacker(NULL);
			//sEnemy->setAttackerPower(0);
			setSoldierEnemy(NULL);
			setIfAttack(false);
			return;
		}
		auto fire = Attackeffect::create();
		fire->setAtkPath(this->getPosition(), sEnemy->getPosition());
		GameScene::gettiledMap()->addChild(fire, 10, GameSceneNodeTagFire);
		sEnemy->setcurrentHealth(sEnemy->getcurrentHealth() - getPower());
		sEnemy->displayHpBar();
	}
	if (bEnemy)
	{
		auto distance = this->getPosition().getDistance(bEnemy->getPosition());
		if (distance > this->getAtkRadius())
		{
			//bEnemy->setAttacker(NULL);
			setBuildingEnemy(NULL);
			setIfAttack(false);
			return;
		}
		auto fire = Attackeffect::create();
		fire->setAtkPath(this->getPosition(), bEnemy->getPosition());
		GameScene::gettiledMap()->addChild(fire, 10, GameSceneNodeTagFire);
		bEnemy->setcurrentHealth(bEnemy->getcurrentHealth() - getPower());
		bEnemy->displayHpBar();
	}
	
}

void Soldiers::update(float dt)
{
<<<<<<< HEAD
	if (getcurrentHealth() <= 0)
	{
		auto explosion = Explosioneffect::create();
		explosion->setPosition(getPosition());
		GameScene::gettiledMap()->addChild(explosion, 15);
		getAttacker()->setIfAttack(false);
		auto it = find(GameScene::soldierSprites.begin(), GameScene::soldierSprites.end(), this);
		if (it != GameScene::soldierSprites.end())
		{
			GameScene::soldierSprites.erase(it);
		}
		removeFromParent();
		return;
	}
	//if (getAttacker()/*getAttackerPower()*/)
	//{
		//setcurrentHealth(getcurrentHealth() - getAttacker()->getPower()/*getAttackerPower()*/);
		//displayHpBar();
	//}
	if (!ifAttack)
	{
		findEnemy();
	}
	else
	{
		if (attackCD)
		{
			attackCD--;
			return;
		}
		attack();
		attackCD = 30;
	}
=======
	int x = vecPoint.x / 16;
	int y = ((100 * 16) - vecPoint.y) / 16;
	return Apoint(x, y);
>>>>>>> 34360dbd6820c2083d37348657fa6d8677657151
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
		log("aksdhkjhuekkad");
		hpBar->schedule(schedule_selector(Bar::update));
		hpBar->setVisible(true);
	}
	log("askdksd");
}

void Soldiers::hideHpBar()
{
	if (hpBar)
	{
		hpBar->unschedule(schedule_selector(Bar::update));
		hpBar->setVisible(false);
	}
}