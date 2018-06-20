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

	log(" ");
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
	//this->attacker = NULL;
	//this->attackerPower = 0;
	this->ifAttack = false;
}

Soldiers * Soldiers::createWithSoldierTypes(SoldierTypes soldierType, char *soldierName)
{
	Soldiers *soldier = new Soldiers(soldierType);
	switch (soldierType)
	{
	case START_MINER:
	{
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
	case START_WARRIOR:
	{
		soldier->health = WARRIOR_HEALTH;
		soldier->price = WARRIOR_PRICE;
		soldier->ifselect = SELECT_OFF;
		soldier->maxHealth = WARRIOR_HEALTH;
		soldier->speed = WARRIOR_SPEED;
		soldier->power = WARRIOR_POWER;
		soldier->atkRadius = WARRIOR_ATK_RADIUS;
		soldier->ifAttack = false;
		break;
	}
	case START_TANK:
	{
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
	}
	if (soldier && soldier->initWithFile(soldierName))
	{
		soldier->autorelease();
		auto body = PhysicsBody::createBox((soldier->getContentSize()) * 0.5);
		body->setCategoryBitmask(0x01);
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

vector<Soldiers *> & Soldiers::getAttackers()
{
	return attackers;
}

void Soldiers::findEnemy()
{
	for (auto &s : GameScene::gamemanager->sid_map)
	{
		if (s.first % 4 != getplayerID()%4)
		{
			auto distance = this->getPosition().getDistance(s.second->getPosition());
			if (distance <= this->getAtkRadius())
			{
				setSoldierEnemy(s.second);
				s.second->getAttackers().push_back(this);
				//s->setAttackerPower(this->getPower());
				setIfAttack(true);
				return;
			}
		}
	}
	for (auto &b : GameScene::gamemanager->bid_map)
	{
		if (b.first % 4 != getplayerID() % 4)
		{
			auto distance = this->getPosition().getDistance(b.second->getPosition());
			if (distance <= this->getAtkRadius())
			{
				setBuildingEnemy(b.second);
				b.second->getAttackers().push_back(this);
				//b->setAttacker(this);
				setIfAttack(true);
				return;
			}
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
			auto it = find(sEnemy->getAttackers().begin(), sEnemy->getAttackers().end(), this);
			if (it != sEnemy->getAttackers().end())
			{
				sEnemy->getAttackers().erase(it);
			}
			//sEnemy->setAttacker(NULL);
			//sEnemy->setAttackerPower(0);
			setSoldierEnemy(NULL);
			setIfAttack(false);
			return;
		}
		auto fire = Attackeffect::create();
		Vec2 sEnemyPosiotion;
		sEnemyPosiotion.x = sEnemy->getContentSize().width + sEnemy->getPosition().x;
		sEnemyPosiotion.y = sEnemy->getContentSize().width + sEnemy->getPosition().y;
		fire->setAtkPath(this->getPosition(), sEnemyPosiotion);
		GameScene::gettiledMap()->addChild(fire, 10, GameSceneNodeTagFire);
		sEnemy->setcurrentHealth(sEnemy->getcurrentHealth() - getPower());
		sEnemy->displayHpBar();
		return;
	}
	if (bEnemy)
	{
		auto distance = this->getPosition().getDistance(bEnemy->getPosition());
		if (distance > this->getAtkRadius())
		{
			auto it = find(bEnemy->getAttackers().begin(), bEnemy->getAttackers().end(), this);
			if (it != bEnemy->getAttackers().end())
			{
				bEnemy->getAttackers().erase(it);
			}
			//bEnemy->setAttacker(NULL);
			setBuildingEnemy(NULL);
			setIfAttack(false);
			return;
		}
		auto fire = Attackeffect::create();
		Vec2 bEnemyPosiotion;
		bEnemyPosiotion.x = bEnemy->getContentSize().width + bEnemy->getPosition().x;
		bEnemyPosiotion.y = bEnemy->getContentSize().width + bEnemy->getPosition().y;
		fire->setAtkPath(this->getPosition(), bEnemyPosiotion);
		GameScene::gettiledMap()->addChild(fire, 10, GameSceneNodeTagFire);
		bEnemy->setcurrentHealth(bEnemy->getcurrentHealth() - getPower());
		bEnemy->displayHpBar();
		return;
	}

}

void Soldiers::update(float dt)
{
	if (getcurrentHealth() <= 0)
	{
		for (auto &atker : attackers)
		{
			atker->setSoldierEnemy(NULL);
		}
		if (sEnemy)
		{
			auto it = find(sEnemy->getAttackers().begin(), sEnemy->getAttackers().end(), this);
			if (it != sEnemy->getAttackers().end())
			{
				sEnemy->getAttackers().erase(it);
			}
		}
		if (bEnemy)
		{
			auto it = find(bEnemy->getAttackers().begin(), bEnemy->getAttackers().end(), this);
			if (it != bEnemy->getAttackers().end())
			{
				bEnemy->getAttackers().erase(it);
			}
		}

		remove();
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

void Soldiers::remove()
{
	auto explosion = Explosioneffect::create();
	explosion->setPosition(getPosition());
	GameScene::gettiledMap()->addChild(explosion, 15);
	removeFromParent();
	for (auto elem : GameScene::gamemanager->sid_map)
	{
		if (elem.first == id)
		{
			GameScene::gamemanager->sid_map.erase(elem.first);
			break;
		}
	}
}
