#include <math.h>  
#include "Astar.h"  

void Astar::InitAstar(vector<bool> &_maze, int mapWidth, int mapHeight)
{
	maze = _maze;
	width = mapWidth;
	height = mapHeight;
}
int Astar::calculateG(Apoint *temp_start, Apoint *point)
{
	int extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? strMove : tiltMove;
	//如果是初始节点，则其父节点是空
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return parentG + extraG;
}
int Astar::calculateH(Apoint *point, Apoint *end)
{
	return sqrt((double)(end->x - point->x)*(double)(end->x - point->x)+(double)(end->y-point->y)*(double)(end->y)-point->y)*strMove;
}
int Astar::calculateF(Apoint *point)
{
	return point->G + point->H;
}

Apoint *Astar::getLeastF()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto point : openList)
			if (point->F < resPoint->F)
				resPoint = point;
		return resPoint;
	}
	return NULL;
}
Apoint *Astar::findPath(Apoint &startPoint, Apoint &endPoint, bool ifIgnoreCorner)
{
	openList.clear();
	closeList.clear();
	openList.push_back(new Apoint(startPoint.x, startPoint.y));
	//置入起点,拷贝开辟一个节点，内外隔离  
	while (!openList.empty())
	{
		auto currentPoint = getLeastF();//找到F值最小的点
		vector<Apoint*>::iterator it = openList.begin();
		for (; it != openList.end(); it++)
		{
			if (*it == currentPoint)
				break;
		}

		openList.erase(it);//从开启列表中删除
		closeList.push_back(currentPoint);//放到关闭列表 
		//1,找到当前周围八个格中可以通过的格子  
		auto surroundingPoints = getSurroundingPoints(currentPoint, ifIgnoreCorner);
		for (auto &target : surroundingPoints)
		{
			//2,对某一个格子，如果它不在开启列表中，
			//加入到开启列表，设置当前格为其父节点，
			//计算F G H  
			if (!ifInList(openList, target))
			{
				target->parent = currentPoint;
				target->G = calculateG(currentPoint, target);
				target->H = calculateH(target, &endPoint);
				target->F = calculateF(target);
				openList.push_back(target);
			}
			//3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F  
			else
			{
				int tempG = calculateG(currentPoint, target);
				if (tempG < target->G)
				{
					target->parent = currentPoint;
					target->G = tempG;
					target->F = calculateF(target);
				}
				
					
				
			}
			Apoint *resPoint = ifInList(openList, &endPoint);
			if (resPoint)
				return resPoint;
			

		}
	}
	return NULL;
}
vector<Apoint*> Astar::getPath(Apoint &startPoint, Apoint &endPoint, bool ifIgnoreCorner)
{
	log("from point============>%d,%d", startPoint.x, startPoint.y);
	log("to point===========>%d,%d", endPoint.x, endPoint.y);
	Apoint *result = findPath(startPoint, endPoint, ifIgnoreCorner);
	vector<Apoint*> path;
	//返回路径
	//如果没找到路径，返回空链表
	int s = 1;
	while (result->parent)
	{
		vector<Apoint*>::iterator it = path.begin();
		for (; it != path.end(); it++)
		{
			if (*it == result)
				break;
		}
		path.insert(it, 0);
		result = result->parent;
		s++;
	}
	log("s===>%d", s);
	return path;
}
Apoint *Astar::ifInList(const vector<Apoint*>&list, const Apoint *point)const
{
	//判断某个节点是否在列表中
	//比较坐标
	for (auto p : list)
	{
		if (p->x == point->x&&p->y == point->y)
			return p;
		return NULL;
	}
}
bool Astar::ifAbleReach(const Apoint *point, const Apoint *target, bool ifIgnoreCorner)const
{
	if (target->x<0 || target->x>width - 1
		|| target->y<0 || target->y>height - 1//超出地图
		|| maze[width*target->y + target->x] == false//是障碍物
		|| (target->x == point->x&&target->y == point->y)//与当前节点重合
		|| ifInList(closeList, target))//在关闭列表中
		return false;
	else
	{
		//斜对角要判断是否绊住  
		if (maze[width*target->y + point->x] == true
			&& maze[width*point->y + target->x] == true)
			return true;
		else
			return ifIgnoreCorner;
	}
}
vector<Apoint*> Astar::getSurroundingPoints(const Apoint *point, bool ifIgnoreCorner) const
{
	vector<Apoint*> surroundingPoints;
	for (int x = point->x - 1; x <= point->x + 1; x++)
	{
		for (int y = point->y - 1; y <= point->y + 1; y++)
			if (ifAbleReach(point, new Apoint(x, y), ifIgnoreCorner))
				surroundingPoints.push_back(new Apoint(x, y)); 

	}
	return surroundingPoints;
}

