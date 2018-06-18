#include"ServerScene.h"

SocketServer* socket_server_;
Scene *ServerScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ServerScene::create();
	scene->addChild(layer);
	return scene;
}

bool ServerScene::init()
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
	//添加端口信息
	auto inputbox = ui::EditBox::create(Size(80, 60), ui::Scale9Sprite::create(INPUT_IP));
	inputbox->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - inputbox->getContentSize().height));
	inputbox->setTextHorizontalAlignment(TextHAlignment::CENTER);
	inputbox->setMaxLength(7);
	inputbox->setFontColor(Color3B::WHITE);
	inputbox->setFontName("/fonts/AGENCYR.TTF");
	inputbox->setFontSize(20);
	inputbox->setText("8008");
	inputbox->setInputMode(ui::EditBox::InputMode::NUMERIC);
	this->addChild(inputbox, 1);
	//信息label
	connection_msg_ = Label::createWithTTF("", "/fonts/arial.ttf", 18);
	connection_msg_->setAnchorPoint(Vec2(0.5, 0));
	connection_msg_->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y));
	addChild(connection_msg_);
	return true;
}

//添加背景图片
void ServerScene::addBackgroundSprite()
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
void ServerScene::addMenuSprites()
{
	//1 显示服务器信息
	//设置菜单的正常图片
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * MessageTTF = LabelTTF::create(MyUtility::gbk_2_utf8("开启服务器"), "华文行楷", 25);
	//创建controlButton
	ControlButton * MessageBtn = ControlButton::create(MessageTTF, NormalButton1);
	//添加菜单按下的效果图片
	MessageBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//设置菜单项的位置
	MessageBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//设置点击的回调方法
	MessageBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	MessageBtn->setTag(START_SERVER);
	//添加Menu到场景
	addChild(MessageBtn);

	//2 开始游戏
	//设置菜单的正常图片
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * startGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("开始游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * startGameBtn = ControlButton::create(startGameTTF, NormalButton2);
	//添加菜单按下的效果图片
	startGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//设置菜单项的位置
	startGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//设置点击的回调方法
	startGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	startGameBtn->setTag(START_GAME);
	//添加Menu到场景
	addChild(startGameBtn);

	//3 返回上一界面(RoomScene)
	//设置菜单的正常图片
	Scale9Sprite * NormalButton3 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton3 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * backTTF = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 25);
	//创建controlButton
	ControlButton * backBtn = ControlButton::create(backTTF, NormalButton3);
	//添加菜单按下的效果图片
	backBtn->setBackgroundSpriteForState(PressButton3, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	backBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.32);
	//设置点击的回调方法
	backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	backBtn->setTag(GO_BACK);
	//添加Menu到场景
	addChild(backBtn);
}

//返回输入的端口信息
void ServerScene::editBoxReturn(EditBox* editBox)
{
	log(editBox->getText());
	int port = atoi(editBox->getText());
}

void ServerScene::connectionSchdeule(float f)
{
	GameScene::playerid = 1;
	if (socket_server_->getconnection_num())
	{
		connection_msg_->setString("Total connection num: " + std::to_string(socket_server_->getconnection_num()));
	}
	else
		connection_msg_->setString("Port already used, please change another one");
}

void ServerScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	ControlButton * button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case START_SERVER:
	{
		if (!socket_server_)
		{
			socket_server_ = SocketServer::create();
			socket_client_ = SocketClient::create();
			log("create server and client on 8008");
			schedule(schedule_selector(ServerScene::connectionSchdeule), 0.1);
		}
		break;
	}
	case START_GAME:
	{
		if (socket_server_)
		{
			socket_server_->button_start();
			auto sc = GameScene::createScene(socket_client_, socket_server_);
			auto reScene = TransitionFadeTR::create(0.5f, sc);
			Director::getInstance()->replaceScene(reScene);
			log("start game");
		}
		break;
	}
	case GO_BACK:
	{
		if (socket_server_)
		{
			unscheduleAllCallbacks();
			socket_client_->close();
			delete socket_client_;
			socket_client_ = nullptr;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			socket_server_->close();
			delete socket_server_;
			socket_server_ = nullptr;
		}
		Director::getInstance()->popScene();
	}
	break;
	}
}




