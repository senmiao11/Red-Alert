#include"GameScene.h"


Scene * GameScene::createScene()
{
	Scene *scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/************地图************/
	//游戏地图
	_tiledMap1 = TMXTiledMap::create(GameMap1);
	addChild(_tiledMap1, -1);
	//地图更新
	schedule(schedule_selector(GameScene::update));
	//地图移动的鼠标事件
	auto mouse_event = EventListenerMouse::create();
	mouse_event->onMouseMove = [&](Event *event)
	{
		EventMouse* e = static_cast<EventMouse*>(event);
		crusor_position = Vec2(e->getCursorX(), e->getCursorY());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_event, 1);
	//地图移动的键盘事件
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_listener, this);

	//创建一个基地精灵
	Buildings *base = Buildings::creatWithBuildingTypes(START_BASE);
	base->setAnchorPoint(Vec2(0, 0));
	base->setScale(0.3);
	base->setPosition(Vec2(origin.x + visibleSize.width * -0.03, origin.y + visibleSize.height *-0.06));
	addChild(base, 10, GameSceneNodeTagBuilding);

	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建返回菜单
	auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 15);
	auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;  //获得菜单宽度
	float back_y = backMenu->getContentSize().height; //获得菜单长度
	backMenu->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - back_y));
	auto mn = Menu::create(backMenu, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	//创建一个选择建筑物造菜单，目前只有兵营，暂用基地图代替
	MenuItemImage *buildingMenu = MenuItemImage::create(BASE, BASE, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu->setScale(0.2);
	float menu_x = buildingMenu->getContentSize().width;
	float menu_y = buildingMenu->getContentSize().height;
	buildingMenu->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - menu_y / 6));
	buildingMenu->setTag(CASERN);
	buildingMenu->setOpacity(128);
	Menu *bmn = Menu::create(buildingMenu, NULL);
	bmn->setPosition(Vec2::ZERO);
	this->addChild(bmn, 20);

	//建筑物移动监听器
	//原本写在这个位置的
	//注册时用的  ....->...(监听器，this->getchildbytag(GameSceneNodeBuilding))
	//但无法移动
	/////////////////



	//实时刷新金钱
	this->Money = 4000;
	this->schedule(schedule_selector(GameScene::moneyUpdate), 1.0f, CC_REPEAT_FOREVER, 0);

}

void GameScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(Buildings::touchBuildingListener);

	this->unschedule(schedule_selector(GameScene::moneyUpdate));
}

//返回MenuScene
void GameScene::backToMenuScene(Ref *pSender)
{
	Scene *sc = Scene::create();
	auto layer = MenuScene::create();
	sc->addChild(layer);

	auto reScene = TransitionSplitRows::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}

//选择建筑物建造
void GameScene::buildingsCreate(Ref *pSender)
{
	MenuItem *mnitem = (MenuItem *)pSender;
	switch (mnitem->getTag())
	{
		case CASERN:
		{
			if (Money < CASERN_PRICE)//判断前是否足够
			{
				break;
			}
			Money -= CASERN_PRICE;
			//建筑物准备定时器，每种建筑物准备时间不同
			this->scheduleOnce(schedule_selector(GameScene::casernReady), 2.0f);
			break;
		}
		//////////
		//待扩充
		//////////
	}

}

void GameScene::casernReady(float dt)
{
	//通过Buildings类来创建建筑物
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto casern = Buildings::creatWithBuildingTypes(CASERN);
	casern->setAnchorPoint(Vec2(0.5, 0.5));
	casern->setScale(0.2);
	float building_x = casern->getContentSize().width;
	float building_y = casern->getContentSize().height;
	casern->setPosition(Vec2(visibleSize.width - building_x, visibleSize.height - building_y / 6));
	this->addChild(casern, 10, GameSceneNodeTagBuilding);
}

void GameScene::moneyUpdate(float dt)
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
	MoneyLabel->setColor(Color3B::YELLOW);
	this->addChild(MoneyLabel, 20, GameSceneNodeTagMoney);
}

void GameScene::update(float dt)
{
	scrollMap();
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
	/*
		//X 
	case EventKeyboard::KeyCode::KEY_X:
		unit_manager->genCreateMessage(1, grid_map->getGridPoint(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)));
		break;
		//空格 返回基地
	case EventKeyboard::KeyCode::KEY_SPACE:
		focusOnBase();
		break;
	*/
	default:
		break;
	}
}

