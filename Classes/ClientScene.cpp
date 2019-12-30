#include"ClientScene.h"

Scene *ClientScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ClientScene::create();
	scene->addChild(layer);
	return scene;
}

bool ClientScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//初始化窗口尺寸变量
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//添加场景背景
	addBackgroundSprite();
	//添加Menu
	addMenuSprites();
	//添加ip_box
	auto ip_box = ui::EditBox::create(Size(150, 60), ui::Scale9Sprite::create(INPUT_IP));
	ip_box->setPosition(Vec2(origin.x + visibleSize.width / 2 - ip_box->getContentSize().width / 2,origin.y + visibleSize.height - ip_box->getContentSize().height));
	ip_box->setTextHorizontalAlignment(TextHAlignment::CENTER);
	ip_box->setFontName("/fonts/AGENCYR.TTF");
	ip_box->setFontSize(20);
	ip_box->setMaxLength(20);
	ip_box->setFontColor(Color3B::WHITE);
	ip_box->setText("127.0.0.1");
	ip_box->setTag(1);
	//添加port_box
	auto port_box = ui::EditBox::create(Size(80, 60), ui::Scale9Sprite::create(INPUT_PORT));
	port_box->setPosition(Vec2(origin.x + visibleSize.width / 2 + port_box->getContentSize().width,origin.y + visibleSize.height - port_box->getContentSize().height));
	port_box->setTextHorizontalAlignment(TextHAlignment::CENTER);
	port_box->setFontName("/fonts/AGENCYR.TTF");
	port_box->setFontSize(20);
	port_box->setMaxLength(20);
	port_box->setFontColor(Color3B::WHITE);
	port_box->setText("8008");
	port_box->setInputMode(ui::EditBox::InputMode::NUMERIC);
	port_box->setTag(2);
	this->addChild(ip_box, 1);
	this->addChild(port_box, 1);
	connection_msg_ = Label::createWithTTF("", "/fonts/arial.ttf", 18);
	connection_msg_->setAnchorPoint(Vec2(0.5, 0));
	connection_msg_->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y));
	addChild(connection_msg_);
	return true;
}

void ClientScene::addBackgroundSprite()
{
	//添加背景图片
	Sprite * MenuBackgroundSprite = Sprite::create(MENU_BACKGROUND);
	//场景最中央显示图片
	MenuBackgroundSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	//设置锚点在最中央
	MenuBackgroundSprite->setAnchorPoint(ccp(0.5, 0.5));
	//设置背景大小，与屏幕按比例适配
	Size WinSize = CCDirector::sharedDirector()->getWinSize();
	float winx = WinSize.width;
	float winy = WinSize.height;
	float backgroundx = MenuBackgroundSprite->getTextureRect().getMaxX();
	float backgroundy = MenuBackgroundSprite->getTextureRect().getMaxY();
	MenuBackgroundSprite->setScaleX(winx / backgroundx);
	MenuBackgroundSprite->setScaleY(winy / backgroundy);
	//添加背景至场景
	this->addChild(MenuBackgroundSprite,-5);
}

//添加Menu
void ClientScene::addMenuSprites()
{
	//设置菜单的正常图片
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * joinGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("加入游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * joinGameBtn = ControlButton::create(joinGameTTF, NormalButton1);
	//添加按下的效果图片
	joinGameBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//设置菜单项的位置
	joinGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//设置点击的回调方法
	joinGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ClientScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	joinGameBtn->setTag(JOIN_GAME);
	//添加Menu到场景
	addChild(joinGameBtn);

	//设置菜单的正常图片
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * backGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 25);
	//创建controlButton
	ControlButton * backGameBtn = ControlButton::create(backGameTTF, NormalButton2);
	//添加菜单按下的效果图片
	backGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//设置菜单项的位置
	backGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//设置点击的回调方法
	backGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ClientScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	backGameBtn->setTag(GO_BACK);
	//添加Menu到场景
	addChild(backGameBtn);
}

void ClientScene::waitStart()
{
	/***********
	//socket_client_->camp();
	unscheduleAllCallbacks();
	log("get the camp");
	log("start game");
	auto scene = BattleScene::createScene(socket_client_, nullptr);
	//	auto scene = BattleScene::createScene(socket_client_);
	Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5, scene));
	**************/
}

void ClientScene::startSchedule(float f)
{
	/**************
	if (socket_client_->error())
	{
		unscheduleAllCallbacks();
		socket_client_->close();
		delete socket_client_;
		socket_client_ = nullptr;
		connection_msg_->setString("Cannot connect to the server, please try again");
		return;
	}
	switch ((timer_++ % 32) / 4)
	{
	case 0: connection_msg_->setString("Connected, wait for server"); break;
	case 1: connection_msg_->setString("Connected, wait for server."); break;
	case 2: connection_msg_->setString("Connected, wait for server.."); break;
	case 3: connection_msg_->setString("Connected, wait for server..."); break;
	default: break;
	}
	if (socket_client_->started())
		waitStart();
	****************/
}

void ClientScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	ControlButton * button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case JOIN_GAME:
	{
		/***********
		if (!socket_client_)
		{
			auto ip_box = static_cast<ui::EditBox*>(getChildByTag(1));
			std::string ip = ip_box->getText();
			auto port_box = static_cast<ui::EditBox*>(getChildByTag(2));
			int port = atoi(port_box->getText());
			log("ip:%s, port:%d", ip.c_str(), port);
			socket_client_ = SocketClient::create(ip, port);
			schedule(schedule_selector(ClientMenu::startSchedule), 0.1);
			//	std::async(&ClientMenu::wait_start, this);
			//	wait_start();	
		}
		************/
		break;
	}
	case GO_BACK:
	{
		/**********
		if (socket_client_)
		{
			unscheduleAllSelectors();
			socket_client_->close();
			delete socket_client_;
			socket_client_ = nullptr;
		}
		************/
		Director::getInstance()->popScene();
		break;
	}
	break;
	}
}
