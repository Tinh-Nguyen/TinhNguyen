#include "MenuGameScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
USING_NS_CC;


Scene* MenuGame::createScene()
{
	
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	
	auto menuBG = Sprite::create("anh1/bg.jpg");
	menuBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(menuBG);

	auto menuItem_1 = MenuItemImage::create("anh1/play.png","anh1/play1.png", CC_CALLBACK_1(MenuGame::Play, this));
	menuItem_1->setScale(0.3, 0.3); 
	menuItem_1->setPosition(-5, 10);
	auto menuItem_2 = MenuItemImage::create("anh1/highscore.png","anh1/highscore1.png", CC_CALLBACK_1(MenuGame::HighScores, this));
	menuItem_2->setScale(0.2, 0.2);
	menuItem_2->setPosition(Vec2(-60, -70));
	auto menuItem_3 = MenuItemImage::create("anh1/options.png","anh1/options1.png", CC_CALLBACK_1(MenuGame::Options, this));
	menuItem_3->setScale(0.2, 0.2);
	menuItem_3->setPosition(Vec2(-10, -70));
	auto menuItem_4 = MenuItemImage::create("anh1/about0.png", "anh1/about11.png", CC_CALLBACK_1(MenuGame::About, this));
	menuItem_4->setScale(0.2, 0.2);
	menuItem_4->setPosition(Vec2(40, -70));
	auto menu = Menu::create( menuItem_1,menuItem_2, menuItem_3,menuItem_4,NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.5));
	this->addChild(menu);

	return true;
}
void MenuGame::Play(cocos2d::Ref* pSender) {
	if (manhinhmo == false) {
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("amthanh/bottle-open-1.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("amthanh/bottle-open-1.mp3", false, 1.0f, 1.0f, 1.0f);
		auto scene = GamePlay::createScene(nhacnen, nhachieung);
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, scene));
	}
	
}

void MenuGame::About(cocos2d::Ref* pSender) {
	if (manhinhmo == false) {
		manhinhmo = true;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto layout = ui::Layout::create();
		layout->setName("menu");
		layout->setLayoutType(Layout::Type::HORIZONTAL);
		layout->setContentSize(Size(280, 150));
		layout->setBackGroundImageOpacity(100);
		layout->setAnchorPoint(Vec2(0.5, 0.5));
		layout->setContentSize(visibleSize);
		layout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(layout);
		auto abc = Sprite::create("anh1/anhabout.png");
		abc->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(abc);
		auto nutrback = MenuItemImage::create("anh1/back.png", "anh1/back1.png", CC_CALLBACK_1(MenuGame::Back, this));
		nutrback->setScale(0.1, 0.1);
		nutrback->setPosition(-70, -125);
		// tao menu
		auto menu = Menu::create(nutrback, NULL);
		menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(menu);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("amthanh/bottle-open-1.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("amthanh/bottle-open-1.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	

}
void MenuGame::HighScores(cocos2d::Ref* pSender) {
	if (manhinhmo == false) {
		manhinhmo = true;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto layout = ui::Layout::create();
		layout->setName("menu");
		layout->setBackGroundImageOpacity(100);
		layout->setAnchorPoint(Vec2(0.5, 0.5));
		layout->setContentSize(visibleSize);
		layout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(layout);
		auto abc = Sprite::create("anh1/anhscoes.png");
		abc->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(abc);
		auto nutrback = MenuItemImage::create("anh1/back.png", "anh1/back1.png", CC_CALLBACK_1(MenuGame::Back, this));
		nutrback->setScale(0.1, 0.1);
		nutrback->setPosition(-70, -125);
		auto nutreset = MenuItemImage::create("anh1/reset.png", "anh1/reset1.png", CC_CALLBACK_1(MenuGame::reset, this));
		nutreset->setPosition(0, -110);
		// tao menu
		auto menu = Menu::create(nutrback,nutreset, NULL);
		menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(menu);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("amthanh/bottle-open-1.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("amthanh/bottle-open-1.mp3", false, 1.0f, 1.0f, 1.0f);
		//diem cao
		const char *HIGH_SCORE = "diem";
		auto def = UserDefault::sharedUserDefault();
		int diemcao = def->getIntegerForKey(HIGH_SCORE);
		auto diemcao1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 30);
		diemcao1->setAnchorPoint(Vec2(0.0f, 0.5f));
		diemcao1->setTextColor(Color4B::ORANGE);
		diemcao1->setPosition(Point(visibleSize.width / 2 -15, visibleSize.height / 2 - 40));
		__String *diem11 = __String::createWithFormat("%i", diemcao);
		diemcao1->setString(diem11->getCString());
		layout->addChild(diemcao1);
	}

}

void MenuGame::Options(cocos2d::Ref* pSender) {

	if (manhinhmo == false) {

		const char *nen = "nhacnen";
		const char *hieuung = "nhachieuung";
		const char *molansau = "lansau";
		auto def = UserDefault::sharedUserDefault();
		bool nhacnen11 = def->getBoolForKey(nen);
		bool nhachieuung11 = def->getBoolForKey(hieuung);

		bool lansau = def->getBoolForKey(molansau);
		if (lansau != true) {
			nhacnen11 = true;
			nhachieuung11 = true;
			def->setBoolForKey(molansau, true);
			def->flush();
			luunhacnen(true);
			luunhachieuung(true);
		}
		nhacnen = nhacnen11;
		nhachieung = nhachieuung11;

		manhinhmo = true;
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto layout = ui::Layout::create();
		layout->setName("menu");
		layout->setBackGroundImageOpacity(100);
		//layout->setAnchorPoint(Vec2(0.5, 0.5));
		layout->setContentSize(visibleSize);
		//layout->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(layout);
		auto abc = Sprite::create("anh1/anhnen.png");
		abc->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(abc);
		auto checkbox_1 = ui::CheckBox::create("anh1/uncheck.png", "anh1/checked.png");
		checkbox_1->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 75));
		if(nhacnen)
			checkbox_1->setSelected(true);
		//su kien checkbox
		checkbox_1->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
		{
			switch (type)
			{
			case ui::CheckBox::EventType::SELECTED:
				nhacnen = true;
				luunhacnen(nhacnen);
				break;
			case ui::CheckBox::EventType::UNSELECTED:
					nhacnen = false;
					luunhacnen(nhacnen);
				break;
			default:
				break;
			}
		});
		auto checkbox_2 = ui::CheckBox::create("anh1/uncheck.png", "anh1/checked.png");
		checkbox_2->setPosition(Vec2(visibleSize.width / 2 + 30, visibleSize.height / 2 + 40));
		if(nhachieung)
			checkbox_2->setSelected(true);
		checkbox_2->addEventListener([&](Ref* sender, ui::CheckBox::EventType type)
		{
			switch (type)
			{
			case ui::CheckBox::EventType::SELECTED:
				nhachieung = true;
				luunhachieuung(nhachieung);
				break;
			case ui::CheckBox::EventType::UNSELECTED:
				nhachieung = false;
				luunhachieuung(nhachieung);
				break;
			default:
				break;
			}
		});
		layout->addChild(checkbox_1);
		layout->addChild(checkbox_2);
		auto nutrback = MenuItemImage::create("anh1/back.png", "anh1/back1.png", CC_CALLBACK_1(MenuGame::Back, this));
		nutrback->setScale(0.1, 0.1);
		nutrback->setPosition(-70, -125);
		// tao menu
		auto menu = Menu::create(nutrback, NULL);
		menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		layout->addChild(menu);

		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("amnthanh/bottle-open-1.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("amthanh/bottle-open-1.mp3", false, 1.0f, 1.0f, 1.0f);
	}
}
void MenuGame::Back(cocos2d::Ref* pSender) {
	this->removeChildByName("menu");
	manhinhmo = false;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("amthanh/bottle-open-1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("amthanh/bottle-open-1.mp3", false, 1.0f, 1.0f, 1.0f);
}

void MenuGame::luunhacnen(bool nhacnen1) {
	const char *nen = "nhacnen";
	auto def = UserDefault::sharedUserDefault();
		def->setBoolForKey(nen, nhacnen1);
		def->flush();
}
void MenuGame::luunhachieuung(bool nhachieuung1) {
	const char *hieuung = "nhachieuung";
	auto def = UserDefault::sharedUserDefault();
	def->setBoolForKey(hieuung, nhachieuung1);
	def->flush();
}
void MenuGame::reset(cocos2d::Ref* pSender) {
	const char *HIGH_SCORE = "diem";
	auto def = UserDefault::sharedUserDefault();
	def->setIntegerForKey(HIGH_SCORE, 0);
	def->flush();
	manhinhmo = false;
	this->removeChildByName("menu");
	HighScores(pSender);
}