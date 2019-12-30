//����˽���

#ifndef __ServerScene_H_
#define __ServerScene_H_
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include "popupLayer/PopupLayer.h"
#include"MyUtility.h"
#include"GameScene.h"
#include"network/SocketClient.h"
#include"network/SocketServer.h"
#include"network/socket_message.h"
USING_NS_CC_EXT;
USING_NS_CC;
#define START_SERVER 4
#define START_GAME 5
#define GO_BACK 6

class ServerScene :public Layer
{
public:
	static Scene* createScene();                                      //��������
	virtual bool init();                                              //��ʼ������
	CREATE_FUNC(ServerScene);                                         //���create�������������
	void addMenuSprites();                                            //����Menu
private:
	Size visibleSize;                                                 //���ڳߴ�
	void addBackgroundSprite();                                       //���ӳ�������
	void menuTouchDown(Object *pSender, Control::EventType event);    //Menu����ص�����
	void editBoxReturn(EditBox* editBox);                             //��������Ķ˿���Ϣ
	void connectionSchdeule(float f);
	SocketServer* socket_server_{ nullptr };
	SocketClient* socket_client_{ nullptr };
	Label* connection_msg_;                                           //������Ϣ
};

#endif // !__ServerScene_H_
