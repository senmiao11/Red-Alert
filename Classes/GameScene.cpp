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
LabelTTF * GameScene::ifBuild;
TMXTiledMap *GameScene::_tiledMap1;
Rect GameScene::select_rect;

<<<<<<< HEAD
//Mouse RectÏà¹Ø·½·¨
=======
//Mouse Rectç›¸å…³æ–¹æ³•
>>>>>>> xiaorui
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
<<<<<<< HEAD
	//ÓÃÓÚÎïÀíÒýÇædebug
=======
	//ç”¨äºŽç‰©ç†å¼•æ“Ždebug
>>>>>>> xiaorui
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
	
<<<<<<< HEAD
	/************µØÍ¼************/
	//ÓÎÏ·µØÍ¼
	_tiledMap1 = TMXTiledMap::create(GAMEMAP1);
	_tiledMap1->setAnchorPoint(Vec2(0, 0));
	_tiledMap1->setPosition(0, 0);
	TMXLayer * layer = _tiledMap1->getLayer("ReachableGroundLayer");
	TMXObjectGroup *objectsGroup = _tiledMap1->objectGroupNamed("Objects");
	ValueVector objects = objectsGroup->getObjects();
	auto s = layer->getLayerSize();
	addChild(_tiledMap1, 0);
	for (auto obj : objects) 
	{
		ValueMap& dict = obj.asValueMap();
	
		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();

		PhysicsBody * phy = PhysicsBody::createBox(Size(width, height));
		phy->setDynamic(false);
		Sprite * sp = Sprite::create();
		sp->setPosition(Vec2(x, y));
		sp->setAnchorPoint(Vec2::ZERO);
		Size sss = sp->getContentSize();
		sp->setContentSize(Size(width, height));
		sp->setPhysicsBody(phy);
		this->addChild(sp);
	}


	//µØÍ¼¸üÐÂ
	schedule(schedule_selector(GameScene::update));
	//µØÍ¼ÒÆ¶¯µÄÊó±êÊÂ¼þ
	mouse_event = EventListenerMouse::create();
	mouse_event->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_event, 1);
	//¸÷ÖÖ¼üÅÌÊÂ¼þ
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	//Êó±ê»æÖÆÒ»¸ö¾ØÐÎ¿ò
	mouseRect = MouseRect::create();
	mouseRect->setVisible(false);
	_tiledMap1->addChild(mouseRect);
	mouseRectListener = EventListenerTouchOneByOne::create();
	mouseRectListener->onTouchBegan = CC_CALLBACK_2(GameScene::mouseRectOnTouchBegan, this);
	mouseRectListener->onTouchMoved = CC_CALLBACK_2(GameScene::mouseRectOnTouchMoved, this);
	mouseRectListener->onTouchEnded = CC_CALLBACK_2(GameScene::mouseRectOnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseRectListener, this);

	//½¨ÖþÎï²»¿É½¨ÔìÊ±ÏÔÊ¾µÄ±êÇ©
	ifBuild = LabelTTF::create(MyUtility::gbk_2_utf8("·Ç·¨½¨Ôì"), "»ªÎÄÐÐ¿¬", 15);
	ifBuild->setColor(Color3B::RED);
	ifBuild->setAnchorPoint(Vec2(0.5, 0.5));
	ifBuild->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - ifBuild->getContentSize().height / 2));
	ifBuild->setTag(0);//±ê¼ÇÎª0ºÍ1·Ö±ð¶ÔÓ¦½¨ÖþÎï¼àÌýÆ÷½«½¨ÖþÎïÉèÎª²»¿ÉÒÆ¶¯ºÍ¿ÉÒÆ¶¯
	ifBuild->setVisible(false);//µ±±êÇ©²»¿É¼ûÊ±½¨ÖþÎï¿É±»¼àÌýÆ÷ÉèÎª²»¿ÉÒÆ¶¯
=======
	/************åœ°å›¾************/
	//æ¸¸æˆåœ°å›¾
	_tiledMap1 = TMXTiledMap::create(GAMEMAP1);
	_tiledMap1->setAnchorPoint(Vec2(0, 0));
	_tiledMap1->setPosition(0, 0);
	addChild(_tiledMap1,0);
	TMXLayer *UnreachableGroundLayer = _tiledMap1->getLayer("UnreachableGroundLayer");
	//åœ°å›¾æ›´æ–°
	schedule(schedule_selector(GameScene::update));
	//åœ°å›¾ç§»åŠ¨çš„é¼ æ ‡äº‹ä»¶
	mouse_event = EventListenerMouse::create();
	mouse_event->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(mouse_event, 1);
	//å„ç§é”®ç›˜äº‹ä»¶
	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	
	//é¼ æ ‡ç»˜åˆ¶ä¸€ä¸ªçŸ©å½¢æ¡†
	mouseRect = MouseRect::create();
	mouseRect->setVisible(false);
	_tiledMap1->addChild(mouseRect);
	mouseRectListener = EventListenerTouchOneByOne::create();
	mouseRectListener->onTouchBegan = CC_CALLBACK_2(GameScene::mouseRectOnTouchBegan, this);
	mouseRectListener->onTouchMoved = CC_CALLBACK_2(GameScene::mouseRectOnTouchMoved, this);
	mouseRectListener->onTouchEnded = CC_CALLBACK_2(GameScene::mouseRectOnTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseRectListener, this);

	//å»ºç­‘ç‰©ä¸å¯å»ºé€ æ—¶æ˜¾ç¤ºçš„æ ‡ç­¾
	ifBuild = LabelTTF::create(MyUtility::gbk_2_utf8("éžæ³•å»ºé€ "), "åŽæ–‡è¡Œæ¥·", 15);
	ifBuild->setColor(Color3B::RED);
	ifBuild->setAnchorPoint(Vec2(0.5, 0.5));
	ifBuild->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - ifBuild->getContentSize().height / 2));
	ifBuild->setTag(0);//æ ‡è®°ä¸º0å’Œ1åˆ†åˆ«å¯¹åº”å»ºç­‘ç‰©ç›‘å¬å™¨å°†å»ºç­‘ç‰©è®¾ä¸ºä¸å¯ç§»åŠ¨å’Œå¯ç§»åŠ¨
	ifBuild->setVisible(false);//å½“æ ‡ç­¾ä¸å¯è§æ—¶å»ºç­‘ç‰©å¯è¢«ç›‘å¬å™¨è®¾ä¸ºä¸å¯ç§»åŠ¨
>>>>>>> xiaorui
	addChild(ifBuild);

	//åˆ›å»ºä¸€ä¸ªåŸºåœ°ç²¾çµ
	Buildings *base = Buildings::creatWithBuildingTypes(START_BASE);
	base->setAnchorPoint(Vec2(0, 0));
	base->setScale(0.3);
<<<<<<< HEAD
	base->setPosition(Vec2(origin.x + visibleSize.width * 0, origin.y + visibleSize.height *0));
=======
	base->setPosition(Vec2(origin.x + visibleSize.width * -0.03, origin.y + visibleSize.height *-0.06));
>>>>>>> xiaorui
	base->createBar();
	base->hpBar->setPosition(base->hpBar->getPosition() - Vec2(80, 0));
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
	//´´½¨·µ»Ø²Ëµ¥
	auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("·µ»Ø"), "»ªÎÄÐÐ¿¬", 15);
	backLabel->setColor(Color3B::GREEN);
=======
	//åˆ›å»ºè¿”å›žèœå•
	auto backLabel = LabelTTF::create(MyUtility::gbk_2_utf8("è¿”å›ž"), "åŽæ–‡è¡Œæ¥·", 15);
>>>>>>> xiaorui
	auto backMenu = MenuItemLabel::create(backLabel, CC_CALLBACK_1(GameScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;  //èŽ·å¾—èœå•å®½åº¦
	float back_y = backMenu->getContentSize().height; //èŽ·å¾—èœå•é•¿åº¦
	backMenu->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - back_y));
	auto mn = Menu::create(backMenu, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

<<<<<<< HEAD
	//´´½¨±øÓª²Ëµ¥
=======
	//åˆ›å»ºå…µè¥èœå•
>>>>>>> xiaorui
	MenuItemImage *buildingMenu1 = MenuItemImage::create(CASERN, CASERN, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu1->setScale(0.3);
	float menu1_x = buildingMenu1->getContentSize().width;
	float menu1_y = buildingMenu1->getContentSize().height;
	buildingMenu1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 40));
	buildingMenu1->setTag(START_CASERN);
	buildingMenu1->setOpacity(128);
	Menu *bmn1 = Menu::create(buildingMenu1, NULL);
	bmn1->setPosition(Vec2::ZERO);
	this->addChild(bmn1, 20);
<<<<<<< HEAD
	auto buildingLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("±øÓª"), "»ªÎÄÐÐ¿¬", 8);
	buildingLabel1->setColor(Color3B::GREEN);
	buildingLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 40));
	this->addChild(buildingLabel1,30);

	//´´½¨µç³§²Ëµ¥
=======
	auto buildingLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("å…µè¥"), "åŽæ–‡è¡Œæ¥·", 8);
	buildingLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 40));
	this->addChild(buildingLabel1,30);

	//åˆ›å»ºç”µåŽ‚èœå•
>>>>>>> xiaorui
	MenuItemImage *buildingMenu2 = MenuItemImage::create(ELECTRICSTATION, ELECTRICSTATION, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu2->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu2->setScale(0.3);
	float menu2_x = buildingMenu2->getContentSize().width;
	float menu2_y = buildingMenu2->getContentSize().height;
	buildingMenu2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 80));
	buildingMenu2->setTag(START_ELECTRICSTATION);
	buildingMenu2->setOpacity(128);
	Menu *bmn2 = Menu::create(buildingMenu2, NULL);
	bmn2->setPosition(Vec2::ZERO);
	this->addChild(bmn2, 20);
<<<<<<< HEAD
	auto buildingLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("µç³§"), "»ªÎÄÐÐ¿¬", 8);
	buildingLabel2->setColor(Color3B::GREEN);
	buildingLabel2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height -80));
	this->addChild(buildingLabel2, 30);

	//´´½¨Õ½³µ¹¤³§²Ëµ¥
=======
	auto buildingLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("ç”µåŽ‚"), "åŽæ–‡è¡Œæ¥·", 8);
	buildingLabel2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height -80));
	this->addChild(buildingLabel2, 30);

	//åˆ›å»ºæˆ˜è½¦å·¥åŽ‚èœå•
>>>>>>> xiaorui
	MenuItemImage *buildingMenu3 = MenuItemImage::create(TANKFACTORY, TANKFACTORY, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu3->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu3->setScale(0.3);
	float menu3_x = buildingMenu3->getContentSize().width;
	float menu3_y = buildingMenu3->getContentSize().height;
	buildingMenu3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 120));
	buildingMenu3->setTag(START_TANKFACTORY);
	buildingMenu3->setOpacity(128);
	Menu *bmn3 = Menu::create(buildingMenu3, NULL);
	bmn3->setPosition(Vec2::ZERO);
	this->addChild(bmn3, 20);
<<<<<<< HEAD
	auto buildingLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("Õ½³µ¹¤³§"), "»ªÎÄÐÐ¿¬", 8);
	buildingLabel3->setColor(Color3B::GREEN);
	buildingLabel3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 120));
	this->addChild(buildingLabel3, 30);

	//´´½¨¿ó³¡²Ëµ¥
	MenuItemImage *buildingMenu4 = MenuItemImage::create(OREYARD, OREYARD, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu4->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu4->setScale(0.3);
	float menu4_x = buildingMenu4->getContentSize().width;
	float menu4_y = buildingMenu4->getContentSize().height;
	buildingMenu4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 160));
	buildingMenu4->setTag(START_OREYARD);
	buildingMenu4->setOpacity(128);
	Menu *bmn4 = Menu::create(buildingMenu4, NULL);
	bmn4->setPosition(Vec2::ZERO);
	this->addChild(bmn4, 20);
	auto buildingLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("¿ó³¡"), "»ªÎÄÐÐ¿¬", 8);
	buildingLabel4->setColor(Color3B::GREEN);
	buildingLabel4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 160));
	this->addChild(buildingLabel4, 30);
	

	//´´½¨¿ó¹¤²Ëµ¥
	MenuItemImage *soldierMenu1 = MenuItemImage::create(MINER, MINER, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu1->setScale(1.2);
	soldierMenu1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 200));
	soldierMenu1->setTag(START_MINER);
	soldierMenu1->setOpacity(128);
	Menu *smn1 = Menu::create(soldierMenu1, NULL);
	smn1->setPosition(Vec2::ZERO);
	this->addChild(smn1, 20);
	auto soldierLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("¿ó¹¤"), "»ªÎÄÐÐ¿¬", 8);
	soldierLabel1->setColor(Color3B::GREEN);
	soldierLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 200));
	this->addChild(soldierLabel1,30);

	//¾¯È®²Ëµ¥
	MenuItemImage *soldierMenu2 = MenuItemImage::create(POLICEMAN, POLICEMAN, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu2->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu2->setScale(1.2);
	soldierMenu2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 220));
	soldierMenu2->setTag(START_POLICEMAN);
	soldierMenu2->setOpacity(128);
	Menu *smn2 = Menu::create(soldierMenu2, NULL);
	smn2->setPosition(Vec2::ZERO);
	this->addChild(smn2, 20);
	auto soldierLabel2 = LabelTTF::create(MyUtility::gbk_2_utf8("¾¯È®"), "»ªÎÄÐÐ¿¬", 8);
	soldierLabel2->setColor(Color3B::GREEN);
	soldierLabel2->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 220));
	this->addChild(soldierLabel2, 30);

	//Ì¹¿Ë²Ëµ¥
	MenuItemImage *soldierMenu3 = MenuItemImage::create(TANK, TANK, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu3->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu3->setScale(1.2);
	soldierMenu3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 240));
	soldierMenu3->setTag(START_TANK);
	soldierMenu3->setOpacity(128);
	Menu *smn3 = Menu::create(soldierMenu3, NULL);
	smn3->setPosition(Vec2::ZERO);
	this->addChild(smn3, 20);
	auto soldierLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("Ì¹¿Ë"), "»ªÎÄÐÐ¿¬", 8);
	soldierLabel3->setColor(Color3B::GREEN);
	soldierLabel3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 240));
	this->addChild(soldierLabel3, 30);


	//½¨ÖþÎï½Ó´¥¼ì²â¼àÌýÆ÷
	buildingContactListener = EventListenerPhysicsContact::create();
	buildingContactListener->onContactBegin = [this](PhysicsContact &contact)
	{
		log("SPRITE CONTACT");
		Sprite *SpriteA = (Sprite *)(contact.getShapeA()->getBody()->getNode());
		Sprite *SpriteB = (Sprite *)(contact.getShapeB()->getBody()->getNode());
		if (!SpriteA || !SpriteB)
		{
			return false;
		}
		//ÅÐ¶ÏÁ½¸ö¾«ÁéÊÇ·ñÎª½¨ÖþÎï£¬²¢¿´ÄÄÒ»¸öÊÇÐèÒª½¨ÔìµÄ
		if (SpriteA->getTag() == GameSceneNodeTagBuilding && SpriteB->getTag() == GameSceneNodeTagBuilding)
		{
			auto buildingSpriteA = dynamic_cast<Buildings *>(SpriteA);
			auto buildingSpriteB = dynamic_cast<Buildings *>(SpriteB);
			//ÐèÒª½¨ÔìµÄ½¨ÖþÎïÊÇ¿ÉÒÆ¶¯µÄ
			if (buildingSpriteA->getifMove() && !buildingSpriteB->getifMove())
			{
				buildingSpriteA->setifMove(CAN_MOVE);//ÈÃ´Ë½¨ÖþÎïÈÏÎª¿ÉÒÆ¶¯
				buildingSpriteB->setOpacity(128);//½«²»¿ÉÒÆ¶¯µÄ½¨ÖþÎï±äÍ¸Ã÷
				//¸ø±êÇ©ÉèÖÃ±ê¼Ç£¬Ê¹½¨ÖþÎïµÄ¼àÌýÆ÷¿ÉÒÔ¸ù¾Ý±êÇ©ÅÐ¶ÏÊÇ·ñÐèÒª½«½¨ÖþÎïÉèÎª²»¿ÉÒÆ¶¯
				this->ifBuild->setTag(1);
				this->ifBuild->setVisible(true);//ÏÔÊ¾½ûÖ¹½¨ÔìµÄ±êÇ©
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
		//´Ë´¦Îª¼ì²â±øÖÖ½Ó´¥
		if (SpriteA->getTag() == GameSceneNodeTagSoldier && SpriteB->getTag() == GameSceneNodeTagSoldier)
		{
			auto soldierSpriteA = dynamic_cast<Soldiers *>(SpriteA);
			auto soldierSpriteB = dynamic_cast<Soldiers *>(SpriteB);
			if (!soldierSpriteA->getifSelect() && !soldierSpriteB->getifSelect())
			{
				//Í¨¹ýËæ»úÊýÖØÐÂÉèÖÃÎ»ÖÃ
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
=======
	auto buildingLabel3 = LabelTTF::create(MyUtility::gbk_2_utf8("æˆ˜è½¦å·¥åŽ‚"), "åŽæ–‡è¡Œæ¥·", 8);
	buildingLabel3->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 120));
	this->addChild(buildingLabel3, 30);

	//åˆ›å»ºçŸ¿åœºèœå•
	MenuItemImage *buildingMenu4 = MenuItemImage::create(OREYARD, OREYARD, CC_CALLBACK_1(GameScene::buildingsCreate, this));
	buildingMenu4->setAnchorPoint(Vec2(0.5, 0.5));
	buildingMenu4->setScale(0.3);
	float menu4_x = buildingMenu4->getContentSize().width;
	float menu4_y = buildingMenu4->getContentSize().height;
	buildingMenu4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 160));
	buildingMenu4->setTag(START_OREYARD);
	buildingMenu4->setOpacity(128);
	Menu *bmn4 = Menu::create(buildingMenu4, NULL);
	bmn4->setPosition(Vec2::ZERO);
	this->addChild(bmn4, 20);
	auto buildingLabel4 = LabelTTF::create(MyUtility::gbk_2_utf8("çŸ¿åœº"), "åŽæ–‡è¡Œæ¥·", 8);
	buildingLabel4->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 160));
	this->addChild(buildingLabel4, 30);
	

	//åˆ›å»ºçŸ¿å·¥èœå•
	MenuItemImage *soldierMenu1 = MenuItemImage::create(MINER, MINER, CC_CALLBACK_1(GameScene::soldiersCreate, this));
	soldierMenu1->setAnchorPoint(Vec2(0.5, 0.5));
	soldierMenu1->setScale(1.2);
	//float smenu1_x = soldierMenu1->getContentSize().width;
	//float smenu1_y = soldierMenu1->getContentSize().height;
	soldierMenu1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 200));
	soldierMenu1->setTag(START_MINER);
	soldierMenu1->setOpacity(128);
	Menu *smn1 = Menu::create(soldierMenu1, NULL);
	smn1->setPosition(Vec2::ZERO);
	this->addChild(smn1, 20);
	auto soldierLabel1 = LabelTTF::create(MyUtility::gbk_2_utf8("çŸ¿å·¥"), "åŽæ–‡è¡Œæ¥·", 8);
	soldierLabel1->setPosition(Vec2(visibleSize.width, origin.y + visibleSize.height - 200));
	this->addChild(soldierLabel1,30);
>>>>>>> xiaorui

	buildingContactListener->onContactSeparate = [this](PhysicsContact &contact)
	{
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
				buildingSpriteA->setifMove(CAN_MOVE);//½¨ÖþÎï·ÖÀëÈÔ¿ÉÒÆ¶¯
				buildingSpriteB->setOpacity(255);//²»¿ÉÒÆ¶¯µÄ½¨ÖþÎï»Ö¸´Îª²»Í¸Ã÷
				this->ifBuild->setTag(0);//±êÇ©µÄ±ê¼ÇÎª0£¬½¨ÖþÎï¼àÌýÆ÷¿ÉÒÔ½«½¨ÖþÎïÉèÎª²»¿ÉÒÆ¶¯
				this->ifBuild->setVisible(false);//±êÇ©²»¿É¼û
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
		return;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(buildingContactListener, 20);

<<<<<<< HEAD
	//ÊµÊ±Ë¢ÐÂ½ðÇ®
	this->Money = 5000;
=======
	//å»ºç­‘ç‰©æŽ¥è§¦æ£€æµ‹ç›‘å¬å™¨
	buildingContactListener = EventListenerPhysicsContact::create();
	buildingContactListener->onContactBegin = [this](PhysicsContact &contact)
	{
		log("SPRITE CONTACT");
		Sprite *SpriteA = (Sprite *)(contact.getShapeA()->getBody()->getNode());
		Sprite *SpriteB = (Sprite *)(contact.getShapeB()->getBody()->getNode());
		if (!SpriteA || !SpriteB)
		{
			return false;
		}
		//åˆ¤æ–­ä¸¤ä¸ªç²¾çµæ˜¯å¦ä¸ºå»ºç­‘ç‰©ï¼Œå¹¶çœ‹å“ªä¸€ä¸ªæ˜¯éœ€è¦å»ºé€ çš„
		if (SpriteA->getTag() == GameSceneNodeTagBuilding && SpriteB->getTag() == GameSceneNodeTagBuilding)
		{
			auto buildingSpriteA = dynamic_cast<Buildings *>(SpriteA);
			auto buildingSpriteB = dynamic_cast<Buildings *>(SpriteB);
			//éœ€è¦å»ºé€ çš„å»ºç­‘ç‰©æ˜¯å¯ç§»åŠ¨çš„
			if (buildingSpriteA->getifMove() && !buildingSpriteB->getifMove())
			{
				buildingSpriteA->setifMove(CAN_MOVE);//è®©æ­¤å»ºç­‘ç‰©è®¤ä¸ºå¯ç§»åŠ¨
				buildingSpriteB->setOpacity(128);//å°†ä¸å¯ç§»åŠ¨çš„å»ºç­‘ç‰©å˜é€æ˜Ž
												 //ç»™æ ‡ç­¾è®¾ç½®æ ‡è®°ï¼Œä½¿å»ºç­‘ç‰©çš„ç›‘å¬å™¨å¯ä»¥æ ¹æ®æ ‡ç­¾åˆ¤æ–­æ˜¯å¦éœ€è¦å°†å»ºç­‘ç‰©è®¾ä¸ºä¸å¯ç§»åŠ¨
				this->ifBuild->setTag(1);
				this->ifBuild->setVisible(true);//æ˜¾ç¤ºç¦æ­¢å»ºé€ çš„æ ‡ç­¾
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
		//æ­¤å¤„ä¸ºæ£€æµ‹å…µç§æŽ¥è§¦
		if (SpriteA->getTag() == GameSceneNodeTagSoldier && SpriteB->getTag() == GameSceneNodeTagSoldier)
		{
			auto soldierSpriteA = dynamic_cast<Soldiers *>(SpriteA);
			auto soldierSpriteB = dynamic_cast<Soldiers *>(SpriteB);
			if (!soldierSpriteA->getifSelect() && !soldierSpriteB->getifSelect())
			{
				//é€šè¿‡éšæœºæ•°é‡æ–°è®¾ç½®ä½ç½®
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

	buildingContactListener->onContactSeparate = [this](PhysicsContact &contact)
	{
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
				buildingSpriteA->setifMove(CAN_MOVE);//å»ºç­‘ç‰©åˆ†ç¦»ä»å¯ç§»åŠ¨
				buildingSpriteB->setOpacity(255);//ä¸å¯ç§»åŠ¨çš„å»ºç­‘ç‰©æ¢å¤ä¸ºä¸é€æ˜Ž
				this->ifBuild->setTag(0);//æ ‡ç­¾çš„æ ‡è®°ä¸º0ï¼Œå»ºç­‘ç‰©ç›‘å¬å™¨å¯ä»¥å°†å»ºç­‘ç‰©è®¾ä¸ºä¸å¯ç§»åŠ¨
				this->ifBuild->setVisible(false);//æ ‡ç­¾ä¸å¯è§
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
		return;
	};
	_eventDispatcher->addEventListenerWithFixedPriority(buildingContactListener, 20);

	//å®žæ—¶åˆ·æ–°é‡‘é’±
	this->Money = 4000;
>>>>>>> xiaorui
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
	Director::getInstance()->getEventDispatcher()->removeEventListener(Buildings::touchBuildingListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouse_event);
	Director::getInstance()->getEventDispatcher()->removeEventListener(keyboard_listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(buildingContactListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(mouseRectListener);
	this->unschedule(schedule_selector(GameScene::moneyUpdate));
	this->unschedule(schedule_selector(GameScene::update));
}

//è¿”å›žMenuScene
void GameScene::backToMenuScene(Ref *pSender)
{
	Scene *sc = Scene::create();
	auto layer = MenuScene::create();
	sc->addChild(layer);

	auto reScene = TransitionSplitRows::create(1.0f, sc);
	Director::getInstance()->replaceScene(reScene);
}

//é€‰æ‹©å»ºç­‘ç‰©å»ºé€ 
void GameScene::buildingsCreate(Ref *pSender)
{
	MenuItem *mnitem = (MenuItem *)pSender;
	switch (mnitem->getTag())
	{
		case START_CASERN:
		{
<<<<<<< HEAD
			if (Money < CASERN_PRICE)//ÅÐ¶ÏÇ®ÊÇ·ñ×ã¹»
=======
			if (Money < CASERN_PRICE)//åˆ¤æ–­é’±æ˜¯å¦è¶³å¤Ÿ
>>>>>>> xiaorui
			{
				break;
			}
			Money -= CASERN_PRICE;
			//å»ºç­‘ç‰©å‡†å¤‡å®šæ—¶å™¨ï¼Œæ¯ç§å»ºç­‘ç‰©å‡†å¤‡æ—¶é—´ä¸åŒ
			this->scheduleOnce(schedule_selector(GameScene::casernReady), 2.0f);
			break;
		}
		case START_ELECTRICSTATION:
		{
<<<<<<< HEAD
			if (Money < ELECTRICSTATION_PRICE)//ÅÐ¶ÏÇ®ÊÇ·ñ×ã¹»
=======
			if (Money < ELECTRICSTATION_PRICE)//åˆ¤æ–­é’±æ˜¯å¦è¶³å¤Ÿ
>>>>>>> xiaorui
			{
				break;
			}
			Money -= ELECTRICSTATION_PRICE;
<<<<<<< HEAD
			//½¨ÖþÎï×¼±¸¶¨Ê±Æ÷£¬Ã¿ÖÖ½¨ÖþÎï×¼±¸Ê±¼ä²»Í¬
=======
			//å»ºç­‘ç‰©å‡†å¤‡å®šæ—¶å™¨ï¼Œæ¯ç§å»ºç­‘ç‰©å‡†å¤‡æ—¶é—´ä¸åŒ
>>>>>>> xiaorui
			this->scheduleOnce(schedule_selector(GameScene::electricStationReady), 1.8f);
			break;
		}
		case START_TANKFACTORY:
		{
<<<<<<< HEAD
			if (Money < TANKFACTORY_PRICE)      //ÅÐ¶ÏÇ®ÊÇ·ñ×ã¹»
=======
			if (Money < TANKFACTORY_PRICE)      //åˆ¤æ–­é’±æ˜¯å¦è¶³å¤Ÿ
>>>>>>> xiaorui
			{
				break;
			}
			Money -= TANKFACTORY_PRICE;
<<<<<<< HEAD
			this->scheduleOnce(schedule_selector(GameScene::tankFactoryReady), 2.5f);
=======
			this->scheduleOnce(schedule_selector(GameScene::tankFactoryReady), 1.5f);
>>>>>>> xiaorui
			break;
		}
		case START_OREYARD:
		{
<<<<<<< HEAD
			if (Money < OREYARD_PRICE)         //ÅÐ¶ÏÇ®ÊÇ·ñ×ã¹»
=======
			if (Money < OREYARD_PRICE)         //åˆ¤æ–­é’±æ˜¯å¦è¶³å¤Ÿ
>>>>>>> xiaorui
			{
				break;
			}
			Money -= OREYARD_PRICE;
<<<<<<< HEAD
			this->scheduleOnce(schedule_selector(GameScene::oreYardReady), 1.5f);
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
			if (Money < MINER_PRICE || !_tiledMap1->getChildByName("oreYard")
				|| dynamic_cast<Buildings *>(_tiledMap1->getChildByName("oreYard"))->getifMove())
			{
				break;
			}
			Money -= MINER_PRICE;
			//×¼±¸¶¨Ê±Æ÷
			this->scheduleOnce(schedule_selector(GameScene::minerReady), 1.0f);
			break;
		}
		case START_POLICEMAN:
		{
			if (Money < POLICEMAN_PRICE || !_tiledMap1->getChildByName("casern")
				|| dynamic_cast<Buildings *>(_tiledMap1->getChildByName("casern"))->getifMove())
			{
				break;
			}
			Money -= POLICEMAN_PRICE;
			//×¼±¸¶¨Ê±Æ÷
			this->scheduleOnce(schedule_selector(GameScene::policemanReady), 1.5f);
			break;
		}
		case START_TANK:
		{
			if (Money < TANK_PRICE || !_tiledMap1->getChildByName("tankFactory")
				|| dynamic_cast<Buildings *>(_tiledMap1->getChildByName("tankFactory"))->getifMove())
			{
				break;
			}
			Money -= TANK_PRICE;
			this->scheduleOnce(schedule_selector(GameScene::tankReady), 2.0f);
=======
			this->scheduleOnce(schedule_selector(GameScene::oreYardReady), 1.0f);
>>>>>>> xiaorui
			break;
		}
	}
}

<<<<<<< HEAD
//±øÖÖ»æÖÆ
void GameScene::minerReady(float dt)
{
	//Í¨¹ýSoldiersÀàÀ´´´½¨Ê¿±ø
=======
void GameScene::soldiersCreate(Ref *pSender)
{
	MenuItem *mnitm = (MenuItem *)pSender;
	switch (mnitm->getTag())
	{
		case START_MINER:
		{
			if (Money < MINER_PRICE)
			{
				break;
			}
			Money -= MINER_PRICE;
			//å‡†å¤‡å®šæ—¶å™¨
			this->scheduleOnce(schedule_selector(GameScene::minerReady), 0.5f);
		}
	}
}

//å…µç§ç»˜åˆ¶
void GameScene::minerReady(float dt)
{
	//é€šè¿‡Soldiersç±»æ¥åˆ›å»ºå£«å…µ
>>>>>>> xiaorui
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto miner = Soldiers::createWithSoldierTypes(START_MINER);
	miner->setAnchorPoint(Vec2(0.5, 0.5));
	miner->setScale(1.0);
	float soldiers_x = miner->getContentSize().width;
	float soldiers_y = miner->getContentSize().height;
<<<<<<< HEAD
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
	//Í¨¹ýSoldiersÀàÀ´´´½¨Ê¿±ø
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto policeman = Soldiers::createWithSoldierTypes(START_POLICEMAN);
	policeman->setAnchorPoint(Vec2(0.5, 0.5));
	policeman->setScale(1.0);
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
	//Í¨¹ýSoldiersÀàÀ´´´½¨Ê¿±ø
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto tank = Soldiers::createWithSoldierTypes(START_TANK);
	tank->setAnchorPoint(Vec2(0.5, 0.5));
	tank->setScale(1.0);
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


//½¨ÖþÎï»æÖÆ
=======
	miner->setPosition(Vec2(visibleSize.width - soldiers_x, visibleSize.height - soldiers_y / 6));
	miner->createBar();
	_tiledMap1->addChild(miner, 10, GameSceneNodeTagSoldier);
}

//å»ºç­‘ç‰©ç»˜åˆ¶
>>>>>>> xiaorui
void GameScene::casernReady(float dt)
{
	//é€šè¿‡Buildingsç±»æ¥åˆ›å»ºå»ºç­‘ç‰©
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto casern = Buildings::creatWithBuildingTypes(START_CASERN);
	casern->setAnchorPoint(Vec2(0.5, 0.5));
	casern->setScale(0.3);
	float building_x = casern->getContentSize().width;
	float building_y = casern->getContentSize().height;
	casern->setPosition(Vec2(visibleSize.width - building_x, visibleSize.height - building_y / 6));
<<<<<<< HEAD
	casern->setName("casern");
=======
>>>>>>> xiaorui
	casern->createBar();
	_tiledMap1->addChild(casern, 10, GameSceneNodeTagBuilding);
}
void GameScene::electricStationReady(float dt)
{
<<<<<<< HEAD
	//Í¨¹ýBuildingsÀàÀ´´´½¨½¨ÖþÎï
=======
	//é€šè¿‡Buildingsç±»æ¥åˆ›å»ºå»ºç­‘ç‰©
>>>>>>> xiaorui
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto electricStation = Buildings::creatWithBuildingTypes(START_ELECTRICSTATION);
	electricStation->setAnchorPoint(Vec2(0.5, 0.5));
	electricStation->setScale(0.3);
	float building_x = electricStation->getContentSize().width;
	float building_y = electricStation->getContentSize().height;
	electricStation->setPosition(Vec2(visibleSize.width - building_x, visibleSize.height - building_y / 6));
<<<<<<< HEAD
	electricStation->setName("electricStation");
=======
>>>>>>> xiaorui
	electricStation->createBar();
	_tiledMap1->addChild(electricStation, 10, GameSceneNodeTagBuilding);
}
void GameScene::tankFactoryReady(float dt)
{
<<<<<<< HEAD
	//Í¨¹ýBuildingÀàÀ´´´½¨½¨ÖþÎï
=======
	//é€šè¿‡Buildingç±»æ¥åˆ›å»ºå»ºç­‘ç‰©
>>>>>>> xiaorui
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto tankFactory = Buildings::creatWithBuildingTypes(START_TANKFACTORY);
	tankFactory->setAnchorPoint(Vec2(0.5, 0.5));
	tankFactory->setScale(0.3);
	float building_x = tankFactory->getContentSize().width;
	float building_y = tankFactory->getContentSize().height;
	tankFactory->setPosition(Vec2(visibleSize.width - building_x, visibleSize.height - building_y / 6));
<<<<<<< HEAD
	tankFactory->setName("tankFactory");
=======
>>>>>>> xiaorui
	tankFactory->createBar();
	_tiledMap1->addChild(tankFactory, 10, GameSceneNodeTagBuilding);
}
void GameScene::oreYardReady(float dt)
{
<<<<<<< HEAD
	//Í¨¹ýBuildingÀàÀ´´´½¨½¨ÖþÎï
=======
	//é€šè¿‡Buildingç±»æ¥åˆ›å»ºå»ºç­‘ç‰©
>>>>>>> xiaorui
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto oreYard = Buildings::creatWithBuildingTypes(START_OREYARD);
	oreYard->setAnchorPoint(Vec2(0.5, 0.5));
	oreYard->setScale(0.3);
	float building_x = oreYard->getContentSize().width;
	float building_y = oreYard->getContentSize().height;
	oreYard->setPosition(Vec2(visibleSize.width - building_x, visibleSize.height - building_y / 6));
<<<<<<< HEAD
	oreYard->setName("oreYard");
=======
>>>>>>> xiaorui
	oreYard->createBar();
	_tiledMap1->addChild(oreYard, 10, GameSceneNodeTagBuilding);
}

void GameScene::moneyUpdate(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//å°†ä¸Šä¸€ä¸ªæ ‡ç­¾ç§»å‡º
	if (this->getChildByTag(GameSceneNodeTagMoney))
	{
		this->removeChildByTag(GameSceneNodeTagMoney);
	}
	//åˆ›å»ºæ–°æ ‡ç­¾
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
<<<<<<< HEAD
			//È±ÉÙÑªÌõÏÔÊ¾
=======
			//ç¼ºå°‘è¡€æ¡æ˜¾ç¤º
>>>>>>> xiaorui
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
<<<<<<< HEAD
		//W ÉÏÒÆ
=======
		//W ä¸Šç§»
>>>>>>> xiaorui
	case EventKeyboard::KeyCode::KEY_W:
		mapCenter += Vec2(0, -100);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(0, 100) + Director::getInstance()->getVisibleSize()))
			_tiledMap1->setPosition(mapCenter);
		break;
<<<<<<< HEAD
		//A ×óÒÆ
=======
		//A å·¦ç§»
>>>>>>> xiaorui
	case EventKeyboard::KeyCode::KEY_A:
		mapCenter += Vec2(100, 0);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(-100, 0)))
			_tiledMap1->setPosition(mapCenter);
		break;
<<<<<<< HEAD
		//S ÏÂÒÆ
=======
		//S ä¸‹ç§»
>>>>>>> xiaorui
	case EventKeyboard::KeyCode::KEY_S:
		mapCenter += Vec2(0, 100);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(0, -100)))
			_tiledMap1->setPosition(mapCenter);
		break;
<<<<<<< HEAD
		//D ÓÒÒÆ
=======
		//D å³ç§»
>>>>>>> xiaorui
	case EventKeyboard::KeyCode::KEY_D:
		mapCenter += Vec2(-100, 0);
		if (_tiledMap1->getBoundingBox().containsPoint(Vec2(100, 0) + Director::getInstance()->getVisibleSize()))
			_tiledMap1->setPosition(mapCenter);
		break;
<<<<<<< HEAD
		//¹Ø±Õ»ò¿ªÆôÊó±êÒÆ¶¯ÆÁÄ»
=======
		//å…³é—­æˆ–å¼€å¯é¼ æ ‡ç§»åŠ¨å±å¹•
>>>>>>> xiaorui
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
<<<<<<< HEAD
		//°´ÏÂcontrolÊó±ê¿ÉÒÔ»òÕß²»¿ÉÒÔ»­³ö¾ØÐÎ¿ò
=======
		//æŒ‰ä¸‹controlé¼ æ ‡å¯ä»¥æˆ–è€…ä¸å¯ä»¥ç”»å‡ºçŸ©å½¢æ¡†
>>>>>>> xiaorui
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
<<<<<<< HEAD
		//¿Õ¸ñ ·µ»Ø»ùµØ
=======
		//ç©ºæ ¼ è¿”å›žåŸºåœ°
>>>>>>> xiaorui
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
	
