#include"MenuScene.h"

//初始化场景
bool MenuScene::init()
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

//创建场景
Scene * MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

//添加场景背景
void MenuScene::addBackgroundSprite()
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
void MenuScene::addMenuSprites()
{
	//1 single game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * singleGameTTF = LabelTTF::create("single game", "arial", 25);
	//创建controlButton
	ControlButton * singleGameBtn = ControlButton::create(singleGameTTF, NormalButton);
	//添加singleButton菜单按下的效果图片
	singleGameBtn->setBackgroundSpriteForState(PressButton, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	singleGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.65);
	//设置点击的回调方法
	singleGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	singleGameBtn->setTag(1);
	//添加Menu到场景
	addChild(singleGameBtn);

	//2 multi game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * multiGameTTF = LabelTTF::create("multi game", "arial", 25);
	//创建controlButton
	ControlButton * multiGameBtn = ControlButton::create(multiGameTTF, NormalButton2);
	//添加singleButton菜单按下的效果图片
	multiGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	multiGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.52);
	//设置点击的回调方法
	multiGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	multiGameBtn->setTag(2);
	//添加Menu到场景
	addChild(multiGameBtn);

	//3 introdunction
	//设置菜单的正常图片
	Scale9Sprite * NormalButton3 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton3 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * introGameTTF = LabelTTF::create("introdunction", "arial", 25);
	//创建controlButton
	ControlButton * introGameBtn = ControlButton::create(introGameTTF, NormalButton3);
	//添加singleButton菜单按下的效果图片
	introGameBtn->setBackgroundSpriteForState(PressButton3, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	introGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.39);
	//设置点击的回调方法
	introGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	multiGameBtn->setTag(3);
	//添加Menu到场景
	addChild(introGameBtn);

	//4 quit game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton4 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton4 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * quitGameTTF = LabelTTF::create("quit game", "arial", 25);
	//创建controlButton
	ControlButton * quitGameBtn = ControlButton::create(quitGameTTF, NormalButton4);
	//添加singleButton菜单按下的效果图片
	quitGameBtn->setBackgroundSpriteForState(PressButton4, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	quitGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.26);
	//设置点击的回调方法
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	multiGameBtn->setTag(4);
	//添加Menu到场景
	addChild(quitGameBtn);
}

//Menu点击回调方法
void MenuScene::menuTouchDown(Object *pSender, Control::EventType event)
{
	ControlButton * button = (ControlButton*)pSender;
	int tag = button->getTag();
	switch (tag)
	{
		case 1:
		{

		}
		case 2:
		{

		}
		case 3:
		{

		}
		case 4:
		{

		}
		break;
	}
}