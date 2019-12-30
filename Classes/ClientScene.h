/*�ͻ��˽���*/

#ifndef __ClientScene_H_
#define __ClientScene_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include "popupLayer/PopupLayer.h"
#include"MyUtility.h"
#include"network/SocketClient.h"
#include"network/SocketServer.h"
#include"network/socket_message.h"
#include"GameScene.h"
USING_NS_CC_EXT;
USING_NS_CC;
#define JOIN_GAME 10
#define GO_BACK 11

class ClientScene :public Layer
{
public:
	static Scene* createScene();                                      //��������
	virtual bool init();                                              //��ʼ������
	CREATE_FUNC(ClientScene);                                         //���create�������������
	void addMenuSprites();                                            //����Menu
	void waitStart();                                                 //�ȴ������ָ��
	void startSchedule(float f);
private:
	Size visibleSize;                                                 //���ڳߴ�
	void addBackgroundSprite();                                       //���ӳ�������
	void menuTouchDown(Object *pSender, Control::EventType event);    //Menu����ص�����
	Label * connection_msg_;
	SocketClient* socket_client_{ nullptr };     
	int timer_ = 0;
};

#endif // !__ClientScene_H_
