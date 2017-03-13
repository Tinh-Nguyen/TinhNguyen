#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "bavo.h"
#include"MenuGameScene.h"


USING_NS_CC;
bool nhacnen11;
bool nhachieuung11;
Scene* GamePlay::createScene(bool nhacnen1,bool nhachieuung1)
{
	nhacnen11 = nhacnen1;
	nhachieuung11 = nhachieuung1;
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();	
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	const char *nen = "nhacnen";
	const char *hieuung = "nhachieuung";
	auto def = UserDefault::sharedUserDefault();
	bool nhacnen111 = def->getBoolForKey(nen);
	bool nhachieuung111 = def->getBoolForKey(hieuung);

	audio->playBackgroundMusic("amthanh/nhacnen12.wav",true);
	nhacnen = nhacnen111;
	nhachieuung = nhachieuung111;
	capnhatnhac();

	//
	chieucaobia = aa.chaibia->getContentSize().height / 2;

	Vec2 vtloa = Vec2(700, 460);
	Vec2 vtpause = Vec2(670, 460);
	Vec2 vttim = Vec2(620,460);
	Vec2 vtchumang = Vec2(640, 465);
	Vec2 vtchuscore = Vec2(580,440);
	Vec2 vtchudiem = Vec2(680,440);
	//them anh tri tim
	auto tim = Sprite::create("anh/tim.png");
	tim->setPosition(vttim);
	//
	//
	auto loa = ui::CheckBox::create("anh/loatat1.png", "anh/loamo1.png");
	loa->setPosition(vtloa);
	if (nhacnen == false && nhachieuung == false) {
		loa->setSelected(false);
	}
	else
		loa->setSelected(true);
	loa->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
	{
		switch (type)
		{
		case ui::CheckBox::EventType::SELECTED:
			if(nhacnen11)
				nhacnen = true;
			if(nhachieuung11)
				nhachieuung = true;
			if (nhacnen11 == false && nhachieuung11 == false) {
				nhacnen = true;
				nhachieuung = true;
			}
			capnhatnhac();
			break;
		case ui::CheckBox::EventType::UNSELECTED:
			nhacnen = false;
			nhachieuung = false;
			capnhatnhac();
			break;
		default:
			break;
		}
	});
	auto bg = Sprite::create("anh/background.jpg");
	bg->setAnchorPoint(Vec2(0.5,0.5));
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bg);
	addChild(tim);
	addChild(loa);

	//

	//
	//
	//
	auto nutpause = MenuItemImage::create("anh/pause.png", "anh/pause1.png", CC_CALLBACK_1(GamePlay::nhanpause, this));
	nutpause->setPosition(vtpause);
	
	menu1 = Menu::create(nutpause, NULL);
	
	menu1->setPosition(0, 0);
	addChild(menu1);
	//

	
	//
	auto chudiem1 = Label::createWithTTF("score: ", "fonts/Neverwinter.ttf", 40);
	chudiem1->setAnchorPoint(ccp(0, 0.5f));
	chudiem1->setPosition(vtchuscore);

	chudiem = Label::createWithTTF("", "fonts/Neverwinter.ttf", 40);
	chudiem->setAnchorPoint(ccp(0, 0.5f));
	chudiem->setPosition(vtchudiem);
	//chuye kieu du lieu
	__String *diem1 = __String::createWithFormat("%i", diem);
	chudiem->setString(diem1->getCString());
	// chu mang
	chumang = Label::createWithTTF("", "fonts/Neverwinter.ttf", 40);
	chumang->setPosition(vtchumang);
	//
	__String *mang1 = __String::createWithFormat("%i", mang);
	chumang->setString(mang1->getCString());
	//
	addChild(chumang);
	this->addChild(chudiem);
	this->addChild(chudiem1);
	

	//auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,1.0f);
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,2.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)	);
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	edgeNode->setPhysicsBody(edgeBody);
	addChild(edgeNode);
	/*	edgeBody->setDynamic(false)*/;
	//edgeBody->setCollisionBitmask(1);
	//edgeBody->setContactTestBitmask(true);
	//auto khung = Sprite::create();
	//khung->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	//khung->setPhysicsBody(edgeBody);
	//addChild(khung);

	//
	auto contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(GamePlay::onPhysicsContact, this);



	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//ba vo
	addChild(a.bavo_1);
	tudongnem(1);
	//ongchong
	addChild(chong.nguoi);
	addChild(chong.ro);

	//auto mouseListener = EventListenerMouse::create();

	//mouseListener->onMouseMove = CC_CALLBACK_1(GamePlay::onMouseMove, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	///
	//

	//
	auto lancan = Sprite::create("anh/lancan.png");
	lancan->setAnchorPoint(Vec2(0, 0));
	lancan->setPosition(Vec2(0,315));
	addChild(lancan);
	//
	//
	//su kien touch
	auto listener1 = EventListenerTouchOneByOne::create();

	// trigger when you push down
	listener1->onTouchBegan = listener1->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);

	// trigger when moving touch
	listener1->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    return true;
}



//void GamePlay::onMouseMove(Event* event) {
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	EventMouse* e = (EventMouse*)event;
//	Vec2 vt = Vec2(e->getCursorX(), e->getCursorY());
//
//	if (vt.y >= chong.ro->getContentSize().height + 10 || vt.y <= chong.ro->getContentSize().height) {
//		chong.setvitri(Vec2(vt.x,chong.vitriro.y));
//	}
//	else
//		chong.setvitri(vt);
//}



void GamePlay::tudongnem(float dt) {
	if (dunggame == false) {
		this->schedule(schedule_selector(GamePlay::tudongnem), tgnem);
		srand(time(0));	
		int mucdo1 = 0;
		if (danem <= 50)
			mucdo1 = (danem / 10)*4;
		tgnem = random(5,30-mucdo1)*0.1;
		int randhuong = rand() % 2;
		(randhuong == 0) ? a.ditrai() : a.diphai();
		a.nem();
		if(nhachieuung==true)
			audio->playEffect("amthanh/nemchai.mp3", false, 1.0f, 1.0f, 1.0f);

		this->scheduleOnce(schedule_selector(GamePlay::taochaibia), 0.4);
	}
	
	
}

//xu li va cham
bool GamePlay::onPhysicsContact(const PhysicsContact &contact)
{
	// va cham voi duong duoi
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();
	if (shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2)
	{
		if (shapeB->getPosition().y <= chieucaobia / 2)
		{
			if (shapeB->getNode() != NULL) {
						shapeB->getNode()->removeFromParentAndCleanup(true);
				if(nhachieuung==true)
					audio->playEffect("amthanh/chaibe.mp3", false, 1.0f, 1.0f, 1.0f);
				mang--;
				if (dunggame == true) mang++;
				__String *mang1 = __String::createWithFormat("%i", mang);
				chumang->setString(mang1->getCString());
				if (mang == 0)
				{
					if(dunggame==false)
						gameover();
				}
			}
		}
	}
	else
	if (shapeA->getCollisionBitmask() == 2 && shapeB->getCollisionBitmask() == 1)
	{
		if (shapeA->getPosition().y <=chieucaobia/2)
			if (shapeA->getNode() != NULL) {
				if(nhachieuung==true)
					audio->playEffect("amthanh/chaibe.mp3", false, 1.0f, 1.0f, 1.0f);
				shapeA->getNode()->removeFromParentAndCleanup(true);
				mang--;
				if (dunggame == true) mang++;
				__String *mang1 = __String::createWithFormat("%i", mang);
				chumang->setString(mang1->getCString());
				if (mang == 0)
				{	
					if (dunggame == false)
						gameover();
				}
			}	
	}
	//
	//va cham bia vo ro
	if (shapeA->getCollisionBitmask() == 2 && shapeB->getCollisionBitmask() == 3)
	{
		if(nhachieuung==true)
			audio->playEffect("amthanh/bialot.mp3", false, 1.0f, 1.0f, 1.0f);
		chong.chamro();
		if(dunggame==false)
			diem++;
		// 
		__String *diem1 = __String::createWithFormat("%i", diem);
		chudiem->setString(diem1->getCString());
		//
		if (shapeA->getNode() != NULL)
			shapeA->getNode()->removeFromParentAndCleanup(true);
	}
	if (shapeA->getCollisionBitmask() == 3 && shapeB->getCollisionBitmask() == 2)
	{
		if(nhachieuung==true)
			audio->playEffect("amthanh/bialot.mp3", false, 1.0f, 1.0f, 1.0f);
		chong.chamro();
		if (dunggame == false)
			diem++;
		//
		__String *diem1 = __String::createWithFormat("%i", diem);
		chudiem->setString(diem1->getCString());
		//
		if (shapeB->getNode() != NULL)
				shapeB->getNode()->removeFromParentAndCleanup(true);
	}
	return true;

}
void GamePlay::taochaibia(float dt)
{
	bia b;
	if (danem <= 50) {	
		danem += 1;
	}
	b.setmucdo(b.mucdo += danem / 5);	

	addChild(b.chaibia);
	(a.phai == true) ? (b.vitri.x = a.vitri.x + 30) : (b.vitri.x = a.vitri.x - 30);
	b.vitri.y = a.vitri.y - 30;
	b.setvitri(b.vitri);
	sobianem++;
	if (sobianem == 10)
		sobianem = 0;
}
void GamePlay::stopgame() {
	dunggame = true;
	a.dunggame();

		
}
void GamePlay::gameover() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	bool kt=kiemtraluudiem();
	if (kt) {

	}
	stopgame();
	layout = ui::Layout::create();
	layout->setTag(10);
	layout->setBackGroundImage("anh/backgroundgameover.png");
	layout->setBackGroundImageOpacity(100);
//	layout->setAnchorPoint(Vec2(0.5, 0.5));
	layout->setContentSize(visibleSize);
	//layout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(layout,100);
	auto abc = Sprite::create("anh/nengameover.png");
	abc->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	layout->addChild(abc);
	auto nuthome = MenuItemImage::create("anh/menu.png", "anh/menu1.png", CC_CALLBACK_1(GamePlay::nhanmenu, this));
	nuthome->setPosition(Vec2(-35, -110));
	auto nutreplay = MenuItemImage::create("anh/replay.png", "anh/replay1.png", CC_CALLBACK_1(GamePlay::nhanreplay, this));
	nutreplay->setPosition(Vec2(35, -110));
	// tao menu
	auto menu = Menu::create(nuthome, nutreplay, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	layout->addChild(menu);

	auto chudiem1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 30);
	chudiem1->setAnchorPoint(Vec2(0.0f, 0.5f));
	chudiem1->setTextColor(Color4B::ORANGE);
	chudiem1->setPosition(Point(visibleSize.width /2+10, visibleSize.height /2-70));
	__String *diem11 = __String::createWithFormat("%i", diem);
	chudiem1->setString(diem11->getCString());
	layout->addChild(chudiem1);
}
void GamePlay::continuegame() {
	dunggame = false;
	a.tieptucgame();
}
void GamePlay::capnhatnhac() {
	nhacnen = true;
	if (nhacnen == true) {
		audio->resumeBackgroundMusic();
	}
	if (nhacnen == false) {
		audio->pauseBackgroundMusic();
	}
}
void GamePlay::nhanmenu(Ref* pSender) {
	removeChildByTag(10, true);
	auto scene = MenuGame::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, scene));
	nhacnen = false;
	capnhatnhac();
		
}
void GamePlay::nhanreplay(Ref* pSender) {
	
	//layout->removeFromParent();
	removeChildByTag(10, true);
	danem = 0;
	a.bavo_1->setPosition(200,400);
	diem = 0;
	mang = 5;
	__String *diem1 = __String::createWithFormat("%i", diem);
	chudiem->setString(diem1->getCString());
	__String *mang1 = __String::createWithFormat("%i", mang);
	chumang->setString(mang1->getCString());
	continuegame();
}
void GamePlay::nhanpause(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (dunggame == false) {
		auto nutplay = MenuItemImage::create("anh/playgame.png", "anh/playgame1.png", CC_CALLBACK_1(GamePlay::nhanplay, this));
		nutplay->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		nutplay->setTag(5);
		menu1->addChild(nutplay);
	}
	stopgame();
	
}
void GamePlay::nhanplay(Ref* pSender) {
	continuegame();
	menu1->removeChildByTag(5);
}
bool GamePlay::kiemtraluudiem() {
	const char *HIGH_SCORE = "diem";
	auto def = UserDefault::sharedUserDefault();
	int diemcu = def->getIntegerForKey(HIGH_SCORE);
	if (diemcu < diem) {
		def->setIntegerForKey(HIGH_SCORE, diem);
		def->flush();
		return true;
	}
	return false;
	
}
void GamePlay::onTouchMoved(Touch* touch, Event* event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 vt = touch->getLocation();

	if (vt.y >= chong.ro->getContentSize().height + 10 || vt.y <= chong.ro->getContentSize().height) {
		chong.setvitri(Vec2(vt.x,chong.vitriro.y));
	}
	else
			chong.setvitri(vt);
}
bool GamePlay::onTouchBegan(Touch* touch, Event* event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 vt = touch->getLocation();

	if (vt.y >= chong.ro->getContentSize().height + 10 || vt.y <= chong.ro->getContentSize().height) {
		chong.setvitri(Vec2(vt.x, chong.vitriro.y));
	}
	else
		chong.setvitri(vt);
	return true;
}