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
	
	//1 start game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton1 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton1 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * startGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("开始游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * startGameBtn = ControlButton::create(startGameTTF, NormalButton1);
	//添加singleButton菜单按下的效果图片
	startGameBtn->setBackgroundSpriteForState(PressButton1, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	startGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.58);
	//设置点击的回调方法
	startGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	startGameBtn->setTag(START_GAME);
	//添加Menu到场景
	addChild(startGameBtn);

	//2 introdunction
	//设置菜单的正常图片
	Scale9Sprite * NormalButton2 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton2 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * introGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("游戏介绍"), "华文行楷", 25);
	//创建controlButton
	ControlButton * introGameBtn = ControlButton::create(introGameTTF, NormalButton2);
	//添加singleButton菜单按下的效果图片
	introGameBtn->setBackgroundSpriteForState(PressButton2, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	introGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.45);
	//设置点击的回调方法
	introGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	introGameBtn->setTag(INTRODUCTION);
	//添加Menu到场景
	addChild(introGameBtn);

	//3 quit game
	//设置菜单的正常图片
	Scale9Sprite * NormalButton3 = Scale9Sprite::create(NORMAL_MENU);
	//设置菜单按下图片
	Scale9Sprite * PressButton3 = Scale9Sprite::create(PRESS_MENU);
	//创建菜单所需要的Label对象
	LabelTTF * quitGameTTF = LabelTTF::create(MyUtility::gbk_2_utf8("退出游戏"), "华文行楷", 25);
	//创建controlButton
	ControlButton * quitGameBtn = ControlButton::create(quitGameTTF, NormalButton3);
	//添加singleButton菜单按下的效果图片
	quitGameBtn->setBackgroundSpriteForState(PressButton3, Control::State::SELECTED);
	//设置单机游戏菜单项的位置
	quitGameBtn->setPosition(visibleSize.width * 0.84, visibleSize.height * 0.32);
	//设置点击的回调方法
	quitGameBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::menuTouchDown), Control::EventType::TOUCH_DOWN);
	//设置菜单按钮的Tag
	quitGameBtn->setTag(QUIT_GAME);
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
		case START_GAME:    
		{
			//进入GameScene，并且伴随按行分割动画
			Scene *sc = Scene::create();
			auto layer = GameScene::create();
			sc->addChild(layer);
			auto reScene = TransitionSplitRows::create(1.0f, sc);
			Director::getInstance()->replaceScene(reScene);
			break;
		}
		case INTRODUCTION:
		{
			scheduleOnce(schedule_selector(MenuScene::jumpToIntroduction), 0.5);
			Director::getInstance()->replaceScene(SplashScene::createScene());
			break;
		}
		case QUIT_GAME:
		{
			popupQuitLayer();
			break;
		}
		break;
	}
}

//跳转到IntroScene
void MenuScene::jumpToIntroduction(float dt)
{

}

void MenuScene::popupQuitLayer()
{
	//根据背景创建对话框
	PopupLayer* popDialog = PopupLayer::create(DIALOG_BG);
	//设置对话框大小
	popDialog->setContentSize(CCSizeMake(350,200));
	//设置对话框标题，显示内容
	popDialog->setTitle("提示",18);
	popDialog->setContentText("确认退出游戏？",22,20,100);
	//在对话框中添加确定和取消的Menu按键，并设置各自的tag
	popDialog->addButton(DIALOG_BUTTON, DIALOG_BUTTON2, "是", 1);
	popDialog->addButton(DIALOG_BUTTON, DIALOG_BUTTON2, "否", 0);
	//设置对话框的按键相应方法
	popDialog->setCallbackFunc(this, callfuncN_selector(MenuScene::quitButtonCallback));
	this->addChild(popDialog);
}

void MenuScene::quitButtonCallback(Node* pNode)
{
	//根据按键的tag调用相应的方法
	if (pNode->getTag() == 1)
	{
		//点击确定，则退出
		Director::getInstance()->end();
	}
	else
	{
		//点击取消，则关闭对话框
		pNode->getParent()->removeFromParent();
	}
}