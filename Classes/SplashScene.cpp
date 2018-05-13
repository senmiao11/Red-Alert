#include"SplashScene.h"

//初始化场景
bool SplashScene::init()                    
{
	//若初始化失败，返回false
	if (!Layer::init())
	{
		return false;
	}
	//初始化窗口尺寸变量
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//初始化动画精灵方法
	initMoveSprite();
	//创建定时器，场景开始一秒后动画开始播放
	scheduleOnce(schedule_selector(SplashScene::startMoveSprite), 1);
	return true;
}

//创建场景
Scene * SplashScene::createScene()          
{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

//初始化图片
void SplashScene::initMoveSprite()           
{
	//创建精灵
	hong_Sprite = Sprite::create(HONG_IMAGE);
	se_Sprite = Sprite::create(SE_IMAGE);
	jing_Sprite = Sprite::create(JING_IMAGE);
	jie_Sprite = Sprite::create(JIE_IMAGE);
	//获取动画尺寸赋值,每个图片大小相同（117*113）
	spriteSize = hong_Sprite->getContentSize();
	//从左到右放置精灵图片，效果为“色警戒红”
	se_Sprite->setPosition(ccp((visibleSize.width / 2 )- (2* spriteSize.width),visibleSize.height/2));
	jing_Sprite->setPosition(ccp(visibleSize.width / 2 - spriteSize.width, visibleSize.height / 2));
	jie_Sprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	hong_Sprite->setPosition(ccp(visibleSize.width / 2 + spriteSize.width, visibleSize.height/2));
	//把精灵锚点设置在(0,0.5)，这样能保证四张图片居中排列在窗口位置
	hong_Sprite->setAnchorPoint(ccp(0, 0.5));
	se_Sprite->setAnchorPoint(ccp(0, 0.5));
	jing_Sprite->setAnchorPoint(ccp(0, 0.5));
	jie_Sprite->setAnchorPoint(ccp(0, 0.5));
	//添加精灵到场景
	this->addChild(hong_Sprite);
	this->addChild(se_Sprite);
	this->addChild(jing_Sprite);
	this->addChild(jie_Sprite);
}

//开始移动方法
void SplashScene::startMoveSprite(float dt)
{
	//动画从右向左开始，最末一个精灵首先开始从右向左移动一个位置
	MoveBy * movehongToLeft1 = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	hong_Sprite->runAction(movehongToLeft1);
	//精灵jie从左向右移动一个位置，这两个动画相当于jie与hong交换位置
	MoveBy * movejieToRight = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc * callFunc1 = CallFunc::create(CC_CALLBACK_0(SplashScene::moveJingSpriteToRight, this));
	//精灵jie动画结束后调用moveJingSpriteToLeft()方法，开始精灵jing的动画
	jie_Sprite->runAction(Sequence::create(movejieToRight, callFunc1, NULL));
}

//精灵jing动画
void SplashScene::moveJingSpriteToRight()
{
	//精灵hong从右向左再次移动一个位置
	MoveBy * movehongToLeft2 = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	hong_Sprite->runAction(movehongToLeft2);
	//精灵jing从左向右移动一个位置，同hong交换位置
	MoveBy * movejingToRight = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc * callFunc2 = CallFunc::create(CC_CALLBACK_0(SplashScene::moveSeSpriteToRight, this));
	//精灵jing动画结束后调用moveJingSpriteToLeft()方法，开始精灵se的动画
	jing_Sprite->runAction(Sequence::create(movejingToRight, callFunc2, NULL));
}

//精灵se动画
void SplashScene::moveSeSpriteToRight()
{
	//精灵hong从右向左再次移动一个位置
	MoveBy * movehongToLeft3 = MoveBy::create(MOVE_SPLEED, ccp(-spriteSize.width, 0));
	hong_Sprite->runAction(movehongToLeft3);
	//精灵se从左向右移动一个位置，同hong交换位置
	MoveBy * moveseToRight = MoveBy::create(MOVE_SPLEED, ccp(spriteSize.width, 0));
	CallFunc * callFunc3 = CallFunc::create(CC_CALLBACK_0(SplashScene::spriteFadeOut, this));
	//精灵se动画结束后调用spriteFadeOut()方法，开始场景消失的动画
	se_Sprite->runAction(Sequence::create(moveseToRight, callFunc3, NULL));
}

//场景消失动画
void SplashScene::spriteFadeOut()
{
	//定义四个消失的FadeOut动画，持续时间2s
	FadeOut * fadeout1 = FadeOut::create(2);
	FadeOut * fadeout2 = FadeOut::create(2);
	FadeOut * fadeout3 = FadeOut::create(2);
	FadeOut * fadeout4 = FadeOut::create(2);
	se_Sprite->runAction(fadeout1);
	jing_Sprite->runAction(fadeout2);
	jie_Sprite->runAction(fadeout3);
	CallFunc * callFunc4 = CallFunc::create(CC_CALLBACK_0(SplashScene::gotoMenuScene, this));
	//动画结束后调用gotoMenuScene()方法进入MenuScene场景
	hong_Sprite->runAction(Sequence::create(fadeout4, callFunc4, NULL));
}

//进入场景MenuScene
void SplashScene::gotoMenuScene()
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}