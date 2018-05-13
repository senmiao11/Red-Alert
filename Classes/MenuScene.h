#ifndef __MenuScene_H_
#define __MenuScene_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
USING_NS_CC_EXT;
USING_NS_CC;
class MenuScene :public Layer
{
public:
	static Scene* createScene();                                      //创建场景
	virtual bool init();                                              //初始化场景
	CREATE_FUNC(MenuScene);                                           //完成create方法代码的生成
private:
	Size visibleSize;                                                 //窗口尺寸
	void addBackgroundSprite();                                       //添加场景背景
	void addMenuSprites();                                            //添加Menu
	void menuTouchDown(Object *pSender,Control::EventType event);      //Menu点击回调方法
};

#endif // !__MenuScene_H_

