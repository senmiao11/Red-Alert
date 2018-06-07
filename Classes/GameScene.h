//游戏界面

#ifndef __GameScene_H_
#define __GameScene_H_
#include"cocos2d.h"
#include<iostream>
#include"MyUtility.h"
#include"ConstUtil.h"
#include"MenuScene.h"
#include"Buildings/Buildings.h"
<<<<<<< HEAD
#include"Soldiers/Soldiers.h"
=======
#include"Soldiers.h"
>>>>>>> xiaorui

USING_NS_CC;
class MouseRect :public DrawNode
{
public:
	CREATE_FUNC(MouseRect);
	Point touch_start, touch_end;
	Point start, end;
	void update(float dt);
	void reset();
};

<<<<<<< HEAD

=======
>>>>>>> xiaorui
class GameScene :public Layer
{
public:

	static Scene *createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	CREATE_FUNC(GameScene);
	void update(float dt);
	void scrollMap();
	static TMXTiledMap *gettiledMap()
	{
		return _tiledMap1;
	}


	//获得是否可以建造的标签
	static LabelTTF *getIfBuild()
	{
		return ifBuild;
	}
	static TMXTiledMap *gettiledMap()
	{
		return _tiledMap1;
	}
	static Rect getSelectRect()
	{
		return select_rect;
	}
private:
	//EventListenerTouchOneByOne * touchBuildingListener;
	EventListenerMouse * mouse_event;//地图移动的鼠标事件
	void onMouseMove(Event *event);
	bool p_flag = true;//第一次按会关掉地图移动鼠标事件，再按可开启
	EventListenerKeyboard * keyboard_listener;//各种键盘事件
	void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* pEvent);
	EventListenerPhysicsContact * buildingContactListener;//建筑物接触监听器

	MouseRect *mouseRect = nullptr;
	EventListenerTouchOneByOne *mouseRectListener;
	bool mouseRectOnTouchBegan(Touch *pTouch, Event *event);
	void mouseRectOnTouchMoved(Touch *pTouch, Event *event);
	void mouseRectOnTouchEnded(Touch *pTouch, Event *event);
	static Rect select_rect;


	void backToMenuScene(Ref *pSender);//返回MenuScene
	void buildingsCreate(Ref *pSender);//选择建筑物建造，建筑物菜单回调方法
<<<<<<< HEAD
	void soldiersCreate(Ref *pSender); //选择兵种生产，兵种菜单回调方法

	void casernReady(float dt);           //兵营准备
	void electricStationReady(float dt);  //电厂准备
	void tankFactoryReady(float dt);      //战车工厂准备
	void oreYardReady(float dt);          //矿场准备


	void minerReady(float dt);
=======
	void soldiersCreate(Ref *pSender);//选择产生兵种

	void casernReady(float dt);//兵营准备
	void electricStationReady(float dt);  //电厂准备
	void minerReady(float dt);
							   //////////////////////////////
							   //待添加其他建筑物的准备方法
							   //////////////////////////////
>>>>>>> xiaorui

	static int Money;//金钱
	void moneyUpdate(float dt);//实时刷新金钱

	static LabelTTF *ifBuild;//建筑物不可建造时显示的标签
<<<<<<< HEAD
	static TMXTiledMap * _tiledMap1;  //瓦片地图
	Point crusor_position{ 0, 0 };
=======

	static TMXTiledMap * _tiledMap1;
	Point crusor_position{ 0, 0 };

>>>>>>> xiaorui
};


#endif // !__GameScene_H_
