#include"Bar.h"
void Bar::update(float dt)
{
	clear();
	Node *parent = getParent();
	if (parent->getTag() == GameSceneNodeTagBuilding)//建筑物血条
	{
		auto temp = dynamic_cast<Buildings *>(parent);
		auto rate = float(temp->getcurrentHealth()) / float(temp->getMaxHealth());//当前血量和满血之比
		drawRect(Point(0, 0), Point(Length, Height), color);//空白矩形
		drawSolidRect(Point(0, 0), Point(Length * rate, Height), color);//实心血量
	}
	if (parent->getTag() == GameSceneNodeTagSoldier)//兵种血条
	{
		auto temp = dynamic_cast<Soldiers *>(parent);
		auto rate = float(temp->getcurrentHealth()) / float(temp->getMaxHealth());
		drawRect(Point(0, 0), Point(Length, Height), color);
		drawSolidRect(Point(0, 0), Point(Length * rate, Height), color);
	}
}

void Bar::setLength(float length)
{
	Length = length;
}

void Bar::setHeight(float height)
{
	Height = height;
}