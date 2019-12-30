#include"Astar.h"

Apoint::Apoint()
{
	this->x = 0;
	this->y = 0;
	this->F = 0;
	this->G = 0;
	this->H = 0;
	this->parent = nullptr;
	this->flag = ABLE;
}
Apoint::Apoint(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
	this->F = 0;
	this->G = 0;
	this->H = 0;
	this->parent = nullptr;
	this->flag = ABLE;
}
void Apoint::setParentPoint(Apoint *parentpoint)
{
	this->parent = parentpoint;
}
Apoint * Apoint::getParentPoint()
{
	return parent;
}



Astar::Astar(int _width, int _height, Apoint start, Apoint end)
{
	width = _width;
	height = _height;
	TMXLayer *collidable = GameScene::gettiledMap()->getLayer("CollidableLayer");
	/*if (collidable == nullptr)
	{
		log("++++++++++++++");
	}*/
	vector<Apoint> row(width, Apoint());
	map_point.assign(height, row);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			map_point[i][j].setX(i);
			map_point[i][j].setY(j);
			int tileGid = collidable->getTileGIDAt(Vec2(i, j));
			if (tileGid > 0)
			{
				ValueMap propValueMap = (GameScene::gettiledMap()->getPropertiesForGID(tileGid)).asValueMap();
				if (propValueMap["Collidable"].asString() == "true")
				{
					map_point[i][j].setFlag(UNABLE);
				}
			}
			else
			{
				map_point[i][j].setFlag(ABLE);
			}
		}
	}
	map_point[start.getX()][start.getY()].setFlag(START);
	if (map_point[end.getX()][end.getY()].getFlag() == UNABLE)
	{
		flag = false;
	}
	map_point[end.getX()][end.getY()].setFlag(END);
	start_point = &map_point[start.getX()][start.getY()];
	end_point = &map_point[end.getX()][end.getY()];
}
Apoint * Astar::nextPointByLeastF()
{
	if (!openlist.empty())
	{
		auto nextPoint = openlist[0];
		for (auto point : openlist)
		{
			if (point->getF() < nextPoint->getF())
			{
				nextPoint = point;
			}
		}
		return nextPoint;
	}
	return NULL;
}
bool Astar::ifInOpenList(Apoint &nextPoint)
{
	if (nextPoint.getFlag() == INOPENLIST)
	{
		return true;
	}
	return false;
}
bool Astar::ifInCloseList(Apoint &nextPoint)
{
	if (nextPoint.getFlag() == INCLOSELIST || nextPoint.getFlag() == START)
	{
		return true;
	}
	return false;
}
int Astar::calculateG(Apoint &currentPoint, Apoint &lastPoint)
{
	/*if (currentPoint.getX() == lastPoint.getX() || currentPoint.getY() == lastPoint.getY())
	{
		return lastPoint.getG() + 10;
	}*/
	return lastPoint.getG() + 10;
}
int Astar::calculateH(Apoint &currentPoint, Apoint &endPoint)
{
	return (abs(currentPoint.getX() - endPoint.getX()) + abs(currentPoint.getY() - endPoint.getY())) * 10;
}
int Astar::calculateF(Apoint &point)
{
	return (point.getG() + point.getH());
}
bool Astar::ifAbleReach(Apoint &nextPoint, Apoint &currentPoint)
{
	if (ifInCloseList(nextPoint))
	{
		return false;
	}
	if (nextPoint.getX() == currentPoint.getX() && nextPoint.getY() == currentPoint.getY())
	{
		return false;
	}
	if (nextPoint.getX() != currentPoint.getX() && nextPoint.getY() != currentPoint.getY())
	{
		return false;
	}
	if (nextPoint.getFlag() == UNABLE)
	{
		return false;
	}
	return true;
}
void Astar::getSurroundingPoints(Apoint &currentPoint)
{
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int next_x = currentPoint.getX() + i;
			int next_y = currentPoint.getY() + j;
			if (next_x >= 0 && next_x < width && next_y >= 0 && next_y < height 
				&& ifAbleReach(map_point[next_x][next_y], currentPoint))
			{
				if (ifInOpenList(map_point[next_x][next_y]))
				{
					if (map_point[next_x][next_y].getG() > calculateG(map_point[next_x][next_y], currentPoint))
					{
						map_point[next_x][next_y].setG(calculateG(map_point[next_x][next_y], currentPoint));
						map_point[next_x][next_y].setH(calculateH(map_point[next_x][next_y], *end_point));
						map_point[next_x][next_y].setF(calculateF(map_point[next_x][next_y]));
						map_point[next_x][next_y].setParentPoint(&currentPoint);
					}
				}
				else
				{
					map_point[next_x][next_y].setG(calculateG(map_point[next_x][next_y], currentPoint));
					map_point[next_x][next_y].setH(calculateH(map_point[next_x][next_y], *end_point));
					map_point[next_x][next_y].setF(calculateF(map_point[next_x][next_y]));
					map_point[next_x][next_y].setFlag(INOPENLIST);
					map_point[next_x][next_y].setParentPoint(&currentPoint);
					openlist.push_back(&map_point[next_x][next_y]);
				}
			}
		}
	}
}
void Astar::findPath()
{
	openlist.clear();
	closelist.clear();
	Apoint *point = nullptr;
	openlist.push_back(start_point);
	if (!flag)
	{
		return;
	}
	while (end_point->getFlag() == END && !openlist.empty())
	{
		point = nextPointByLeastF();
		getSurroundingPoints(*point);
		point->setFlag(INCLOSELIST);
		closelist.push_back(point);
		vector<Apoint *>::iterator it = find(openlist.begin(), openlist.end(), point);
		if (it != openlist.end())
		{
			openlist.erase(it);
		}
	}
}
vector<Apoint> Astar::getPath()
{
	vector<Apoint> path;
	Apoint *point = end_point;
	while (point->getParentPoint() != nullptr)
	{
		path.push_back(Apoint(point->getX(), point->getY()));
		point = point->getParentPoint();
	}
	return path;
}