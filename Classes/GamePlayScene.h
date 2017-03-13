#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__
#include "bavo.h"
#include "cocos2d.h"
#include "bia.h"
#include "ongchong.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "ui\CocosGUI.h"

class GamePlay : public cocos2d::Layer
{
private:
	PhysicsWorld *world;
	void setPhysicsWorld(PhysicsWorld *mworld) {
		world = mworld; 
	}
public:
	static cocos2d::Scene* createScene(bool nhacnen1, bool nhachieuung1);
	CocosDenshion::SimpleAudioEngine* audio= CocosDenshion::SimpleAudioEngine::getInstance();
	bool nhacnen = true;
	bool nhachieuung=true;
	bool dunggame=false;
	int diem=0;
	int tg;
	int danem = 0;
	int mang = 5;
	int sobianem=0;

	Label* chudiem;
	Label* chumang;
	bool loadangmo = true;
	Sprite* loamo;
	Sprite* loatat;
	bia aa;
	ongchong chong;
	float chieucaobia;
	void taochaibia(float dt);
	bool onPhysicsContact(const PhysicsContact &contact);
	float tgnem=1;
	bavo a;
	ui::Layout* layout;
	Menu* menu1;
    virtual bool init();
	//void onMouseMove(Event* event);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void stopgame();
	void gameover();
	void continuegame();
	void capnhatnhac();
	void tudongnem(float dt);
	void nhanmenu(Ref* pSender);
	void nhanreplay(Ref* pSender);
	void nhanpause(Ref* pSender);
	void nhanplay(Ref* pSender);
	bool kiemtraluudiem();
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlay);
};

#endif // __GAMEPLAY_SCENE_H__
