#include"ServerScene.h"

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
	//��ʼ�����ڳߴ����
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//���ӳ�������
	addBackgroundSprite();
	//����Menu
	addMenuSprites();
	//���Ӷ˿���Ϣ
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
	//��Ϣlabel
	connection_msg_ = Label::createWithTTF("", "/fonts/arial.ttf", 18);
	connection_msg_->setAnchorPoint(Vec2(0.5, 0));
	connection_msg_->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y));
	addChild(connection_msg_);
	return true;
}

//���ӱ���ͼƬ
void ServerScene::addBackgroundSprite()
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
void ServerScene::addMenuSprites()
{
	//1 ��ʾ��������Ϣ
	//���ò˵�������ͼƬ
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//���ò˵�����ͼƬ
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//�����˵�����Ҫ��Label����
	LabelTTF * MessageTTF = LabelTTF::create(MyUtility::gbk_2_utf8("����������"), "�����п�", 25);
	//����controlButton
	ControlButton * MessageBtn = ControlButton::create(MessageTTF, NormalButton1);
	//���Ӳ˵����µ�Ч��ͼƬ
	MessageBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//���ò˵����λ��
	MessageBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//���õ���Ļص�����
	MessageBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//���ò˵���ť��Tag
	MessageBtn->setTag(START_SERVER);
	//����Menu������
	addChild(MessageBtn);

	//2 ��ʼ��Ϸ
	//���ò˵�������ͼƬ
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//���ò˵�����ͼƬ
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//�����˵�����Ҫ��Label����
	LabelTTF * startGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("��ʼ��Ϸ"), "�����п�", 25);
	//����controlButton
	ControlButton * startGameBtn = ControlButton::create(startGameTTF, NormalButton2);
	//���Ӳ˵����µ�Ч��ͼƬ
	startGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//���ò˵����λ��
	startGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//���õ���Ļص�����
	startGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//���ò˵���ť��Tag
	startGameBtn->setTag(START_GAME);
	//����Menu������
	addChild(startGameBtn);

	//3 ������һ����(RoomScene)
	//���ò˵�������ͼƬ
	Scale9Sprite * NormalButton3 = Scale9Sprite::create(NORMAL_MENU);
	//���ò˵�����ͼƬ
	Scale9Sprite * PressButton3 = Scale9Sprite::create(PRESS_MENU);
	//�����˵�����Ҫ��Label����
	LabelTTF * backTTF = LabelTTF::create(MyUtility::gbk_2_utf8("����"), "�����п�", 25);
	//����controlButton
	ControlButton * backBtn = ControlButton::create(backTTF, NormalButton3);
	//���Ӳ˵����µ�Ч��ͼƬ
	backBtn->setBackgroundSpriteForState(PressButton3, Control::State::SELECTED);
	//���õ�����Ϸ�˵����λ��
	backBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.32);
	//���õ���Ļص�����
	backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(ServerScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//���ò˵���ť��Tag
	backBtn->setTag(GO_BACK);
	//����Menu������
	addChild(backBtn);
}

//��������Ķ˿���Ϣ
void ServerScene::editBoxReturn(EditBox* editBox)
{
	log(editBox->getText());
	int port = atoi(editBox->getText());
}

void ServerScene::connectionSchdeule(float f)
{
	if (socket_server_->connection_num())
		connection_msg_->setString("Total connection num: " + std::to_string(socket_server_->connection_num()));
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
		/*
		auto sc = GameScene::createScene();
		auto reScene = TransitionFadeTR::create(0.5f, sc);
		Director::getInstance()->pushScene(reScene);
		*/
		if (socket_server_)
		{
			socket_server_->button_start();
			auto sc = GameScene::createScene(socket_client_, socket_server_);
			auto reScene = TransitionFadeTR::create(0.5f, sc);
			Director::getInstance()->pushScene(reScene);
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




