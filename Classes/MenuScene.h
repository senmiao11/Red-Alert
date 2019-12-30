/*�˵�����*/

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
	static Scene* createScene();                                      //��������
	virtual bool init();                                              //��ʼ������
	CREATE_FUNC(MenuScene);                                           //���create�������������
	void popupQuitLayer();                                            //�����Ի���������������ʾ����
	void quitButtonCallback(Node* pNode);                             //�Ի��򰴼��ľ�����Ӧ�취
	void menuMusicCallBack(cocos2d::Ref* pSender);
private:
	Size visibleSize;                                                 //���ڳߴ�
	void addBackgroundSprite();                                       //���ӳ�������
	void addMenuSprites();                                            //����Menu
	void menuTouchDown(Object *pSender,Control::EventType event);     //Menu����ص�����
	void jumpToIntroduction(float dt);                                //��ת��IntroScene
	void jumpToRoomScene(float dt);                                   //��ת��RoomScene
	bool is_paused;
};

#endif // !__MenuScene_H_

