#pragma once
#include "cocos2d.h"
USING_NS_CC;
class bavo : public cocos2d::Layer
{

public:
	Vec2 vitri;
	bool dunggame1 = false;
	bool phai = true;
	Animate* animate;
	Animate* animate_nem;
	Animate* animate_trai;
	Animate* animate_nemtrai;
	Sprite* bavo_1;
	int vitriy;
	bavo();
	~bavo();
	void diphai();
	void ditrai();
	void nem();
	void capnhatanimate();
	void kiemtra(float dt);
	void dunggame();
	void tieptucgame();

};

