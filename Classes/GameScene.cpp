#include"GameScene.h"

void MouseRect::update(float dt)
{
	clear();
	Node *parent = getParent();
	end = touch_end - parent->getPosition();
	drawRect(start, end, Color4F(0, 1, 0, 1));
}
void MouseRect::reset()
{
	setVisible(false);
	if (isScheduled(schedule_selector(MouseRect::update)))
	{
		unschedule(schedule_selector(MouseRect::update));
	}
	touch_start = Point{ 0,0 };
	touch_end = Point{ 0,0 };
	start = Point{ 0,0 };
	end = Point{ 0,0 };
}

int GameScene::Money;
int GameScene::Power;
TMXTiledMap *GameScene::_tiledMap1;
int GameScene::mapType;
int GameScene::playerid;
GameManager *GameScene::gamemanager;

//Mouse Rect相关方法
Rect GameScene::getvisionRect()
{
	auto visible_origin = Vec2(0, 0) - _tiledMap1->getPosition();
	auto visible_size = Director::getInstance()->getVisibleSize();
	return cocos2d::Rect(visible_origin, visible_size);
}

GameScene* GameScene::create(SocketClient* _socket_client, SocketServer* _socket_server)
{
	GameScene *game_scene = new (std::nothrow) GameScene();
	if (game_scene && game_scene->init(_socket_client, _socket_server))
	{
		game_scene->autorelease();
		return game_scene;
	}
	CC_SAFE_DELETE(game_scene);

	return nullptr;
}

Scene * GameScene::createScene(SocketClient* _socket_client, SocketServer* _socket_server)
{
	Scene *scene = Scene::createWithPhysics();
	PhysicsWorld *phyWorld = scene->getPhysicsWorld();
	//用于物理引擎debug
	//phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	phyWorld->setGravity(Vec2(0, 0));
	auto layer = GameScene::create(_socket_client, _socket_server);
	scene->addChild(layer);
	return scene;
}

bool GameScene::init(SocketClient* _socket_client, SocketServer* _socket_server)
{
	if (!Layer::init())
	{
		return false;
	}
	//服务器相关
	socket_client = _socket_client;
	socket_server = _socket_server;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/************地图************/
	//游戏地图
	if (mapType == 1)
	{
		_tiledMap1 = TMXTiledMap::create(GAMEMAP1);
	}
	else
	{
		_tiledMap1 = TMXTiledMap::create(GAMEMAP2);
	}
	_tiledMap1->setAnchorPoint(Vec2(0, 0));
	_tiledMap1->setPosition(0, 0);
	addChild(_tiledMap1, 0);
	focusOnBase();
	/*TMXObjectGroup *objectsGroup = _tiledMap1->objectGroupNamed("Objects");
	ValueVector objects = objectsGroup->getObjects();
	for (auto obj : objects) 
	{
		ValueMap& dict = obj.asValueMap();
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		Point p1 = Vec2(x, y);
		Point p2 = gettiledMap()->convertToNodeSpace(p1);
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
		phy->setDynamic(false);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(x, y));
		sp->setAnchorPoint(ccp(0,0));
		sp->setContentSize(Size(width, height));
		sp->setPhysicsBody(phy);
		_tiledMap1->addChild(sp);
	}*/
	//地图移动的鼠标事件
	mouse_event = EventListenerMouse::create();
	mouse_event->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_event, 1);
	//各种键盘事件
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	//鼠标绘制一个矩形框
	mouseRect = MouseRect::create();
	mouseRect->setVisible(false);
	_tiledMap1->addChild(mouseRect);
	mouseRectListener = EventListenerTouchOneByOne::create();
	mouseRectListener->onTouchBegan = CC_CALLBACK_2(GameScene::mouseRectOnTouchBegan, this);
	mouseRectListener->onTouchMoved = CC_CALLBACK_2(GameScene::mouseRectOnTouchMoved, this);
	mouseRectListener->onTouchEnded = CC_CALLBACK_2(GameScene::mouseRectOnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseRectListener, this);

	/*******************游戏管理器*****************/
	playerid = socket_client->camp();
	playernum = socket_client->total();
	gamemanager = GameManager::create();
	gamemanager->retain();
	gamemanager->setMessageSet(&msg_set);
	gamemanager->setTiledMap(_tiledMap1);
	gamemanager->setSocketClient(socket_client);
	gamemanager->setGameScene(this);
	gamemanager->setPlayerID(socket_client->camp());
	gamemanager->setPlayernum(socket_client->total());

	schedule(schedule_selector(GameScene::update));

	/*************************兵种移动************************/
	soldierMove = EventListenerTouchOneByOne::create();
	soldierMove->onTouchBegan = [this](Touch *touch, Event *event)
	{
		return true;
	};
	soldierMove->onTouchEnded = [this](Touch *touch, Event *event)
	{
		int s = _tiledMap1->convertTouchToNodeSpace(touch).x / 16;
		int t = ((100 * 16) - _tiledMap1->convertTouchToNodeSpace(touch).y) / 16;
		Apoint end(s, t);
		//log("%f %f", _tiledMap1->convertTouchToNodeSpace(touch).x, _tiledMap1->convertTouchToNodeSpace(touch).y);
		//log("%d       %d", end.getX(), end.getY());
		if (end.getX() < 0 || end.getX() > 99 || end.getY() < 0 || end.getY() > 99)
		{
			return;
		}
		for (auto &target : gamemanager->sid_map)
		{
			if (target.first % 4 == gamemanager->getPlayerID() % 4)
			{
				if (target.second->getSoldierType() == START_MINER)
				{
					continue;
				}
				if (!target.second->getifSelect())
				{
					target.second->stopAllActions();
					target.second->moveToPath.clear();
					gamemanager->genMoveMessage(target.second->moveToPath, target.second->getID(), target.second->getSoldierType());
					continue;
				}
				target.second->stopAllActions();
				target.second->moveToPath.clear();
				gamemanager->genMoveMessage(target.second->moveToPath, target.second->getID(), target.second->getSoldierType());
				int x = target.second->getPosition().x / 16;
				int y = ((100 * 16) - target.second->getPosition().y) / 16;
				Apoint start(x, y);
				//log("%f  %f", target->getPosition().x, target->getPosition().y);
				//log("%d   %d", start.getX(), start.getY());
				Astar pathFinder(100, 100, start, end);
				pathFinder.findPath();
				vector<Apoint> path = pathFinder.getPath();
				if (path.size() >= 2)
				{
					end.setX(path[path.size() - 2].getX());
					end.setY(path[path.size() - 2].getY());
				}
				for (auto it = path.begin(); it != path.end(); it++)
				{
					//log("%d,%d", it->getX(), it->getY());
					float x = (it->getX()) * 16;
					float y = (99.5 - it->getY()) * 16;
					target.second->moveToPath.push_back(Vec2(x, y));
				}
				//target.second->soldierAutoMove();
				gamemanager->genMoveMessage(target.second->moveToPath, target.second->getID(), target.second->getSoldierType());
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(soldierMove, _tiledMap1);
	//通知
	notice = Notice::create();
	addChild(notice, 40);
	notice->setAnchorPoint(Vec2(0, 0));
	notice->setPosition(10, visibleSize.height / 2);
	notice->setScale(0.7);
	notice->schedule(schedule_selector(Notice::update));
	gamemanager->setNotice(notice);


	//创建基地
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateBuildingMessage(START_BASE);
	start_flag = true;
	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建返回菜单
	/*auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 15);
	backLabel->setColor(Color3B::GREEN);
	auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;  //获得菜单宽度
	float back_y = backMenu->getContentSize().height; //获得菜单长度
	backMenu->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - back_y));
	auto mn = Menu::create(backMenu, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);*/

	//创建兵营菜单
	MenuItemImage *buildingMenu1 = MenuItemImage::create(CASERN, CASERN, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu1->setScale(1);
	float menu1_x = buildingMenu1->getContentSize().width;
	float menu1_y = buildingMenu1->getContentSize().height;
	buildingMenu1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 40));
	buildingMenu1->setTag(START_CASERN);
	buildingMenu1->setOpacity(128);
	Menu *bmn1 = Menu::create(buildingMenu1, NULL);
	bmn1->setPosition(Vec2::ZERO);
	this->addChild(bmn1, 20);
	auto buildingLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("兵营"), "华文行楷", 8);
	buildingLabel1->setColor(Color3B::GREEN);
	buildingLabel1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 40));
	this->addChild(buildingLabel1,30);

	//创建电厂菜单
	MenuItemImage *buildingMenu2 = MenuItemImage::create(ELECTRICSTATION, ELECTRICSTATION, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu2->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu2->setScale(1);
	float menu2_x = buildingMenu2->getContentSize().width;
	float menu2_y = buildingMenu2->getContentSize().height;
	buildingMenu2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 80));
	buildingMenu2->setTag(START_ELECTRICSTATION);
	buildingMenu2->setOpacity(128);
	Menu *bmn2 = Menu::create(buildingMenu2, NULL);
	bmn2->setPosition(Vec2::ZERO);
	this->addChild(bmn2, 20);
	auto buildingLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("电厂"), "华文行楷", 8);
	buildingLabel2->setColor(Color3B::GREEN);
	buildingLabel2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height -80));
	this->addChild(buildingLabel2, 30);

	//创建战车工厂菜单
	MenuItemImage *buildingMenu3 = MenuItemImage::create(TANKFACTORY, TANKFACTORY, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu3->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu3->setScale(1);
	float menu3_x = buildingMenu3->getContentSize().width;
	float menu3_y = buildingMenu3->getContentSize().height;
	buildingMenu3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 120));
	buildingMenu3->setTag(START_TANKFACTORY);
	buildingMenu3->setOpacity(128);
	Menu *bmn3 = Menu::create(buildingMenu3, NULL);
	bmn3->setPosition(Vec2::ZERO);
	this->addChild(bmn3, 20);
	auto buildingLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("战车工厂"), "华文行楷", 8);
	buildingLabel3->setColor(Color3B::GREEN);
	buildingLabel3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 120));
	this->addChild(buildingLabel3, 30);

	//创建矿场菜单
	MenuItemImage *buildingMenu4 = MenuItemImage::create(OREYARD, OREYARD, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu4->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu4->setScale(1);
	float menu4_x = buildingMenu4->getContentSize().width;
	float menu4_y = buildingMenu4->getContentSize().height;
	buildingMenu4->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 160));
	buildingMenu4->setTag(START_OREYARD);
	buildingMenu4->setOpacity(128);
	Menu *bmn4 = Menu::create(buildingMenu4, NULL);
	bmn4->setPosition(Vec2::ZERO);
	this->addChild(bmn4, 20);
	auto buildingLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("矿场"), "华文行楷", 8);
	buildingLabel4->setColor(Color3B::GREEN);
	buildingLabel4->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 160));
	this->addChild(buildingLabel4, 30);
	

	//创建矿工菜单
	MenuItemImage *soldierMenu1 = MenuItemImage::create(MINER1, MINER1, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu1->setScale(1.2);
	soldierMenu1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 200));
	soldierMenu1->setTag(START_MINER);
	soldierMenu1->setOpacity(128);
	Menu *smn1 = Menu::create(soldierMenu1, NULL);
	smn1->setPosition(Vec2::ZERO);
	this->addChild(smn1, 20);
	auto soldierLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("矿工"), "华文行楷", 8);
	soldierLabel1->setColor(Color3B::GREEN);
	soldierLabel1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 200));
	this->addChild(soldierLabel1,30);

	//警察菜单
	MenuItemImage *soldierMenu2 = MenuItemImage::create(POLICEMAN1, POLICEMAN1, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu2->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu2->setScale(1.2);
	soldierMenu2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 225));
	soldierMenu2->setTag(START_POLICEMAN);
	soldierMenu2->setOpacity(128);
	Menu *smn2 = Menu::create(soldierMenu2, NULL);
	smn2->setPosition(Vec2::ZERO);
	this->addChild(smn2, 20);
	auto soldierLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("警察"), "华文行楷", 8);
	soldierLabel2->setColor(Color3B::GREEN);
	soldierLabel2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 225));
	this->addChild(soldierLabel2, 30);

	//坦克菜单
	MenuItemImage *soldierMenu3 = MenuItemImage::create(TANK1, TANK1, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu3->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu3->setScale(1.2);
	soldierMenu3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 250));
	soldierMenu3->setTag(START_TANK);
	soldierMenu3->setOpacity(128);
	Menu *smn3 = Menu::create(soldierMenu3, NULL);
	smn3->setPosition(Vec2::ZERO);
	this->addChild(smn3, 20);
	auto soldierLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("坦克"), "华文行楷", 8);
	soldierLabel3->setColor(Color3B::GREEN);
	soldierLabel3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 250));
	this->addChild(soldierLabel3, 30);

	//战士菜单
	MenuItemImage *soldierMenu4 = MenuItemImage::create(WARRIOR1, WARRIOR1, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu4->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu4->setScale(1.2);
	soldierMenu4->setPosition(Vec2(visibleSize.width - 20, origin.y + visibleSize.height - 275));
	soldierMenu4->setTag(START_WARRIOR);
	soldierMenu4->setOpacity(128);
	Menu *smn4 = Menu::create(soldierMenu4, NULL);
	smn4->setPosition(Vec2::ZERO);
	this->addChild(smn4, 20);
	auto soldierLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("战士"), "华文行楷", 8);
	soldierLabel4->setColor(Color3B::GREEN);
	soldierLabel4->setPosition(Vec2(visibleSize.width - 20, origin.y + visibleSize.height - 275));
	this->addChild(soldierLabel4, 30);

	//士兵升级菜单
	auto updateLabel = LabelTTF::create(MyUtility::gbk_2_utf8("士兵升级"), "华文行楷", 12);
	updateLabel->setColor(Color3B::GREEN);
	auto updateMenu = MenuItemLabel::create(updateLabel, CC_CALLBACK_1(GameScene::soldierUpdate, this));
	float update_x = updateMenu->getContentSize().width;  //获得菜单宽度
	float update_y = updateMenu->getContentSize().height; //获得菜单长度
	updateMenu->setPosition(Vec2(visibleSize.width - 25, origin.y + 85));
	auto up = Menu::create(updateMenu, NULL);
	up->setPosition(Vec2::ZERO);
	this->addChild(up);


	//建筑物接触检测监听器
	spriteContactListener = EventListenerPhysicsContact::create();
	spriteContactListener->onContactBegin = [this](PhysicsContact &contact)
	{
		Sprite *SpriteA = (Sprite *)(contact.getShapeA()->getBody()->getNode());
		Sprite *SpriteB = (Sprite *)(contact.getShapeB()->getBody()->getNode());
		if (!SpriteA || !SpriteB)
		{
			return false;
		}
		//此处为检测兵种接触
		/*if (SpriteA->getTag() == GameSceneNodeTagSoldier && SpriteB->getTag() == GameSceneNodeTagSoldier)
		{
			auto soldierSpriteA = dynamic_cast<Soldiers *>(SpriteA);
			auto soldierSpriteB = dynamic_cast<Soldiers *>(SpriteB);
			if (!soldierSpriteA->getifSelect() && !soldierSpriteB->getifSelect())
			{
				//通过随机数重新设置位置
				Size s = soldierSpriteA->getContentSize();
				Vec2 rand = soldierSpriteB->getPosition() + (Vec2(s.width, s.height) * (1 + CCRANDOM_0_1()));
				soldierSpriteA->setPosition(rand);
				return false;
			}
			if (!soldierSpriteA->getifSelect() && soldierSpriteB->getifSelect())
			{
			Size s = soldierSpriteA->getContentSize();
			Vec2 rand = soldierSpriteA->getPosition() + (Vec2(s.width, s.height) * (1 + CCRANDOM_0_1()));
			soldierSpriteB->setPosition(rand);
			return false;
			}
			return false;
			Size s = soldierSpriteA->getContentSize();
			Vec2 rand = soldierSpriteB->getPosition() + (Vec2(s.width, s.height) * (1 + CCRANDOM_0_1()));
			soldierSpriteA->setPosition(rand);
			return false;
		}*/
		if (SpriteA->getTag() == GameSceneNodeTagSoldier && SpriteB->getTag() == GameSceneNodeTagBuilding)
		{
			auto soldierSpriteA = dynamic_cast<Soldiers *>(SpriteA);
			int ax = soldierSpriteA->getPosition().x / 16;
			int ay = (100 * 16 - soldierSpriteA->getPosition().y) / 16;
			float as = ax * 16;
			float at = (99.5 - ay) * 16;
			soldierSpriteA->stopAllActions();
			MoveTo *Amoveto = MoveTo::create(0.1f, Vec2(as, at));
			soldierSpriteA->runAction(Amoveto);
		}
		if (SpriteA->getTag() == GameSceneNodeTagBuilding && SpriteB->getTag() == GameSceneNodeTagSoldier)
		{
			auto soldierSpriteB = dynamic_cast<Soldiers *>(SpriteB);
			int bx = soldierSpriteB->getPosition().x / 16;
			int by = (100 * 16 - soldierSpriteB->getPosition().y) / 16;
			float bs = bx * 16;
			float bt = (99.5 - by) * 16;
			soldierSpriteB->stopAllActions();
			MoveTo *Bmoveto = MoveTo::create(0.1f, Vec2(bs, bt));
			soldierSpriteB->runAction(Bmoveto);
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(spriteContactListener, 20);

	//实时刷新金钱
	this->Money = 7000;
	__String *currentMoney = __String::createWithFormat("Money:%d", this->Money);
	auto MoneyLabel = LabelTTF::create(currentMoney->getCString(), "Marker Felt", 15);
	float Money_x = MoneyLabel->getContentSize().width;
	float Money_y = MoneyLabel->getContentSize().height;
	MoneyLabel->setPosition(origin.x + visibleSize.width - Money_x * 0.75, origin.y + Money_y);
	MoneyLabel->setColor(Color3B::RED);
	this->addChild(MoneyLabel, 20, GameSceneNodeTagMoney);
	this->schedule(schedule_selector(GameScene::moneyUpdate), 0.1f, CC_REPEAT_FOREVER, 0);

	this->Power = 4000;
	__String *currentPower = __String::createWithFormat("Power:%d", this->Power);
	auto PowerLabel = LabelTTF::create(currentPower->getCString(), "Marker Felt", 15);
	float Power_x = PowerLabel->getContentSize().width;
	float Power_y = PowerLabel->getContentSize().height;
	PowerLabel->setPosition(origin.x + visibleSize.width - Power_x * 0.75, origin.y + Power_y + 20);
	PowerLabel->setColor(Color3B::RED);
	this->addChild(PowerLabel, 20, GameSceneNodeTagPower);
	this->schedule(schedule_selector(GameScene::powerUpdate), 0.1f, CC_REPEAT_FOREVER, 0);
}

void GameScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouse_event);
	Director::getInstance()->getEventDispatcher()->removeEventListener(keyboard_listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(spriteContactListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouseRectListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(soldierMove);
	this->unschedule(schedule_selector(GameScene::moneyUpdate));
	this->unschedule(schedule_selector(GameScene::update));
	if (socket_client)
	{
		socket_client->close();
		delete socket_client;
		socket_client = nullptr;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	/*if (socket_server)
	{
		socket_server->close();
		delete socket_server;
		socket_server = nullptr;
	}*/
	if (_onExitCallback)
		_onExitCallback();
	if (_componentContainer && !_componentContainer->isEmpty())
	{
		_componentContainer->onExit();
	}
	this->pause();
	_running = false;
	for (const auto &child : _children)
		child->onExit();
}

//返回MenuScene
void GameScene::backToMenuScene(Ref *pSender)
{
	gamemanager->genGobackMessgage(playerid);
}

//选择建筑物建造
void GameScene::buildingsCreate(Ref *pSender)
{
	MenuItem *mnitem = (MenuItem *)pSender;
	switch (mnitem->getTag())
	{
		case START_CASERN:
		{
			if (Money < CASERN_PRICE)//判断钱是否足够
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 1 &&( _tiledMap1->getChildByName("casern1") || !_tiledMap1->getChildByName("base1")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 2 && (_tiledMap1->getChildByName("casern2") || !_tiledMap1->getChildByName("base2")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 3 && (_tiledMap1->getChildByName("casern3") || !_tiledMap1->getChildByName("base3")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 4 && (_tiledMap1->getChildByName("casern4") || !_tiledMap1->getChildByName("base4")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			//Money -= CASERN_PRICE;
			//建筑物准备定时器，每种建筑物准备时间不同
			this->scheduleOnce(schedule_selector(GameScene::casernReady), 2.0f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
		case START_ELECTRICSTATION:
		{
			if (Money < ELECTRICSTATION_PRICE)//判断钱是否足够
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 1 &&( _tiledMap1->getChildByName("electricStation1")||!_tiledMap1->getChildByName("base1")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 2 && (_tiledMap1->getChildByName("electricStation2") || !_tiledMap1->getChildByName("base2")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 3 && (_tiledMap1->getChildByName("electricStation3") || !_tiledMap1->getChildByName("base3")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 4 && (_tiledMap1->getChildByName("electricStation4") || !_tiledMap1->getChildByName("base4")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			//Money -= ELECTRICSTATION_PRICE;
			//建筑物准备定时器，每种建筑物准备时间不同
			this->scheduleOnce(schedule_selector(GameScene::electricStationReady), 1.8f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
		case START_TANKFACTORY:
		{
			if (Money < TANKFACTORY_PRICE)      //判断钱是否足够
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 1 &&( _tiledMap1->getChildByName("tankFactory1") || !_tiledMap1->getChildByName("base1")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 2 && (_tiledMap1->getChildByName("tankFactory2") || !_tiledMap1->getChildByName("base2")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 3 && (_tiledMap1->getChildByName("tankFactory3") || !_tiledMap1->getChildByName("base3")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 4 && (_tiledMap1->getChildByName("tankFactory4") || !_tiledMap1->getChildByName("base4")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			//Money -= TANKFACTORY_PRICE;
			this->scheduleOnce(schedule_selector(GameScene::tankFactoryReady), 2.5f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
		case START_OREYARD:
		{
			if (Money < OREYARD_PRICE)         //判断钱是否足够
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 1 &&( _tiledMap1->getChildByName("oreyard1") || !_tiledMap1->getChildByName("base1")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 2 && (_tiledMap1->getChildByName("oreyard2") || !_tiledMap1->getChildByName("base2")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 3 && (_tiledMap1->getChildByName("oreyard3") || !_tiledMap1->getChildByName("base3")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			if (playerid == 4 && (_tiledMap1->getChildByName("oreyard4") || !_tiledMap1->getChildByName("base4")))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			//Money -= OREYARD_PRICE;
			this->scheduleOnce(schedule_selector(GameScene::oreYardReady), 1.5f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
	}
}

void GameScene::soldierUpdate(Ref *pSender)
{
	MenuItem *mnitm = (MenuItem *)pSender;
	if (Power < POWER_PRICE)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
		return;
	}
	else
	{
		this->scheduleOnce(schedule_selector(GameScene::soldierUpdateReady), 0.01f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
	}
}

void GameScene::soldiersCreate(Ref *pSender)
{
	MenuItem *mnitm = (MenuItem *)pSender;
	switch (mnitm->getTag())
	{
	case START_MINER:
	{
		if (Money < MINER_PRICE )
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 1 && (!_tiledMap1->getChildByName("oreyard1") || !_tiledMap1->getChildByName("base1")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 2 && (!_tiledMap1->getChildByName("oreyard2") || !_tiledMap1->getChildByName("base2")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 3 && (!_tiledMap1->getChildByName("oreyard3") || !_tiledMap1->getChildByName("base3")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 4 && (!_tiledMap1->getChildByName("oreyard4") || !_tiledMap1->getChildByName("base4")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		//Money -= MINER_PRICE;
		//准备定时器
		this->scheduleOnce(schedule_selector(GameScene::minerReady), 1.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
		break;
	}
	case START_POLICEMAN:
	{
		if (Money < POLICEMAN_PRICE )
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 1 && (!_tiledMap1->getChildByName("casern1") || !_tiledMap1->getChildByName("base1")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 2 && (!_tiledMap1->getChildByName("casern2") || !_tiledMap1->getChildByName("base2")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 3 && (!_tiledMap1->getChildByName("casern3") || !_tiledMap1->getChildByName("base3")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 4 && (!_tiledMap1->getChildByName("casern4") || !_tiledMap1->getChildByName("base4")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		//Money -= POLICEMAN_PRICE;
		//准备定时器
		this->scheduleOnce(schedule_selector(GameScene::policemanReady), 1.5f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
		break;
	}
	case START_TANK:
	{
		if (Money < TANK_PRICE )
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 1 &&( !_tiledMap1->getChildByName("tankFactory1") || !_tiledMap1->getChildByName("base1")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 2 && (!_tiledMap1->getChildByName("tankFactory2") || !_tiledMap1->getChildByName("base2")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 3 && (!_tiledMap1->getChildByName("tankFactory3") || !_tiledMap1->getChildByName("base3")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 4 && (!_tiledMap1->getChildByName("tankFactory4") || !_tiledMap1->getChildByName("base4")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		//Money -= TANK_PRICE;
		this->scheduleOnce(schedule_selector(GameScene::tankReady), 2.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
		break;
	}
	case START_WARRIOR:
	{
		if (Money < WARRIOR_PRICE )
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 1 &&( !_tiledMap1->getChildByName("casern1") || !_tiledMap1->getChildByName("base1")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 2 && (!_tiledMap1->getChildByName("casern2") || !_tiledMap1->getChildByName("base2")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 3 && (!_tiledMap1->getChildByName("casern3") || !_tiledMap1->getChildByName("base3")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		if (playerid == 4 && (!_tiledMap1->getChildByName("casern4") || !_tiledMap1->getChildByName("base4")))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
			break;
		}
		//Money -= WARRIOR_PRICE;
		this->scheduleOnce(schedule_selector(GameScene::warriorReady), 2.0f);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
		break;
	}
	}
}

//兵种绘制
void GameScene::minerReady(float dt)
{
	Money -= MINER_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateSoldierMessage(START_MINER);
}
void GameScene::policemanReady(float dt)
{
	Money -= POLICEMAN_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateSoldierMessage(START_POLICEMAN);
}
void GameScene::warriorReady(float dt)
{
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateSoldierMessage(START_WARRIOR);
	Money -= WARRIOR_PRICE;
}
void GameScene::tankReady(float dt)
{
	Money -= TANK_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateSoldierMessage(START_TANK);
}

void GameScene::soldierUpdateReady(float dt)
{
	Power -= POWER_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	gamemanager->genSoldierUpdateMessage();
}

//建筑物绘制
void GameScene::casernReady(float dt)
{
	Money -= CASERN_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateBuildingMessage(START_CASERN);
}

void GameScene::electricStationReady(float dt)
{
	Money -= ELECTRICSTATION_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateBuildingMessage(START_ELECTRICSTATION);
}
void GameScene::tankFactoryReady(float dt)
{
	Money -= TANKFACTORY_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateBuildingMessage(START_TANKFACTORY);
}
void GameScene::oreYardReady(float dt)
{
	Money -= OREYARD_PRICE;
	auto _player_id = gamemanager->getPlayerID();
	auto _id = gamemanager->getnextID();
	gamemanager->genCreateBuildingMessage(START_OREYARD);
}

void GameScene::moneyUpdate(float dt)
{
	frame_cnt3++;
	if (frame_cnt3 % KEYFRAME3 == 0)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//将上一个标签移出
		if (this->getChildByTag(GameSceneNodeTagMoney))
		{
			this->removeChildByTag(GameSceneNodeTagMoney);
		}
		//创建新标签
		if (this->Money <= 0)
		{
			this->Money = 0;
		}
		__String *currentMoney = __String::createWithFormat("Money:%d", (this->Money)++);
		auto MoneyLabel = LabelTTF::create(currentMoney->getCString(), "Marker Felt", 15);
		float Money_x = MoneyLabel->getContentSize().width;
		float Money_y = MoneyLabel->getContentSize().height;
		MoneyLabel->setPosition(origin.x + visibleSize.width - Money_x * 0.75, origin.y + Money_y);
		MoneyLabel->setColor(Color3B::RED);
		this->addChild(MoneyLabel, 20, GameSceneNodeTagMoney);
	}
	else
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//将上一个标签移出
		if (this->getChildByTag(GameSceneNodeTagMoney))
		{
			this->removeChildByTag(GameSceneNodeTagMoney);
		}
		//创建新标签
		if (this->Money <= 0)
		{
			this->Money = 0;
		}
		__String *currentMoney = __String::createWithFormat("Money:%d", (this->Money));
		auto MoneyLabel = LabelTTF::create(currentMoney->getCString(), "Marker Felt", 15);
		float Money_x = MoneyLabel->getContentSize().width;
		float Money_y = MoneyLabel->getContentSize().height;
		MoneyLabel->setPosition(origin.x + visibleSize.width - Money_x * 0.75, origin.y + Money_y);
		MoneyLabel->setColor(Color3B::RED);
		this->addChild(MoneyLabel, 20, GameSceneNodeTagMoney);
	}
}

void GameScene::powerUpdate(float dt)
{
	frame_cnt2++;
	if (frame_cnt2 % KEYFRAME2 == 0)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//将上一个标签移出
		if (this->getChildByTag(GameSceneNodeTagPower))
		{
			this->removeChildByTag(GameSceneNodeTagPower);
		}
		//创建新标签
		if (this->Power <= 0)
		{
			this->Power = 0;
		}
		if ((gettiledMap()->getChildByName("electricStation1") && playerid == 1)
			|| (gettiledMap()->getChildByName("electricStation2") && playerid == 2)
			|| (gettiledMap()->getChildByName("electricStation3") && playerid == 3)
			|| (gettiledMap()->getChildByName("electricStation4") && playerid == 4))
		{
			__String *currentPower = __String::createWithFormat("Power:%d", (this->Power) += 15);
			auto PowerLabel = LabelTTF::create(currentPower->getCString(), "Marker Felt", 15);
			float Power_x = PowerLabel->getContentSize().width;
			float Power_y = PowerLabel->getContentSize().height;
			PowerLabel->setPosition(origin.x + visibleSize.width - Power_x * 0.75, origin.y + Power_y + 20);
			PowerLabel->setColor(Color3B::RED);
			this->addChild(PowerLabel, 20, GameSceneNodeTagPower);
		}
		else
		{
			__String *currentPower = __String::createWithFormat("Power:%d", (this->Power) += 2);
			auto PowerLabel = LabelTTF::create(currentPower->getCString(), "Marker Felt", 15);
			float Power_x = PowerLabel->getContentSize().width;
			float Power_y = PowerLabel->getContentSize().height;
			PowerLabel->setPosition(origin.x + visibleSize.width - Power_x * 0.75, origin.y + Power_y + 20);
			PowerLabel->setColor(Color3B::RED);
			this->addChild(PowerLabel, 20, GameSceneNodeTagPower);
		}
	}
	else
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		//将上一个标签移出
		if (this->getChildByTag(GameSceneNodeTagPower))
		{
			this->removeChildByTag(GameSceneNodeTagPower);
		}
		//创建新标签
		if (this->Power <= 0)
		{
			this->Power = 0;
		}
		__String *currentPower = __String::createWithFormat("Power:%d", (this->Power));
		auto PowerLabel = LabelTTF::create(currentPower->getCString(), "Marker Felt", 15);
		float Power_x = PowerLabel->getContentSize().width;
		float Power_y = PowerLabel->getContentSize().height;
		PowerLabel->setPosition(origin.x + visibleSize.width - Power_x * 0.75, origin.y + Power_y + 20);
		PowerLabel->setColor(Color3B::RED);
		this->addChild(PowerLabel, 20, GameSceneNodeTagPower);
	}
}

void GameScene::update(float dt)
{
	frame_cnt1++;
	scrollMap();
	for (auto &b : gamemanager->bid_map)
	{
		if (b.second->isScheduled(schedule_selector(Buildings::update)))
		{
			continue;
		}
		b.second->schedule(schedule_selector(Buildings::update));
	}
	for (auto &s : gamemanager->sid_map)
	{
		if (s.second->isScheduled(schedule_selector(Soldiers::update)))
		{
			continue;
		}
		s.second->schedule(schedule_selector(Soldiers::update));
	}
	if (frame_cnt1 % KEYFRAME1 == 0 && start_flag)
	{
		gamemanager->updateGameState();
		checkWinOrLose();
	}
}

void GameScene::scrollMap()
{
		auto mapCenter = _tiledMap1->getPosition();
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		int horizontal_state, vertical_state;
		horizontal_state = (origin.x + visibleSize.width - BOX_EDGE_WITDH_SMALL < crusor_position.x)
			+ (origin.x + visibleSize.width - BOX_EDGE_WITDH < crusor_position.x)
			- (origin.x + BOX_EDGE_WITDH_SMALL > crusor_position.x)
			- (origin.x + BOX_EDGE_WITDH > crusor_position.x);
		vertical_state = (origin.y + visibleSize.height - BOX_EDGE_WITDH_SMALL < crusor_position.y)
			+ (origin.y + visibleSize.height - BOX_EDGE_WITDH < crusor_position.y)
			- (origin.y + BOX_EDGE_WITDH_SMALL > crusor_position.y)
			- (origin.y + BOX_EDGE_WITDH > crusor_position.y);
		Vec2 scroll(0, 0);
		scroll += Vec2(-SCROLL_LENGTH, 0)*horizontal_state;
		scroll += Vec2(0, -SCROLL_LENGTH)*vertical_state;
		mapCenter += scroll;
		if (_tiledMap1->getBoundingBox().containsPoint((-scroll) + Director::getInstance()->getVisibleSize())
			&& _tiledMap1->getBoundingBox().containsPoint(-scroll))
			_tiledMap1->setPosition(mapCenter);
}

void GameScene::onMouseMove(Event *event)
{
	EventMouse* e = static_cast<EventMouse*>(event);
	crusor_position = Vec2(e->getCursorX(), e->getCursorY());
}

bool GameScene::mouseRectOnTouchBegan(Touch *pTouch, Event *event)
{
	Point touch = pTouch->getLocation();
	last_touch = touch;
	mouseRect->start = touch - _tiledMap1->getPosition();
	mouseRect->touch_start = touch;
	mouseRect->touch_end = touch;
	mouseRect->schedule(schedule_selector(MouseRect::update));
	return true;
}

void GameScene::mouseRectOnTouchMoved(Touch *pTouch, Event *event)
{
	Point touch = pTouch->getLocation();
	this->mouseRect->touch_end = touch;
	this->mouseRect->clear();
	this->mouseRect->setVisible(true);
}

void GameScene::mouseRectOnTouchEnded(Touch *pTouch, Event *event)
{
	Point touch = pTouch->getLocation();
	this->mouseRect->setVisible(false);
	if (this->mouseRect->isScheduled(schedule_selector(MouseRect::update)))
	{
		this->mouseRect->unschedule(schedule_selector(MouseRect::update));
	}
	mouseRect->end = touch - _tiledMap1->getPosition();
	Point maptouch = mouseRect->end;
	Point last_maptouch = mouseRect->start;
	if ((maptouch - last_maptouch).length() < MIN_SELECT_RECT_SIZE)
	{
		auto target = dynamic_cast<Soldiers *>(event->getCurrentTarget());
		if (!target)
		{
			return;
		}
		if (target->getTag() == GameSceneNodeTagBuilding || target->getTag() == GameSceneNodeTagSoldier)
		{
			///////////////
			//缺少血条显示
			///////////////
			log("search");
			if (target->getTag() == GameSceneNodeTagSoldier && target->getifSelect())
			{
				target->setifSelect(SELECT_ON);
			}
		}
	}
	else
	{
		Rect select_rect = { MIN(last_maptouch.x, maptouch.x), MIN(last_maptouch.y, maptouch.y),
			abs(last_maptouch.x - maptouch.x), abs(last_maptouch.y - maptouch.y) };
		for (auto &target_2 : gamemanager->sid_map)
		{
			if (target_2.first % 4 == gamemanager->getPlayerID() % 4)
			{
				//////////////
				if (target_2.second->getSoldierType() == START_MINER
					&& select_rect.containsPoint(target_2.second->getPosition()))
				{
					target_2.second->displayHpBar();
					target_2.second->setifSelect(SELECT_OFF);
					continue;
				}
				if (target_2.second->getSoldierType() == START_MINER
					&& !select_rect.containsPoint(target_2.second->getPosition()))
				{
					target_2.second->hideHpBar();
					target_2.second->setifSelect(SELECT_OFF);
					continue;
				}
				//////////////
				target_2.second->stopAllActions();
				target_2.second->moveToPath.clear();
				gamemanager->genMoveMessage(target_2.second->moveToPath, target_2.second->getID(), target_2.second->getSoldierType());
				if (!select_rect.containsPoint(target_2.second->getPosition()))
				{
					target_2.second->hideHpBar();
					target_2.second->setifSelect(SELECT_OFF);
					continue;
				}
				target_2.second->displayHpBar();
				target_2.second->setifSelect(SELECT_ON);
			}
		}
		for (auto &target_1 : gamemanager->bid_map)
		{
			if (target_1.first % 4 == gamemanager->getPlayerID() % 4)
			{
				if (!select_rect.containsPoint(target_1.second->getPosition()))
				{
					target_1.second->hideHpBar();
					continue;
				}
				target_1.second->displayHpBar();
			}
		}
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* pEvent)
{
	auto mapCenter = _tiledMap1->getPosition();
	Director::getInstance()->getVisibleSize();
	switch (keycode)
	{
		//W 上移
	case EventKeyboard::KeyCode::KEY_W:
		mapCenter += Vec2(0, -100);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(0, 100) + Director::getInstance()->getVisibleSize()))
			_tiledMap1->setPosition(mapCenter);
		break;
		//A 左移
	case EventKeyboard::KeyCode::KEY_A:
		mapCenter += Vec2(100, 0);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(-100, 0)))
			_tiledMap1->setPosition(mapCenter);
		break;
		//S 下移
	case EventKeyboard::KeyCode::KEY_S:
		mapCenter += Vec2(0, 100);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(0, -100)))
			_tiledMap1->setPosition(mapCenter);
		break;
		//D 右移
	case EventKeyboard::KeyCode::KEY_D:
		mapCenter += Vec2(-100, 0);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(100, 0) + Director::getInstance()->getVisibleSize()))
			_tiledMap1->setPosition(mapCenter);
		break;
		//关闭或开启鼠标移动屏幕
	case EventKeyboard::KeyCode::KEY_P:
		if (p_flag)
		{
			log("map move by mouse close");
			p_flag = false;
			Director::getInstance()->getEventDispatcher()->removeEventListener(mouse_event);
			break;
		}
		log("map move by mouse open");
		p_flag = true;
		mouse_event = EventListenerMouse::create();
		mouse_event->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_event, 1);
		break;
		//按下control鼠标可以或者不可以画出矩形框
	case EventKeyboard::KeyCode::KEY_CTRL:
		if (ctrl_flag)
		{
			log("mouse Rect unusable");
			ctrl_flag = false;
			Director::getInstance()->getEventDispatcher()->removeEventListener(mouseRectListener);
			break;
		}
		log("mouse Rect usable");
		ctrl_flag = true;
		mouseRectListener = EventListenerTouchOneByOne::create();
		mouseRectListener->onTouchBegan = CC_CALLBACK_2(GameScene::mouseRectOnTouchBegan, this);
		mouseRectListener->onTouchMoved = CC_CALLBACK_2(GameScene::mouseRectOnTouchMoved, this);
		mouseRectListener->onTouchEnded = CC_CALLBACK_2(GameScene::mouseRectOnTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseRectListener, this);
		break;
		//空格 返回基地
	case EventKeyboard::KeyCode::KEY_SPACE:
		focusOnBase();
		break;
	default:
		break;
	}
}


void GameScene::setMapType(int maptype)
{
	if (maptype == 1)
	{
		mapType = 1;
	}
	else
	{
		mapType = 2;
	}
}

void GameScene::focusOn(Point pos)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 map_vec = pos - visibleSize / 2;
	if (_tiledMap1->getBoundingBox().size.height < map_vec.y + visibleSize.height)
		map_vec.y = _tiledMap1->getBoundingBox().size.height - visibleSize.height;
	if (_tiledMap1->getBoundingBox().size.width < map_vec.x + visibleSize.width)
		map_vec.x = _tiledMap1->getBoundingBox().size.width - visibleSize.width;
	if (map_vec.x < 0)
		map_vec.x = 0;
	if (map_vec.y < 0)
		map_vec.y = 0;
	_tiledMap1->setPosition(Point(0, 0) - map_vec);
}

void GameScene::focusOnBase()
{
	if (playerid == 1)
	{
		focusOn(Vec2(0, 0));
	}
	if (playerid == 2)
	{
		focusOn(Vec2(1600, 0));
	}
	if (playerid == 3)
	{
		focusOn(Vec2(1600, 1600));
	}
	if (playerid == 4)
	{
		focusOn(Vec2(0, 1600));
	}
}

void GameScene::win()
{
	log("win");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto win_label = LabelBMFont::create("You Win!", "fonts/NoticeFont.fnt");
	win_label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - win_label->getContentSize().height));
	addChild(win_label, 100);
	//notice->displayNotice("You Win!");
	end_flag = true;
}

void GameScene::lose()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto lose_label = LabelBMFont::create("You Lose!", "fonts/NoticeFont.fnt");
	lose_label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - lose_label->getContentSize().height));
	addChild(lose_label, 100);
	//notice->displayNotice("You Lose");
	end_flag = true;
}

void GameScene::checkWinOrLose()
{
	int buildingnum = 0;
	if (_tiledMap1->getChildByName("base1"))
	{
		buildingnum++;
	}
	if (_tiledMap1->getChildByName("base2"))
	{
		buildingnum++;
	}
	if (_tiledMap1->getChildByName("base3"))
	{
		buildingnum++;
	}
	if (_tiledMap1->getChildByName("base4"))
	{
		buildingnum++;
	}
	if (playerid == 1 && !_tiledMap1->getChildByName("base1"))
	{
		lose();
	}
	if (playerid == 2 && !_tiledMap1->getChildByName("base2"))
	{
		lose();
	}
	if (playerid == 3 && !_tiledMap1->getChildByName("base3"))
	{
		lose();
	}
	if (playerid == 4 && !_tiledMap1->getChildByName("base4"))
	{
		lose();
	}
	if (playerid == 1 && _tiledMap1->getChildByName("base1") && buildingnum == 1 && playernum >= 2)
	{
		win();
	}
	if (playerid == 2 && _tiledMap1->getChildByName("base2") && buildingnum == 1 && playernum >= 2)
	{
		win();
	}
	if (playerid == 3 && _tiledMap1->getChildByName("base3") && buildingnum == 1 && playernum >= 2)
	{
		win();
	}
	if (playerid == 4 && _tiledMap1->getChildByName("base4") && buildingnum == 1 && playernum >= 2)
	{
		win();
	}
}

void Notice::update(float f)
{
	if (++timer == ntc_life)
	{
		setString("");
		ntc_life = 0;
		timer = 0;
		unschedule(schedule_selector(Notice::update));
	}
}
void Notice::displayNotice(std::string ntc, int _ntc_life)
{
	setString(ntc);
	ntc_life = _ntc_life;
	timer = 0;
	if (!isScheduled(schedule_selector(Notice::update)))
		schedule(schedule_selector(Notice::update));
}
void Notice::displayNotice(std::string ntc)
{
	setString(ntc);
	ntc_life = 0;
	timer = 0;
	if (isScheduled(schedule_selector(Notice::update)))
		unschedule(schedule_selector(Notice::update));
}
bool Notice::init()
{
	ntc_life = 100;
	return true;
}


	
