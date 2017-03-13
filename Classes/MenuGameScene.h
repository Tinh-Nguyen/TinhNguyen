#ifndef __MenuGame_SCENE_H__
#define __MenuGame_SCENE_H__
#include"GamePlayScene.h"
#include "cocos2d.h"
#include "ui\CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class MenuGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
	bool nhacnen = true;
	bool nhachieung = true;
	bool manhinhmo = false;
	void Play(cocos2d::Ref* pSender);
	void HighScores(cocos2d::Ref* pSender);
	void Options(cocos2d::Ref* pSender);
	void About(cocos2d::Ref* pSender);
	void Back(cocos2d::Ref* pSender);
	void music(cocos2d::Ref* pSender);
	void reset(cocos2d::Ref* pSender);
	void luunhacnen(bool nhacnen1);
	void luunhachieuung(bool nhachieuung1);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuGame);
};

#endif // __HELLOWORLD_SCENE_H__
