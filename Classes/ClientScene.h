//客户端界面

#ifndef __ClientScene_H_
#define __ClientScene_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include "popupLayer/PopupLayer.h"
#include"MyUtility.h"
USING_NS_CC_EXT;
USING_NS_CC;
#define JOIN_GAME 10
#define GO_BACK 11

class ClientScene :public Layer
{
public:
	static Scene* createScene();                                      //创建场景
	virtual bool init();                                              //初始化场景
	CREATE_FUNC(ClientScene);                                          //完成create方法代码的生成
	void addMenuSprites();                                            //添加Menu
	void waitStart();
	void startSchedule(float f);
private:
	Size visibleSize;                                                 //窗口尺寸
	void addBackgroundSprite();                                       //添加场景背景
	void menuTouchDown(Object *pSender, Control::EventType event);    //Menu点击回调方法
	Label * connection_msg_;
	/**********SocketClient* socket_client_{ nullptr };       *********/
	int timer_ = 0;
};

#endif // !__ClientScene_H_
