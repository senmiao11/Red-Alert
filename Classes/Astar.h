#ifndef __ASTAR_H_
#define __ASTAR_H_
#include<iostream>
#include<vector>
#include"cocos2d.h"
#include"GameScene.h"

USING_NS_CC;
using namespace std;

typedef enum
{
	INOPENLIST,
	INCLOSELIST,
	ABLE,
	UNABLE,
	START,
	END,
	OCCUPATION
}flagType;

class Apoint
{
private:
	Apoint *parent;

public:
	Apoint();
	Apoint(int _x, int _y);
	CC_SYNTHESIZE(int, x, X);
	CC_SYNTHESIZE(int, y, Y);
	CC_SYNTHESIZE(int, F, F);
	CC_SYNTHESIZE(int, G, G);
	CC_SYNTHESIZE(int, H, H);
	CC_SYNTHESIZE(flagType, flag, Flag);
	void setParentPoint(Apoint *parentpoint);
	Apoint *getParentPoint();
};


class Astar
{
	friend class GameScene;
public:

	Astar(int _width, int _height, Apoint start, Apoint end);
	void findPath();
	vector<Apoint> getPath();


private:

	vector<Apoint *> openlist;
	vector<Apoint *> closelist;
	vector<vector<Apoint> > map_point;
	Apoint *start_point;
	Apoint *end_point;
	int width;
	int height;


	Apoint *nextPointByLeastF();
	bool ifInOpenList(Apoint &nextPoint);
	bool ifInCloseList(Apoint &nextPoint);
	int calculateG(Apoint &currentPoint, Apoint &lastPoint);
	int calculateH(Apoint &currentPoint, Apoint &end);
	int calculateF(Apoint &point);
	bool ifAbleReach(Apoint &nextPoint, Apoint &currentPoint);
	void getSurroundingPoints(Apoint &currentPoint);

public:

};

#endif // !__ASTAR_H_
