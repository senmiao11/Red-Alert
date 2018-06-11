/*菜单场景*/

#ifndef __MenuScene_H_
#define __MenuScene_H_
#define STRAT_GAME    1
#define INTRODUCTION  2
#define QUIT_GAME     3
#define SETTINGS      4

#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include "popupLayer/PopupLayer.h"
#include"SplashScene.h"
#include"MyUtility.h"
#include"RoomScene.h"
#include"SimpleAudioEngine.h"
#include"Music/AudioControl.h"
using namespace ui;
USING_NS_CC_EXT;
USING_NS_CC;

class MenuScene :public Layer
{
public:
	static Scene* createScene();                                      //创建场景
	virtual bool init();                                              //初始化场景
	CREATE_FUNC(MenuScene);                                           //完成create方法代码的生成
	void popupQuitLayer();                                            //创建对话框，设置类型与显示内容
	void quitButtonCallback(Node* pNode);                             //对话框按键的具体响应办法
	void menuMusicCallBack(cocos2d::Ref* pSender);
private:
	Size visibleSize;                                                 //窗口尺寸
	void addBackgroundSprite();                                       //添加场景背景
	void addMenuSprites();                                            //添加Menu
	void menuTouchDown(Object *pSender,Control::EventType event);     //Menu点击回调方法
	void jumpToIntroduction(float dt);                                //跳转到IntroScene
	void jumpToRoomScene(float dt);                                   //跳转到RoomScene
	bool is_paused;
};

#endif // !__MenuScene_H_

