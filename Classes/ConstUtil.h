//资源类

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
#define BASE "base.png"

#define CAN_MOVE true
#define CANNOT_MOVE false

#define BASE_HEALTH 20000
#define CASERN_PRICE 4000
#define CASERN_HEALTH 10000

typedef enum
{
	START_BASE = 1,
	CASERN

}BuildingTypes;


//游戏界面节点
#define GameSceneNodeTagBuilding 512
#define GameSceneNodeTagMoney 1024



#endif 