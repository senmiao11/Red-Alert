#include"RoomScene.h"

Scene *RoomScene::createScene()
{
	auto scene = Scene::create();
	auto layer = RoomScene::create();
	scene->addChild(layer);
	return scene;
}

bool RoomScene::init()
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
	return true;
}

void RoomScene::addBackgroundSprite()
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
	this->addChild(MenuBackgroundSprite);
}

//添加Menu
void RoomScene::addMenuSprites()
{
	//1 start game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * startGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("创建游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * startGameBtn = ControlButton::create(startGameTTF, NormalButton1);
	//添加singleButton菜单按下的效果图片
	startGameBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	startGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//设置点击的回调方法
	startGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(RoomScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	startGameBtn->setTag(START_SERVER);
	//添加Menu到场景
	addChild(startGameBtn);

	//2 introdunction
	//设置菜单的正常图片
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * introGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("加入游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * introGameBtn = ControlButton::create(introGameTTF, NormalButton2);
	//添加singleButton菜单按下的效果图片
	introGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	introGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//设置点击的回调方法
	introGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(RoomScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	introGameBtn->setTag(START_CLIENT);
	//添加Menu到场景
	addChild(introGameBtn);

	//3 quit game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton3 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton3 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * quitGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 25);
	//创建controlButton
	ControlButton * quitGameBtn = ControlButton::create(quitGameTTF, NormalButton3);
	//添加singleButton菜单按下的效果图片
	quitGameBtn->setBackgroundSpriteForState(PressButton3, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	quitGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.32);
	//设置点击的回调方法
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(RoomScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	quitGameBtn->setTag(GO_BACK);
	//添加Menu到场景
	addChild(quitGameBtn);
}

void RoomScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	ControlButton * button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
	case START_SERVER:
	{
		scheduleOnce(schedule_selector(RoomScene::jumpToServerScene), 0.5);
		break;
	}
	case START_CLIENT:
	{
		scheduleOnce(schedule_selector(RoomScene::jumpToClientScene), 0.5);
		break;
	}
	case GO_BACK:
	{
		Director::getInstance()->popScene();
		break;
	}
	break;
	}
}

void RoomScene::jumpToServerScene(float dt)
{
	auto sc = ServerScene::createScene();
	auto reScene = TransitionFadeTR::create(0.5f, sc);
	Director::getInstance()->pushScene(reScene);
}

void RoomScene::jumpToClientScene(float dt)
{
	auto sc = ClientScene::createScene();
	auto reScene = TransitionFadeTR::create(0.5f, sc);
	Director::getInstance()->pushScene(reScene);
}
