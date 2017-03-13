#pragma once
#include "cocos2d.h"
USING_NS_CC;

class bia
{
public:
	int mucdo = 2;
	bia();
	~bia();
	Sprite* chaibia;
	Vec2 vitri;
	PhysicsBody* bodybia;
	void setvitri(Vec2 vt);
	bool dichuyen = false;
	void setmucdo(int md);

};

