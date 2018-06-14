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
TMXTiledMap *GameScene::_tiledMap1;
Rect GameScene::select_rect;

//Mouse Rect相关方法
Rect GameScene::getvisionRect()
{
	auto visible_origin = Vec2(0, 0) - _tiledMap1->getPosition();
	auto visible_size = Director::getInstance()->getVisibleSize();
	return cocos2d::Rect(visible_origin, visible_size);
}

Scene * GameScene::createScene()
{
	Scene *scene = Scene::createWithPhysics();
	PhysicsWorld *phyWorld = scene->getPhysicsWorld();
	//用于物理引擎debug
	//phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	phyWorld->setGravity(Vec2(0, 0));
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
	_tiledMap1 = TMXTiledMap::create(GAMEMAP1);
	_tiledMap1->setAnchorPoint(Vec2(0, 0));
	_tiledMap1->setPosition(0, 0);
<<<<<<< HEAD
	addChild(_tiledMap1, 0);
	TMXObjectGroup *objectsGroup = _tiledMap1->objectGroupNamed("Objects");
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
		Size sss = sp->getContentSize();
		sp->setContentSize(Size(width, height));
		sp->setPhysicsBody(phy);
		_tiledMap1->addChild(sp);
	}


	//��ͼ����
=======
	addChild(_tiledMap1,0);
	TMXLayer *UnreachableGroundLayer = _tiledMap1->getLayer("UnreachableGroundLayer");
	//地图更新
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	schedule(schedule_selector(GameScene::update));
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

<<<<<<< HEAD
=======
	//建筑物不可建造时显示的标签
	ifBuild = LabelTTF::create(MyUtility::gbk_2_utf8("非法建造"), "华文行楷", 15);
	ifBuild->setColor(Color3B::RED);
	ifBuild->setAnchorPoint(Vec2(0.5, 0.5));
	ifBuild->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - ifBuild->getContentSize().height / 2));
	ifBuild->setTag(0);//标记为0和1分别对应建筑物监听器将建筑物设为不可移动和可移动
	ifBuild->setVisible(false);//当标签不可见时建筑物可被监听器设为不可移动
	addChild(ifBuild);
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5

	//创建一个基地精灵
	Buildings *base = Buildings::creatWithBuildingTypes(START_BASE);
	base->setAnchorPoint(Vec2(0, 0));
	base->setScale(1);
	base->setPosition(Vec2(16,16));
	base->createBar();
	//base->hpBar->setPosition(base->hpBar->getPosition() - Vec2(16, -32));
	_tiledMap1->addChild(base, 10, GameSceneNodeTagBuilding);

	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	log("GameScene onEnter");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

<<<<<<< HEAD
	//�������ز˵�
	auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("����"), "�����п�", 15);
	backLabel->setColor(Color3B::GREEN);
	auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;  //��ò˵�����
	float back_y = backMenu->getContentSize().height; //��ò˵�����
	backMenu->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - back_y));
=======
	//创建返回菜单
	auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 15);
	auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;  //获得菜单宽度
	float back_y = backMenu->getContentSize().height; //获得菜单长度
	backMenu->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - back_y));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	auto mn = Menu::create(backMenu, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

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
<<<<<<< HEAD
	auto buildingLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("��Ӫ"), "�����п�", 8);
	buildingLabel1->setColor(Color3B::GREEN);
	buildingLabel1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 40));
=======
	auto buildingLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("兵营"), "华文行楷", 8);
	buildingLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 40));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
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
<<<<<<< HEAD
	auto buildingLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("�糧"), "�����п�", 8);
	buildingLabel2->setColor(Color3B::GREEN);
	buildingLabel2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height -80));
=======
	auto buildingLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("电厂"), "华文行楷", 8);
	buildingLabel2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height -80));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
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
<<<<<<< HEAD
	auto buildingLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("ս������"), "�����п�", 8);
	buildingLabel3->setColor(Color3B::GREEN);
	buildingLabel3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 120));
=======
	auto buildingLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("战车工厂"), "华文行楷", 8);
	buildingLabel3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 120));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
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
<<<<<<< HEAD
	auto buildingLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("��"), "�����п�", 8);
	buildingLabel4->setColor(Color3B::GREEN);
	buildingLabel4->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 160));
=======
	auto buildingLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("矿场"), "华文行楷", 8);
	buildingLabel4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 160));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	this->addChild(buildingLabel4, 30);
	

	//创建矿工菜单
	MenuItemImage *soldierMenu1 = MenuItemImage::create(MINER, MINER, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu1->setScale(1.2);
	soldierMenu1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 200));
	soldierMenu1->setTag(START_MINER);
	soldierMenu1->setOpacity(128);
	Menu *smn1 = Menu::create(soldierMenu1, NULL);
	smn1->setPosition(Vec2::ZERO);
	this->addChild(smn1, 20);
<<<<<<< HEAD
	auto soldierLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("��"), "�����п�", 8);
	soldierLabel1->setColor(Color3B::GREEN);
	soldierLabel1->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 200));
=======
	auto soldierLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("矿工"), "华文行楷", 8);
	soldierLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 200));
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	this->addChild(soldierLabel1,30);

	//��Ȯ�˵�
	MenuItemImage *soldierMenu2 = MenuItemImage::create(POLICEMAN, POLICEMAN, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu2->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu2->setScale(1.2);
	soldierMenu2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 220));
	soldierMenu2->setTag(START_POLICEMAN);
	soldierMenu2->setOpacity(128);
	Menu *smn2 = Menu::create(soldierMenu2, NULL);
	smn2->setPosition(Vec2::ZERO);
	this->addChild(smn2, 20);
	auto soldierLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("��Ȯ"), "�����п�", 8);
	soldierLabel2->setColor(Color3B::GREEN);
	soldierLabel2->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 220));
	this->addChild(soldierLabel2, 30);

	//̹�˲˵�
	MenuItemImage *soldierMenu3 = MenuItemImage::create(TANK, TANK, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu3->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu3->setScale(1.2);
	soldierMenu3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 240));
	soldierMenu3->setTag(START_TANK);
	soldierMenu3->setOpacity(128);
	Menu *smn3 = Menu::create(soldierMenu3, NULL);
	smn3->setPosition(Vec2::ZERO);
	this->addChild(smn3, 20);
	auto soldierLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("̹��"), "�����п�", 8);
	soldierLabel3->setColor(Color3B::GREEN);
	soldierLabel3->setPosition(Vec2(visibleSize.width-20, origin.y + visibleSize.height - 240));
	this->addChild(soldierLabel3, 30);


<<<<<<< HEAD
	//������Ӵ���������
	spriteContactListener = EventListenerPhysicsContact::create();
	spriteContactListener->onContactBegin = [this](PhysicsContact &contact)
=======
	//建筑物接触检测监听器
	buildingContactListener = EventListenerPhysicsContact::create();
	buildingContactListener->onContactBegin = [this](PhysicsContact &contact)
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	{
		log("SPRITE CONTACT");
		Sprite *SpriteA = (Sprite *)(contact.getShapeA()->getBody()->getNode());
		Sprite *SpriteB = (Sprite *)(contact.getShapeB()->getBody()->getNode());
		if (!SpriteA || !SpriteB)
		{
			return false;
		}
<<<<<<< HEAD
		//�ж����������Ƿ�Ϊ�����������һ������Ҫ�����

		//�˴�Ϊ�����ֽӴ�
=======
		//判断两个精灵是否为建筑物，并看哪一个是需要建造的
		if (SpriteA->getTag() == GameSceneNodeTagBuilding && SpriteB->getTag() == GameSceneNodeTagBuilding)
		{
			auto buildingSpriteA = dynamic_cast<Buildings *>(SpriteA);
			auto buildingSpriteB = dynamic_cast<Buildings *>(SpriteB);
			//需要建造的建筑物是可移动的
			if (buildingSpriteA->getifMove() && !buildingSpriteB->getifMove())
			{
				buildingSpriteA->setifMove(CAN_MOVE);//让此建筑物认为可移动
				buildingSpriteB->setOpacity(128);//将不可移动的建筑物变透明
												 //给标签设置标记，使建筑物的监听器可以根据标签判断是否需要将建筑物设为不可移动
				this->ifBuild->setTag(1);
				this->ifBuild->setVisible(true);//显示禁止建造的标签
				return true;
			}
			if (buildingSpriteB->getifMove() && !buildingSpriteA->getifMove())
			{
				buildingSpriteB->setifMove(CAN_MOVE);
				buildingSpriteA->setOpacity(128);
				this->ifBuild->setTag(1);
				this->ifBuild->setVisible(true);
				return true;
			}
		}
		//此处为检测兵种接触
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
		if (SpriteA->getTag() == GameSceneNodeTagSoldier && SpriteB->getTag() == GameSceneNodeTagSoldier)
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
			/*if (!soldierSpriteA->getifSelect() && soldierSpriteB->getifSelect())
			{
			Size s = soldierSpriteA->getContentSize();
			Vec2 rand = soldierSpriteA->getPosition() + (Vec2(s.width, s.height) * (1 + CCRANDOM_0_1()));
			soldierSpriteB->setPosition(rand);
			return false;
			}
			return false;*/
			/*Size s = soldierSpriteA->getContentSize();
			Vec2 rand = soldierSpriteB->getPosition() + (Vec2(s.width, s.height) * (1 + CCRANDOM_0_1()));
			soldierSpriteA->setPosition(rand);
			return false;*/
		}
		return false;
	};

	spriteContactListener->onContactSeparate = [this](PhysicsContact &contact)
	{
<<<<<<< HEAD
		
=======
		log("SPRITE CONTACTSEPARATE");
		Buildings *buildingSpriteA = (Buildings *)(contact.getShapeA()->getBody()->getNode());
		Buildings *buildingSpriteB = (Buildings *)(contact.getShapeB()->getBody()->getNode());
		if (!buildingSpriteA || !buildingSpriteB)
		{
			return;
		}
		if (buildingSpriteA->getTag() == GameSceneNodeTagBuilding && buildingSpriteB->getTag() == GameSceneNodeTagBuilding)
		{
			if (buildingSpriteA->getifMove() && !buildingSpriteB->getifMove())
			{
				buildingSpriteA->setifMove(CAN_MOVE);//建筑物分离仍可移动
				buildingSpriteB->setOpacity(255);//不可移动的建筑物恢复为不透明
				this->ifBuild->setTag(0);//标签的标记为0，建筑物监听器可以将建筑物设为不可移动
				this->ifBuild->setVisible(false);//标签不可见
				return;
			}
			if (buildingSpriteB->getifMove() && !buildingSpriteA->getifMove())
			{
				buildingSpriteB->setifMove(CAN_MOVE);
				buildingSpriteA->setOpacity(255);
				this->ifBuild->setTag(0);
				this->ifBuild->setVisible(false);
				return;
			}
		}
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
		return;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(spriteContactListener, 20);

<<<<<<< HEAD
	//ʵʱˢ�½�Ǯ
	this->Money = 5000;
=======
	//实时刷新金钱
	this->Money = 4000;
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
	__String *currentMoney = __String::createWithFormat("Money:%d", this->Money);
	auto MoneyLabel = LabelTTF::create(currentMoney->getCString(), "Marker Felt", 15);
	float Money_x = MoneyLabel->getContentSize().width;
	float Money_y = MoneyLabel->getContentSize().height;
	MoneyLabel->setPosition(origin.x + visibleSize.width - Money_x * 0.75, origin.y + Money_y);
	MoneyLabel->setColor(Color3B::RED);
	this->addChild(MoneyLabel, 20, GameSceneNodeTagMoney);
	this->schedule(schedule_selector(GameScene::moneyUpdate), 1.0f, CC_REPEAT_FOREVER, 0);

}

void GameScene::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouse_event);
	Director::getInstance()->getEventDispatcher()->removeEventListener(keyboard_listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(spriteContactListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouseRectListener);
	this->unschedule(schedule_selector(GameScene::moneyUpdate));
	this->unschedule(schedule_selector(GameScene::update));
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
		case START_CASERN:
		{
			if (Money < CASERN_PRICE)//判断钱是否足够
			{
				break;
			}
			Money -= CASERN_PRICE;
			//建筑物准备定时器，每种建筑物准备时间不同
			this->scheduleOnce(schedule_selector(GameScene::casernReady), 2.0f);
			break;
		}
		case START_ELECTRICSTATION:
		{
			if (Money < ELECTRICSTATION_PRICE)//判断钱是否足够
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			Money -= ELECTRICSTATION_PRICE;
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
			Money -= TANKFACTORY_PRICE;
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
			Money -= OREYARD_PRICE;
			this->scheduleOnce(schedule_selector(GameScene::oreYardReady), 1.5f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
	}
}

void GameScene::soldiersCreate(Ref *pSender)
{
	MenuItem *mnitm = (MenuItem *)pSender;
	switch (mnitm->getTag())
	{
		case START_MINER:
		{
			if (Money < MINER_PRICE || !_tiledMap1->getChildByName("oreYard"))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			Money -= MINER_PRICE;
<<<<<<< HEAD
			//׼����ʱ��
			this->scheduleOnce(schedule_selector(GameScene::minerReady), 1.0f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
		case START_POLICEMAN:
		{
			if (Money < POLICEMAN_PRICE || !_tiledMap1->getChildByName("casern"))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			Money -= POLICEMAN_PRICE;
			//׼����ʱ��
			this->scheduleOnce(schedule_selector(GameScene::policemanReady), 1.5f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
		}
		case START_TANK:
		{
			if (Money < TANK_PRICE || !_tiledMap1->getChildByName("tankFactory"))
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/insufficientfund.wav");
				break;
			}
			Money -= TANK_PRICE;
			this->scheduleOnce(schedule_selector(GameScene::tankReady), 2.0f);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/unitready.wav");
			break;
=======
			//准备定时器
			this->scheduleOnce(schedule_selector(GameScene::minerReady), 0.5f);
>>>>>>> adab2cd04015cfcb12374731b7f276360b4fd5e5
		}
	}
}

//兵种绘制
void GameScene::minerReady(float dt)
{
	//通过Soldiers类来创建士兵
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto miner = Soldiers::createWithSoldierTypes(START_MINER);
	miner->setAnchorPoint(Vec2(0.5, 0.5));
	miner->setScale(1.2);
	float soldiers_x = miner->getContentSize().width;
	float soldiers_y = miner->getContentSize().height;
	Size s = _tiledMap1->getChildByName("oreYard")->getContentSize() * 0.3;
	Vec2 position = _tiledMap1->getChildByName("oreYard")->getPosition() + Vec2(s.width, 0);
	miner->setPosition(position);
	//miner->setPosition(Vec2(visibleSize.width - soldiers_x, visibleSize.height - soldiers_y / 6));
	miner->setName("miner");
	miner->createBar();
	_tiledMap1->addChild(miner, 10, GameSceneNodeTagSoldier);
}
void GameScene::policemanReady(float dt)
{
	//ͨ��Soldiers��������ʿ��
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto policeman = Soldiers::createWithSoldierTypes(START_POLICEMAN);
	policeman->setAnchorPoint(Vec2(0.5, 0.5));
	policeman->setScale(1.2);
	float soldiers_x = policeman->getContentSize().width;
	float soldiers_y = policeman->getContentSize().height;
	Size s = _tiledMap1->getChildByName("casern")->getContentSize() * 0.3;
	Vec2 position = _tiledMap1->getChildByName("casern")->getPosition() + Vec2(s.width, 0);
	policeman->setPosition(position);
	//policeman->setPosition(Vec2(visibleSize.width - soldiers_x, visibleSize.height - soldiers_y / 6));
	policeman->setName("policeman");
	policeman->createBar();
	_tiledMap1->addChild(policeman, 10, GameSceneNodeTagSoldier);
}
void GameScene::tankReady(float dt)
{
	//ͨ��Soldiers��������ʿ��
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto tank = Soldiers::createWithSoldierTypes(START_TANK);
	tank->setAnchorPoint(Vec2(0.5, 0.5));
	tank->setScale(1.2);
	float soldiers_x = tank->getContentSize().width;
	float soldiers_y = tank->getContentSize().height;
	Size s = _tiledMap1->getChildByName("tankFactory")->getContentSize() * 0.3;
	Vec2 position = _tiledMap1->getChildByName("tankFactory")->getPosition() + Vec2(s.width, 0);
	tank->setPosition(position);
	//tank->setPosition(Vec2(visibleSize.width - soldiers_x, visibleSize.height - soldiers_y / 6));
	tank->setName("tank");
	tank->createBar();
	_tiledMap1->addChild(tank, 10, GameSceneNodeTagSoldier);
}


//建筑物绘制
void GameScene::casernReady(float dt)
{
	//通过Buildings类来创建建筑物
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto casern = Buildings::creatWithBuildingTypes(START_CASERN);
	casern->setAnchorPoint(Vec2(0, 0));
	casern->setScale(1);
	float building_x = casern->getContentSize().width;
	float building_y = casern->getContentSize().height;
	casern->setPosition(Vec2(16, 176));
	casern->setName("casern");
	casern->createBar();
	_tiledMap1->addChild(casern, 10, GameSceneNodeTagBuilding);
}
void GameScene::electricStationReady(float dt)
{
	//通过Buildings类来创建建筑物
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto electricStation = Buildings::creatWithBuildingTypes(START_ELECTRICSTATION);
	electricStation->setAnchorPoint(Vec2(0, 0));
	electricStation->setScale(1);
	float building_x = electricStation->getContentSize().width;
	float building_y = electricStation->getContentSize().height;
	electricStation->setPosition(Vec2(112, 176));
	electricStation->setName("electricStation");
	electricStation->createBar();
	_tiledMap1->addChild(electricStation, 10, GameSceneNodeTagBuilding);
}
void GameScene::tankFactoryReady(float dt)
{
	//通过Building类来创建建筑物
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto tankFactory = Buildings::creatWithBuildingTypes(START_TANKFACTORY);
	tankFactory->setAnchorPoint(Vec2(0, 0));
	tankFactory->setScale(1);
	float building_x = tankFactory->getContentSize().width;
	float building_y = tankFactory->getContentSize().height;
	tankFactory->setPosition(Vec2(112, 16));
	tankFactory->setName("tankFactory");
	tankFactory->createBar();
	_tiledMap1->addChild(tankFactory, 10, GameSceneNodeTagBuilding);
}
void GameScene::oreYardReady(float dt)
{
	//通过Building类来创建建筑物
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto oreYard = Buildings::creatWithBuildingTypes(START_OREYARD);
	oreYard->setAnchorPoint(Vec2(0, 0));
	//oreYard->setScale(1);
	float building_x = oreYard->getContentSize().width;
	float building_y = oreYard->getContentSize().height;
	oreYard->setPosition(Vec2(16, 96));
	oreYard->setName("oreYard");
	oreYard->createBar();
	_tiledMap1->addChild(oreYard, 10, GameSceneNodeTagBuilding);
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
	MoneyLabel->setColor(Color3B::RED);
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
	/**********************************************
	if (mini_map_rect.containsPoint(touch))
	{
		auto focus_point = (touch - mini_map_rect.origin) / 2 * grid_map->getGridWidth();
		focusOn(focus_point);
		mini_map->update(0.0f);
		mouseRect->reset();
		return;
	}
	**************************************************/
	if (this->mouseRect->isScheduled(schedule_selector(MouseRect::update)))
	{
		this->mouseRect->unschedule(schedule_selector(MouseRect::update));
	}
	mouseRect->end = touch - _tiledMap1->getPosition();
	Point maptouch = mouseRect->end;
	Point last_maptouch = mouseRect->start;
	/********************************************************************
	GridPoint map_touch_grid_point = grid_map->getGridPoint(maptouch);
	log("Map Touch Grid Point: (%d, %d)", map_touch_grid_point.x, map_touch_grid_point.y);
	if (end_flag)
		return;
	if ((maptouch - last_maptouch).length() < MIN_SELECT_RECT_SIZE)
		unit_manager->selectUnits(maptouch);
	else
	{
		Rect select_rect{ MIN(last_maptouch.x, maptouch.x), MIN(last_maptouch.y, maptouch.y),
			abs(last_maptouch.x - maptouch.x), abs(last_maptouch.y - maptouch.y) };
		unit_manager->selectUnits(select_rect);
	}
	***********************************************************************/
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
		select_rect = { MIN(last_maptouch.x, maptouch.x), MIN(last_maptouch.y, maptouch.y),
			abs(last_maptouch.x - maptouch.x), abs(last_maptouch.y - maptouch.y) };
		for (auto &sprite : _tiledMap1->getChildren())
		{
			if (!select_rect.containsPoint(sprite->getPosition()))
			{
				if (sprite->getTag() == GameSceneNodeTagBuilding)
				{
					auto temp = dynamic_cast<Buildings *>(sprite);
					temp->hideHpBar();
					continue;
				}
				if (sprite->getTag() == GameSceneNodeTagSoldier)
				{
					auto temp = dynamic_cast<Soldiers *>(sprite);
					temp->hideHpBar();
					continue;
				}
				continue;
			}
			if (sprite->getTag() == GameSceneNodeTagBuilding)
			{
				auto temp = dynamic_cast<Buildings *>(sprite);
				temp->displayHpBar();
			}
			if (sprite->getTag() == GameSceneNodeTagSoldier)
			{
				auto temp = dynamic_cast<Soldiers *>(sprite);
				temp->displayHpBar();
				temp->setifSelect(SELECT_ON);
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

/*****************************************************************
void MiniMap::update(float dt)
{
	static std::vector<Color4F> color_list = { { 0, 0, 0, 0.5 },{ 0.5, 0.5, 0.5, 0.5 },{ 1, 0, 0, 1 },{ 0, 1, 0, 1 },{ 0, 0, 1, 1 },{ 1, 1, 0, 1 } };
	const auto& umap = grid_map->getUnitMap();
	const auto& fmap = grid_map->getFogMap();
	clear();
	int color_index = 0;
	for (int x = 0; x < int(fmap.size()); x++)
		for (int y = 0; y < int(fmap[x].size()); y++)
		{
			if (fmap[x][y])
				color_index = 0;
			else
				if (umap[x][y])
					color_index = unit_manager->getUnitCamp(umap[x][y]) + 1;
				else
					color_index = 1;
			drawPoint(Point(x * 2, y * 2), 2, color_list[color_index]);
		}

	const auto& visible_rect = battle_scene->getVisionRect();
	int grid_width = grid_map->getGridWidth();
	auto mini_rect_start = visible_rect.origin / grid_width * 2;
	auto mini_rect_end = mini_rect_start + visible_rect.size / grid_width * 2;
	drawRect(mini_rect_start, mini_rect_end, Color4F(1, 0, 1, 1));
}

void MiniMap::setGridMap(GridMap * _grid_map)
{
	grid_map = _grid_map;
}

void MiniMap::setUnitManager(UnitManager * _unit_manager)
{
	unit_manager = _unit_manager;
}

void MiniMap::setBattleScene(GameScene * _game_scene)
{
	game_scene = _game_scene;
}
**************************************************************************/
	
