/*资源类*/

#ifndef __Resources_H_
#define __Resources_H_
//定义红色警戒图片资源
#define HONG_IMAGE "hong.png"
#define SE_IMAGE "se.png"
#define JING_IMAGE "jing.png"
#define JIE_IMAGE "jie.png"
#define HONGSEJINGJIE_IMAGE "hongsejingjie.png"
#define MENU_BACKGROUND  "menubackground.png"
#define NORMAL_MENU "normalmenu.png"              //150*60
#define PRESS_MENU "pressmenu.png"                //180*80
#define INPUT_IP   "InputIP.png"
#define INPUT_PORT "InputPort.png"
//对话框
#define DIALOG_BG "popuplayer/dialogbackground.png"
#define DIALOG_BUTTON "popuplayer/dialogbutton.png"
#define DIALOG_BUTTON2 "popuplayer/dialogbutton2.png"
//建筑物
#define BASE "building/base.png"
#define CASERN "building/casern.png"
#define ELECTRICSTATION "building/electricStation.png"
#define OREYARD "building/oreYard.png"
#define TANKFACTORY "building/tankFactory.png"

#define CAN_MOVE true
#define CANNOT_MOVE false

#define BASE_HEALTH 20000
#define CASERN_PRICE 4000
#define CASERN_HEALTH 10000
#define ELECTRICSTATION_PRICE 2000
#define ELECTRICSTATION_HEALTH 6000
#define TANKFACTORY_PRICE 2800
#define TANKFACTORY_HEALTH 7000
#define OREYARD_PRICE 1500
#define OREYARD_HEALTH 4000

typedef enum
{
	START_BASE = 1,
	START_CASERN = 2,
	START_ELECTRICSTATION = 3,
	START_TANKFACTORY = 4,
	START_OREYARD = 5,
}BuildingTypes;

//游戏界面节点
#define GameSceneNodeTagBuilding 512
#define GameSceneNodeTagMoney 1024
#define GameSceneNodeTagSoldier 2048
#define GameSceneNodeTagFire 4096

//地图
#define GAMEMAP1 "map/GameMap1.tmx"
#define GAMEMAP2 "map/GameMap2.tmx"
#define BOX_EDGE_WITDH 40
#define BOX_EDGE_WITDH_SMALL 10
#define SCROLL_LENGTH 10



//兵种
typedef enum
{
	START_MINER = 1,
	START_POLICEMAN = 2,
	START_WARRIOR = 3,
	START_TANK = 4
}SoldierTypes;

#define MIN_SELECT_RECT_SIZE 1
#define SELECT_ON true
#define SELECT_OFF false

#define MINER1 "soldiers/miner1.png"
#define MINER2 "soldiers/miner2.png"
#define MINER3 "soldiers/miner3.png"
#define MINER4 "soldiers/miner4.png"
#define POLICEMAN1 "soldiers/police1.png"
#define POLICEMAN2 "soldiers/police2.png"
#define POLICEMAN3 "soldiers/police3.png"
#define POLICEMAN4 "soldiers/police4.png"
#define WARRIOR1 "soldiers/warrior1.png"
#define WARRIOR2 "soldiers/warrior2.png"
#define WARRIOR3 "soldiers/warrior3.png"
#define WARRIOR4 "soldiers/warrior4.png"
#define TANK1 "soldiers/tank1.png"
#define TANK2 "soldiers/tank2.png"
#define TANK3 "soldiers/tank3.png"
#define TANK4 "soldiers/tank4.png"
#define MINER_PRICE 100
#define MINER_HEALTH 200
#define MINER_SPEED 0.4f
#define MINER_ATK_RADIUS 80
#define MINER_POWER 20
#define POLICEMAN_PRICE 150
#define POLICEMAN_HEALTH 300
#define POLICEMAN_SPEED 0.3f
#define POLICEMAN_ATK_RADIUS 80
#define POLICEMAN_POWER 30
#define WARRIOR_PRICE 220
#define WARRIOR_HEALTH 370
#define WARRIOR_SPEED 0.5f
#define WARRIOR_ATK_RADIUS 80
#define WARRIOR_POWER 40
#define TANK_PRICE 300
#define TANK_HEALTH 500
#define TANK_SPEED 0.15f
#define TANK_ATK_RADIUS 80
#define TANK_POWER 500

#define KEY_FRAME 5
#endif 