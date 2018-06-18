#ifndef _GameManager_H_
#define _GameManager_H_
#include"cocos2d.h"
#include<iostream>
#include"MyUtility.h"
#include"ConstUtil.h"
#include"MenuScene.h"
#include"Buildings/Buildings.h"
#include"Soldiers/Soldiers.h"
#include"network/SocketClient.h"
#include"network/SocketServer.h"
#include"network/socket_message.h"
#include"network/GameMessage.pb.h"
#include"network/GameMessageWrap.h"

USING_NS_CC;

class GameManager:public cocos2d::Ref
{
	friend class Soldiers;
	friend class Buildings;
	friend class GameScene;
	friend class Notice;
public:
	CREATE_FUNC(GameManager);
	bool init();                                                 //初始化
	GameMessageSet* msgs = nullptr;                              //游戏消息集
	void setMessageSet(GameMessageSet* _msgs);                   //设置消息集
	void setTiledMap(TMXTiledMap* _tiledMap);                    //设置瓦片地图
	void setGameScene(GameScene* _game_scene);                   //设置游戏场景
	void setNotice(Notice* _notice);                             //游戏提示
	void setSocketClient(SocketClient* _socket_client);          //如果是客户端，则设置客户端套接字
	void setPlayerID(int _player_id);                            //设置玩家ID
	int  getPlayerID();                                          //获取单位所属阵营
	int  getnextID();                                            //获取下一个生产ID
	void setPlayernum(int _player_num);                          //设置玩家总数
	int  getPlayernum();                                         //获取玩家总数
	void produceSoldiers(SoldierTypes soldierType, int _player_id, int _id);              //生产士兵
	void produceBuildings(BuildingTypes buildingType, int _player_id, int _id);           //生产建筑
	void updateGameState();                                      //通过网络收法消息，更新游戏状态
	void genCreateBuildingMessage(BuildingTypes buildingtype);   //产生建筑物生产信息
	void genCreateSoldierMessage(SoldierTypes soldiertype);       //产生兵种生产信息
	void deleteAll(int _player_id);                               //失败后移除所有建筑和士兵

private:
	Map<int, Soldiers*> sid_map;                                 //ID和士兵对应表
	Map<int, Buildings*> bid_map;                                //ID和建筑对应表
	SocketClient * socket_client = nullptr;                      //客户端套接字
	int player_id;                                               //玩家ID
	int player_num;                                              //玩家总数
	int next_id;                                                 //下一个生产单位的id
    TMXTiledMap* tiledMap;                                       //瓦片地图
	GameScene* game_scene;                                       //游戏场景
	Notice* notice = nullptr;                                    //游戏提示

};


#endif //!_GameManager_H_
