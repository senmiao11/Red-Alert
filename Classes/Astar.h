#pragma once
#include<vector>
#include<list>
#include<unordered_map>
#include"Cocos2d.h"
USING_NS_CC;
using namespace std;


const int strMove = 10;
const int tiltMove = 14;

struct Apoint :public Ref
{
	int x, y;//坐标
	int F, G, H;//F=G+H
	Apoint* parent;
	//初始化
	Apoint(int _x,int _y):
		x(_x),y(_y),F(0),G(0),H(0),parent(NULL){}
};
class Astar {
public:
	void InitAstar(vector<bool>&_maze, int mapWidth,int mapHeight);
	vector<Apoint*> getPath(Apoint &startPoint, Apoint &endPoint, bool ifIgnoreCorner);
private:
	Apoint *findPath(Apoint &startPoint, Apoint &endPoint, bool ifIgnoreCorner);
	vector<Apoint*> getSurroundingPoints(const Apoint *point, bool ifIgnoreCorner)const;
	bool ifAbleReach
	(const Apoint *point, const Apoint *target, bool ifIngoreCorner)const;
    //判断某点是否可以用于下一步判断 
	Apoint* ifInList(const vector<Apoint*> &list, const Apoint *point)const;
	//判断开启/关闭列表中是否包含某点
	Apoint *getLeastF();
	//从开启列表中返回F值最小的节点  
	//计算FGH值
	int calculateG(Apoint *temp_start, Apoint *point);
	int calculateH(Apoint *point, Apoint *end);
	int calculateF(Apoint *point);
	
private:
	std::vector<bool> maze;
	vector<Apoint*> openList;  //开启列表  
	vector<Apoint*> closeList; //关闭列表  



	int width;
	int height;

};

