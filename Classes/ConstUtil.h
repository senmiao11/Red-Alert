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
<<<<<<< HEAD
#define OREYARD "building/oreYard.png"
#define TANKFACTORY "building/tankFactory.png"
=======
>>>>>>> xiaorui

#define CAN_MOVE true
#define CANNOT_MOVE false

#define BASE_HEALTH 20000
#define CASERN_PRICE 4000
#define CASERN_HEALTH 10000
#define ELECTRICSTATION_PRICE 2000
#define ELECTRICSTATION_HEALTH 6000
<<<<<<< HEAD
#define TANKFACTORY_PRICE 2800
#define TANKFACTORY_HEALTH 7000
#define OREYARD_PRICE 1500
#define OREYARD_HEALTH 4000
=======
>>>>>>> xiaorui

typedef enum
{
	START_BASE = 1,
	START_CASERN = 2,
	START_ELECTRICSTATION = 3,
<<<<<<< HEAD
	START_TANKFACTORY = 4,
	START_OREYARD = 5,
=======

>>>>>>> xiaorui
}BuildingTypes;

//游戏界面节点
#define GameSceneNodeTagBuilding 512
#define GameSceneNodeTagMoney 1024
#define GameSceneNodeTagSoldier 2048

//地图
#define GAMEMAP1 "map/GameMap1.tmx"
#define BOX_EDGE_WITDH 40
#define BOX_EDGE_WITDH_SMALL 10
#define SCROLL_LENGTH 10

//兵种
typedef enum
{
<<<<<<< HEAD
	START_MINER = 1,
	START_POLICEMAN = 2,
	START_SOLDIER = 3,
	START_TANK = 4
}SoldierTypes;

#define MINER "soldiers/miner.png"
#define POLICEMAN "soldiers/policeman.png"
#define SOLDIER "sildiers/soldier.png"
#define TANK "soldiers/tank.png"
#define MINER_PRICE 100
#define MINER_HEALTH 200
#define POLICEMAN_PRICE 150
#define POLICEMAN_HEALTH 300
#define TANK_PRICE 300
#define TANK_HEALTH 450

=======
	MINER = 11,
	POLICEMAN = 12,
	SOLDIER = 13,
	TANK = 14
}SoldierTypes;
#define MINER_IMAGE "soldiers/miner.png"
#define POLICEMAN_IMAGE "soldiers/policeman.png"
#define SOLDIER_IMAGE "sildiers/soldier.png"
#define TANK_IMAGE "soldiers/tank.png"
#define MINER_PRICE 100
#define MINER_HEALTH 200
>>>>>>> xiaorui

#define MIN_SELECT_RECT_SIZE 1
#define SELECT_ON true
#define SELECT_OFF false

#endif 