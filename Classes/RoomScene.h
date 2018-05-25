//房间列表界面

#ifndef __RoomScene_H_
#define __RoomScene_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include "popupLayer/PopupLayer.h"
#include"MyUtility.h"
#include "ServerScene.h"
#include "ClientScene.h"
USING_NS_CC_EXT;
USING_NS_CC;
#define START_SERVER 1
#define START_CLIENT 2
#define GO_BACK 3

class RoomScene:public Layer
{
public:
	static Scene* createScene();                                      //创建场景
	virtual bool init();                                              //初始化场景
	CREATE_FUNC(RoomScene);                                           //完成create方法代码的生成
	void addMenuSprites();                                            //添加Menu
private:
	Size visibleSize;                                                 //窗口尺寸
	void addBackgroundSprite();                                       //添加场景背景
	void menuTouchDown(Object *pSender, Control::EventType event);    //Menu点击回调方法
	void jumpToServerScene(float dt);                                  //跳转到ServeScene
	void jumpToClientScene(float dt);                                 //跳转到ClientScene
};

#endif // !__RoomScene_H_

