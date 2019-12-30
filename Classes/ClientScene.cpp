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
	//��ʼ�����ڳߴ����
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//���ӳ�������
	addBackgroundSprite();
	//����Menu
	addMenuSprites();
	//����ip_box
	auto ip_box = ui::EditBox::create(Size(150, 60), ui::Scale9Sprite::create(INPUT_IP));
	ip_box->setPosition(Vec2(origin.x + visibleSize.width / 2 - ip_box->getContentSize().width / 2,origin.y + visibleSize.height - ip_box->getContentSize().height));
	ip_box->setTextHorizontalAlignment(TextHAlignment::CENTER);
	ip_box->setFontName("/fonts/AGENCYR.TTF");
	ip_box->setFontSize(20);
	ip_box->setMaxLength(20);
	ip_box->setFontColor(Color3B::WHITE);
	ip_box->setText("127.0.0.1");
	ip_box->setTag(1);
	//����port_box
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
	//���ӱ���ͼƬ
	Sprite * MenuBackgroundSprite = Sprite::create(MENU_BACKGROUND);
	//������������ʾͼƬ
	MenuBackgroundSprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	//����ê����������
	MenuBackgroundSprite->setAnchorPoint(ccp(0.5, 0.5));
	//���ñ�����С������Ļ����������
	Size WinSize = CCDirector::sharedDirector()->getWinSize();
	float winx = WinSize.width;
	float winy = WinSize.height;
	float backgroundx = MenuBackgroundSprite->getTextureRect().getMaxX();
	float backgroundy = MenuBackgroundSprite->getTextureRect().getMaxY();
	MenuBackgroundSprite->setScaleX(winx / backgroundx);
	MenuBackgroundSprite->setScaleY(winy / backgroundy);
	//���ӱ���������
	this->addChild(MenuBackgroundSprite,-5);
}

//����Menu
void ClientScene::addMenuSprites()
{
	//���ò˵�������ͼƬ
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//���ò˵�����ͼƬ
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//�����˵�����Ҫ��Label����
	LabelTTF * joinGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("������Ϸ"), "�����п�", 25);
	//����controlButton
	ControlButton * joinGameBtn = ControlButton::create(joinGameTTF, NormalButton1);
	//���Ӱ��µ�Ч��ͼƬ
	joinGameBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//���ò˵����λ��
	joinGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//���õ���Ļص�����
	joinGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ClientScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//���ò˵���ť��Tag
	joinGameBtn->setTag(JOIN_GAME);
	//����Menu������
	addChild(joinGameBtn);

	//���ò˵�������ͼƬ
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//���ò˵�����ͼƬ
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//�����˵�����Ҫ��Label����
	LabelTTF * backGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("����"), "�����п�", 25);
	//����controlButton
	ControlButton * backGameBtn = ControlButton::create(backGameTTF, NormalButton2);
	//���Ӳ˵����µ�Ч��ͼƬ
	backGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//���ò˵����λ��
	backGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//���õ���Ļص�����
	backGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ClientScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//���ò˵���ť��Tag
	backGameBtn->setTag(GO_BACK);
	//����Menu������
	addChild(backGameBtn);
}

void ClientScene::waitStart()
{
	//socket_client_->camp();
	unscheduleAllCallbacks();
	log("get the camp");
	log("start game");
	auto scene = GameScene::createScene(socket_client_, nullptr);
	Director::getInstance()->replaceScene(TransitionSplitCols::create(0.5, scene));
}

void ClientScene::startSchedule(float f)
{
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
}

void ClientScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	ControlButton * button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case JOIN_GAME:
	{
		if (!socket_client_)
		{
			auto ip_box = static_cast<ui::EditBox*>(getChildByTag(1));
			std::string ip = ip_box->getText();
			auto port_box = static_cast<ui::EditBox*>(getChildByTag(2));
			int port = atoi(port_box->getText());
			log("ip:%s, port:%d", ip.c_str(), port);
			socket_client_ = SocketClient::create(ip, port);
			schedule(schedule_selector(ClientScene::startSchedule), 0.1);
			//	std::async(&ClientMenu::wait_start, this);
			//	wait_start();	
		}
		break;
	}
	case GO_BACK:
	{
		if (socket_client_)
		{
			unscheduleAllSelectors();
			socket_client_->close();
			delete socket_client_;
			socket_client_ = nullptr;
		}
		Director::getInstance()->popScene();
		break;
	}
	break;
	}
}
