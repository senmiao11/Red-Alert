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
<<<<<<< HEAD
#define CASERN "building/casern.png"
#define ELECTRICSTATION "building/electricStation.png"
=======
>>>>>>> xiaorui

#define CAN_MOVE true
#define CANNOT_MOVE false

#define BASE_HEALTH 20000
#define CASERN_PRICE 4000
#define CASERN_HEALTH 10000
#define ELECTRICSTATION_PRICE 2000
#define ELECTRICSTATION_HEALTH 6000

typedef enum
{
<<<<<<< HEAD
	START_BASE = 1,
	START_CASERN = 2,
	START_ELECTRICSTATION=3,
=======
	START_BASE = 100,
	CASERN
>>>>>>> xiaorui

}BuildingTypes;

//游戏界面节点
#define GameSceneNodeTagBuilding 512
#define GameSceneNodeTagMoney 1024

//地图
<<<<<<< HEAD
#define GAMEMAP1 "map/GameMap1.tmx"
=======
#define GameMap1 "map/GameMap1.tmx"
>>>>>>> xiaorui
#define BOX_EDGE_WITDH 40
#define BOX_EDGE_WITDH_SMALL 10
#define SCROLL_LENGTH 10

<<<<<<< HEAD
//兵种
typedef enum
{
	MINER = 1,
	POLICEMAN = 2,
	SOLDIER = 3,
	TANK = 4
}soldiers;
#define MINER_IMAGE "soldiers/miner.png"
#define POLICEMAN_IMAGE "soldiers/policeman.png"
#define SOLDIER_IMAGE "sildiers/soldier.png"
#define TANK_IMAGE "soldiers/tank.png"
#define MINER_PRICE 100

=======
>>>>>>> xiaorui


#endif 