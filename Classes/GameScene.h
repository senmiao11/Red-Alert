//游戏界面

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
using namespace ui;
USING_NS_CC;
class MouseRect :public DrawNode
{
public:
	CREATE_FUNC(MouseRect);
	Point touch_start;             //触摸开始点
	Point touch_end;               //触摸结束点
	Point start, end;              //选框开始 结束点
	void update(float dt);         //鼠标矩形的更新函数
	void reset();                  //重新设定参数
};


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
	static Rect getSelectRect()
	{
		return select_rect;
	}
	static Rect select_rect;

	//获得是否可以建造的标签
	static LabelTTF *getIfBuild()
	{
		return ifBuild;
	}

private:
	//EventListenerTouchOneByOne * touchBuildingListener;
	//地图相关方法
	EventListenerMouse * mouse_event;//地图移动的鼠标事件
	void onMouseMove(Event *event);
	bool p_flag = true;              //第一次按会关掉地图移动鼠标事件，再按可开启

	//键盘操作相关方法
	EventListenerKeyboard * keyboard_listener;//各种键盘事件
	void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event* pEvent);

	EventListenerPhysicsContact * buildingContactListener;//建筑物接触监听器

	//菜单按钮
	void backToMenuScene(Ref *pSender);//返回MenuScene
	void buildingsCreate(Ref *pSender);//选择建筑物建造，建筑物菜单回调方法
	void soldiersCreate(Ref *pSender); //选择兵种生产，兵种菜单回调方法

	//建筑物准备方法
	void casernReady(float dt);           //兵营准备
	void electricStationReady(float dt);  //电厂准备
	void tankFactoryReady(float dt);      //战车工厂准备
	void oreYardReady(float dt);          //矿场准备

	//兵种准备方法
	void minerReady(float dt);
	void policemanReady(float dt);
	void tankReady(float dt);

	//金钱相关方法
	void moneyUpdate(float dt);//实时刷新金钱
	static int Money;          //金钱

	static LabelTTF *ifBuild;//建筑物不可建造时显示的标签
	static TMXTiledMap * _tiledMap1;  //瓦片地图



//Mouse Rect相关方法
public:
	Rect getvisionRect();
private:
	MouseRect *mouseRect = nullptr;
	EventListenerTouchOneByOne *mouseRectListener;
	bool ctrl_flag = true;//第一次按ctrl会关掉画矩形框，再按可以开启
	bool mouseRectOnTouchBegan(Touch *pTouch, Event *event);
	void mouseRectOnTouchMoved(Touch *pTouch, Event *event);
	void mouseRectOnTouchEnded(Touch *pTouch, Event *event);
	//MiniMap* mini_map = nullptr;
	Rect mini_map_rect{};
	Point last_touch{ 0, 0 };
	Point crusor_position{ 0, 0 };
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
