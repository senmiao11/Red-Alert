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

#define CAN_MOVE true
#define CANNOT_MOVE false

#define BASE_HEALTH 20000
#define CASERN_PRICE 4000
#define CASERN_HEALTH 10000
#define ELECTRICSTATION_PRICE 2000
#define ELECTRICSTATION_HEALTH 6000

typedef enum
{
	START_BASE = 1,
	START_CASERN = 2,
	START_ELECTRICSTATION=3,

}BuildingTypes;

//游戏界面节点
#define GameSceneNodeTagBuilding 512
#define GameSceneNodeTagMoney 1024

//地图
#define GAMEMAP1 "map/GameMap1.tmx"
#define BOX_EDGE_WITDH 40
#define BOX_EDGE_WITDH_SMALL 10
#define SCROLL_LENGTH 10

//兵种
typedef enum
{
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



#endif 