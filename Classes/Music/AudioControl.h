#pragma once
#ifndef AUDIOCONTROL_H_
#define AUDIOCONTROL_H_

#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"MenuScene.h"
#include"MyUtility.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

/*
AudioControl类 继承自Layer
进行音量大小的控制
*/
class AudioControl :public Layer
{
public:

	//创建场景函数
	static Scene* createScene();
    //初始化函数
	virtual bool init();
	void musicTogglemenuCallBack(Ref* pSender);
	void effectTogglemenuCallBack(Ref* pSender);
	void onEnter();

	CREATE_FUNC(AudioControl);
};


#endif // !AUDIOCONTROL_H_
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"