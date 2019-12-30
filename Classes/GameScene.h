//��Ϸ����

#ifndef __GameScene_H_
#define __GameScene_H_
#include"cocos2d.h"
#include<iostream>
#include"MyUtility.h"
#include"ConstUtil.h"
#include"MenuScene.h"
#include"Buildings/Buildings.h"
#include"Soldiers/Soldiers.h"
#include"SimpleAudioEngine.h"
#include"network/SocketClient.h"
#include"network/SocketServer.h"
#include"network/socket_message.h"
using namespace ui;
USING_NS_CC;
class MouseRect :public DrawNode
{
public:
	CREATE_FUNC(MouseRect);
	Point touch_start;             //������ʼ��
	Point touch_end;               //����������
	Point start, end;              //ѡ��ʼ ������
	void update(float dt);         //�����εĸ��º���
	void reset();                  //�����趨����
};


class GameScene :public Layer
{
public:
	static GameScene* create(SocketClient* _socket_client, SocketServer* _socket_server);
	static Scene *createScene(SocketClient* _socket_client, SocketServer* _socket_server = nullptr);
	virtual bool init(SocketClient* _socket_client, SocketServer* _socket_server);
	virtual void onEnter();
	virtual void onExit();
	void update(float dt);
	void scrollMap();
	static TMXTiledMap *gettiledMap()
	{
		return _tiledMap1;
	}
	static Rect getSelectRect()
	{
		return select_rect;
	}
	static Rect select_rect;


private:
	//EventListenerTouchOneByOne * touchBuildingListener;
	//��ͼ��ط���
	EventListenerMouse * mouse_event;//��ͼ�ƶ�������¼�
	void onMouseMove(Event *event);
	bool p_flag = true;              //��һ�ΰ���ص���ͼ�ƶ�����¼����ٰ��ɿ���

	//���̲�����ط���
	EventListenerKeyboard * keyboard_listener;//���ּ����¼�
	void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* pEvent);

	EventListenerPhysicsContact * spriteContactListener;//������Ӵ�������

	//�˵���ť
	void backToMenuScene(Ref *pSender);//����MenuScene
	void buildingsCreate(Ref *pSender);//ѡ�����ｨ�죬������˵��ص�����
	void soldiersCreate(Ref *pSender); //ѡ��������������ֲ˵��ص�����

	//������׼������
	void casernReady(float dt);           //��Ӫ׼��
	void electricStationReady(float dt);  //�糧׼��
	void tankFactoryReady(float dt);      //ս������׼��
	void oreYardReady(float dt);          //��׼��

	//����׼������
	void minerReady(float dt);
	void policemanReady(float dt);
	void tankReady(float dt);

	//��Ǯ��ط���
	void moneyUpdate(float dt);//ʵʱˢ�½�Ǯ
	static int Money;          //��Ǯ

	static TMXTiledMap * _tiledMap1;  //��Ƭ��ͼ



//Mouse Rect��ط���
public:
	Rect getvisionRect();
private:
	MouseRect *mouseRect = nullptr;
	EventListenerTouchOneByOne *mouseRectListener;
	bool ctrl_flag = true;//��һ�ΰ�ctrl��ص������ο��ٰ����Կ���
	bool mouseRectOnTouchBegan(Touch *pTouch, Event *event);
	void mouseRectOnTouchMoved(Touch *pTouch, Event *event);
	void mouseRectOnTouchEnded(Touch *pTouch, Event *event);
	//MiniMap* mini_map = nullptr;
	Rect mini_map_rect{};
	Point last_touch{ 0, 0 };
	Point crusor_position{ 0, 0 };

//network
	SocketServer* socket_server = nullptr;
	SocketClient* socket_client = nullptr;
};

/***************************************************
class MiniMap : public cocos2d::DrawNode
{
public:
	CREATE_FUNC(MiniMap);
	void update(float dt) override;
	void setGridMap(GridMap* _grid_map);
	void setUnitManager(UnitManager* _unit_manager);
	void setBattleScene(GameScene* _battle_scene);
private:
	GridMap * grid_map;
	UnitManager* unit_manager;
	GameSceneScene* battle_scene;
};
***************************************************/

#endif // !__GameScene_H_
