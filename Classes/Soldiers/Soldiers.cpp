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
		sEnemyPosiotion.x = sEnemy->getContentSize().width/2 + sEnemy->getPosition().x;
		sEnemyPosiotion.y = sEnemy->getContentSize().width/2 + sEnemy->getPosition().y;
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
		bEnemyPosiotion.x = bEnemy->getContentSize().width /2+ bEnemy->getPosition().x;
		bEnemyPosiotion.y = bEnemy->getContentSize().width /2+ bEnemy->getPosition().y;
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

void Soldiers::minerRemoveAndAddMoney()
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
	removeFromParent();
	for (auto elem : GameScene::gamemanager->sid_map)
	{
		if (elem.first == id)
		{
			GameScene::gamemanager->sid_map.erase(elem.first);
			break;
		}
	}
	(GameScene::Money) += this->getPrice() * 3;
}

void Soldiers::minerAutoMoveInMap_1()
{
	if (this->getName() == "miner1")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path11");
		auto obj2 = group->getObject("path12");
		auto obj3 = group->getObject("path13");
		auto startPos = this->getPosition();
		auto path_11_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_12_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_13_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_11_pos) / 40, path_11_pos);
		MoveTo *move_2 = MoveTo::create(path_11_pos.getDistance(path_12_pos) / 40, path_12_pos);
		MoveTo *move_3 = MoveTo::create(path_12_pos.getDistance(path_13_pos) / 40, path_13_pos);
		MoveTo *move_4 = MoveTo::create(path_13_pos.getDistance(path_12_pos) / 40, path_12_pos);
		MoveTo *move_5 = MoveTo::create(path_12_pos.getDistance(path_11_pos) / 40, path_11_pos);
		MoveTo *move_6 = MoveTo::create(path_11_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, 
			move_4, move_5, move_6, addMoney, nullptr));
	}
	if (this->getName() == "miner2")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path21");
		auto obj2 = group->getObject("path22");
		auto obj3 = group->getObject("path23");
		auto obj4 = group->getObject("path24");
		auto obj5 = group->getObject("path25");
		auto startPos = this->getPosition();
		auto path_21_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_22_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_23_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		auto path_24_pos = Vec2(obj4["x"].asFloat(), obj4["y"].asFloat());
		auto path_25_pos = Vec2(obj5["x"].asFloat(), obj5["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_21_pos) / 40, path_21_pos);
		MoveTo *move_2 = MoveTo::create(path_21_pos.getDistance(path_22_pos) / 40, path_22_pos);
		MoveTo *move_3 = MoveTo::create(path_22_pos.getDistance(path_23_pos) / 40, path_23_pos);
		MoveTo *move_4 = MoveTo::create(path_23_pos.getDistance(path_24_pos) / 40, path_24_pos);
		MoveTo *move_5 = MoveTo::create(path_24_pos.getDistance(path_25_pos) / 40, path_25_pos);
		MoveTo *move_6 = MoveTo::create(path_25_pos.getDistance(path_24_pos) / 40, path_24_pos);
		MoveTo *move_7 = MoveTo::create(path_24_pos.getDistance(path_23_pos) / 40, path_23_pos);
		MoveTo *move_8 = MoveTo::create(path_23_pos.getDistance(path_22_pos) / 40, path_22_pos);
		MoveTo *move_9 = MoveTo::create(path_22_pos.getDistance(path_21_pos) / 40, path_21_pos);
		MoveTo *move_10 = MoveTo::create(path_21_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, move_4, move_5,
			move_6, move_7, move_8, move_9, move_10, addMoney, nullptr));
	}
	if (this->getName() == "miner3")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path31");
		auto obj2 = group->getObject("path32");
		auto obj3 = group->getObject("path33");
		auto startPos = this->getPosition();
		auto path_31_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_32_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_33_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_31_pos) / 40, path_31_pos);
		MoveTo *move_2 = MoveTo::create(path_31_pos.getDistance(path_32_pos) / 40, path_32_pos);
		MoveTo *move_3 = MoveTo::create(path_32_pos.getDistance(path_33_pos) / 40, path_33_pos);
		MoveTo *move_4 = MoveTo::create(path_33_pos.getDistance(path_32_pos) / 40, path_32_pos);
		MoveTo *move_5 = MoveTo::create(path_32_pos.getDistance(path_31_pos) / 40, path_31_pos);
		MoveTo *move_6 = MoveTo::create(path_31_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, 
			move_4, move_5, move_6, addMoney, nullptr));
	}
	if (this->getName() == "miner4")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path41");
		auto obj2 = group->getObject("path42");
		auto obj3 = group->getObject("path43");
		auto obj4 = group->getObject("path44");
		auto startPos = this->getPosition();
		auto path_41_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_42_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_43_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		auto path_44_pos = Vec2(obj4["x"].asFloat(), obj4["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_41_pos) / 40, path_41_pos);
		MoveTo *move_2 = MoveTo::create(path_41_pos.getDistance(path_42_pos) / 40, path_42_pos);
		MoveTo *move_3 = MoveTo::create(path_42_pos.getDistance(path_43_pos) / 40, path_43_pos);
		MoveTo *move_4 = MoveTo::create(path_43_pos.getDistance(path_44_pos) / 40, path_44_pos);
		MoveTo *move_5 = MoveTo::create(path_44_pos.getDistance(path_43_pos) / 40, path_43_pos);
		MoveTo *move_6 = MoveTo::create(path_43_pos.getDistance(path_42_pos) / 40, path_42_pos);
		MoveTo *move_7 = MoveTo::create(path_42_pos.getDistance(path_41_pos) / 40, path_41_pos);
		MoveTo *move_8 = MoveTo::create(path_41_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, move_4, 
			move_5, move_6, move_7, move_8, addMoney, nullptr));
	}
}

void Soldiers::minerAutoMoveInMap_2()
{
	if (this->getName() == "miner1")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path11");
		auto obj2 = group->getObject("path12");
		auto obj3 = group->getObject("path13");
		auto obj4 = group->getObject("path14");
		auto startPos = this->getPosition();
		auto path_11_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_12_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_13_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		auto path_14_pos = Vec2(obj4["x"].asFloat(), obj4["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_11_pos) / 40, path_11_pos);
		MoveTo *move_2 = MoveTo::create(path_11_pos.getDistance(path_12_pos) / 40, path_12_pos);
		MoveTo *move_3 = MoveTo::create(path_12_pos.getDistance(path_13_pos) / 40, path_13_pos);
		MoveTo *move_4 = MoveTo::create(path_13_pos.getDistance(path_14_pos) / 40, path_14_pos);
		MoveTo *move_5 = MoveTo::create(path_14_pos.getDistance(path_13_pos) / 40, path_13_pos);
		MoveTo *move_6 = MoveTo::create(path_13_pos.getDistance(path_12_pos) / 40, path_12_pos);
		MoveTo *move_7 = MoveTo::create(path_12_pos.getDistance(path_11_pos) / 40, path_11_pos);
		MoveTo *move_8 = MoveTo::create(path_11_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, move_4, 
			move_5, move_6, move_7, move_8, addMoney, nullptr));
	}
	if (this->getName() == "miner2")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path21");
		auto obj2 = group->getObject("path22");
		auto obj3 = group->getObject("path23");
		auto obj4 = group->getObject("path24");
		auto obj5 = group->getObject("path25");
		auto startPos = this->getPosition();
		auto path_21_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_22_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_23_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		auto path_24_pos = Vec2(obj4["x"].asFloat(), obj4["y"].asFloat());
		auto path_25_pos = Vec2(obj5["x"].asFloat(), obj5["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_21_pos) / 40, path_21_pos);
		MoveTo *move_2 = MoveTo::create(path_21_pos.getDistance(path_22_pos) / 40, path_22_pos);
		MoveTo *move_3 = MoveTo::create(path_22_pos.getDistance(path_23_pos) / 40, path_23_pos);
		MoveTo *move_4 = MoveTo::create(path_23_pos.getDistance(path_24_pos) / 40, path_24_pos);
		MoveTo *move_5 = MoveTo::create(path_24_pos.getDistance(path_25_pos) / 40, path_25_pos);
		MoveTo *move_6 = MoveTo::create(path_25_pos.getDistance(path_24_pos) / 40, path_24_pos);
		MoveTo *move_7 = MoveTo::create(path_24_pos.getDistance(path_23_pos) / 40, path_23_pos);
		MoveTo *move_8 = MoveTo::create(path_23_pos.getDistance(path_22_pos) / 40, path_22_pos);
		MoveTo *move_9 = MoveTo::create(path_22_pos.getDistance(path_21_pos) / 40, path_21_pos);
		MoveTo *move_10 = MoveTo::create(path_21_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, move_4, move_5,
			move_6, move_7, move_8, move_9, move_10, addMoney, nullptr));
	}
	if (this->getName() == "miner3")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path31");
		auto obj2 = group->getObject("path32");
		auto obj3 = group->getObject("path33");
		auto startPos = this->getPosition();
		auto path_31_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_32_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_33_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_31_pos) / 40, path_31_pos);
		MoveTo *move_2 = MoveTo::create(path_31_pos.getDistance(path_32_pos) / 40, path_32_pos);
		MoveTo *move_3 = MoveTo::create(path_32_pos.getDistance(path_33_pos) / 40, path_33_pos);
		MoveTo *move_4 = MoveTo::create(path_33_pos.getDistance(path_32_pos) / 40, path_32_pos);
		MoveTo *move_5 = MoveTo::create(path_32_pos.getDistance(path_31_pos) / 40, path_31_pos);
		MoveTo *move_6 = MoveTo::create(path_31_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3,
			move_4, move_5, move_6, addMoney, nullptr));
	}
	if (this->getName() == "miner4")
	{
		auto group = GameScene::gettiledMap()->getObjectGroup("PathObject");
		auto obj1 = group->getObject("path41");
		auto obj2 = group->getObject("path42");
		auto obj3 = group->getObject("path43");
		auto obj4 = group->getObject("path44");
		auto startPos = this->getPosition();
		auto path_41_pos = Vec2(obj1["x"].asFloat(), obj1["y"].asFloat());
		auto path_42_pos = Vec2(obj2["x"].asFloat(), obj2["y"].asFloat());
		auto path_43_pos = Vec2(obj3["x"].asFloat(), obj3["y"].asFloat());
		auto path_44_pos = Vec2(obj4["x"].asFloat(), obj4["y"].asFloat());
		MoveTo *move_1 = MoveTo::create(startPos.getDistance(path_41_pos) / 40, path_41_pos);
		MoveTo *move_2 = MoveTo::create(path_41_pos.getDistance(path_42_pos) / 40, path_42_pos);
		MoveTo *move_3 = MoveTo::create(path_42_pos.getDistance(path_43_pos) / 40, path_43_pos);
		MoveTo *move_4 = MoveTo::create(path_43_pos.getDistance(path_44_pos) / 40, path_44_pos);
		MoveTo *move_5 = MoveTo::create(path_44_pos.getDistance(path_43_pos) / 40, path_43_pos);
		MoveTo *move_6 = MoveTo::create(path_43_pos.getDistance(path_42_pos) / 40, path_42_pos);
		MoveTo *move_7 = MoveTo::create(path_42_pos.getDistance(path_41_pos) / 40, path_41_pos);
		MoveTo *move_8 = MoveTo::create(path_41_pos.getDistance(startPos) / 40, startPos);
		CallFunc *addMoney = CallFunc::create(CC_CALLBACK_0(Soldiers::minerRemoveAndAddMoney, this));
		this->runAction(Sequence::create(move_1, move_2, move_3, move_4,
			move_5, move_6, move_7, move_8, addMoney, nullptr));
	}
}

