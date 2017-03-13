#include "bavo.h"

bavo::bavo() 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	vitriy = 400;
	//bavo_1= Sprite::createWithSpriteFrameName("1.png");
	bavo_1 = Sprite::create("bavo/1.png");
	//bavo_1->setAnchorPoint(Vec2(0,0));
	bavo_1->setPosition(200, vitriy);
	bavo_1->setScale(0.4);// thu nho
	capnhatanimate();
	//this->schedule(schedule_selector(bavo::kiemtra), 0.5);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(bavo::kiemtra), this, 0.5f, false);

}
void bavo::diphai() {
	if (dunggame1 == false) {
		 phai = true;
		 capnhatanimate();
		 bavo_1->stopAllActions();
		 auto di = MoveBy::create(0.4, Vec2(30, 0));
		 auto dichuyen = Spawn::createWithTwoActions(animate, di);
		 bavo_1->runAction(RepeatForever::create(dichuyen));
	}
}

void bavo::ditrai() {
	if (dunggame1 == false) {
		phai = false;
		capnhatanimate();
		auto di = MoveBy::create(0.4, Vec2(-30, 0));
		auto dichuyen = Spawn::createWithTwoActions(animate_trai, di);
		bavo_1->stopAllActions();
		bavo_1->runAction(RepeatForever::create(dichuyen));
	}
		
}
void bavo::nem() {
	capnhatanimate();
	vitri = bavo_1->getPosition();
	bool b=phai;
	bavo_1->stopAllActions();
	auto di = CallFunc::create([&,b]()
	{
		b == true ? diphai() : ditrai();
		
	});
	auto nemxongdi = Sequence::create(phai==true?animate_nem:animate_nemtrai, di, nullptr);
	bavo_1->runAction(nemxongdi);
}
void bavo::kiemtra(float dt) {
	if (dunggame1 == false) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		if (bavo_1->getPositionX() <= 0 + 70 /*+ bavo_1->getContentSize().width/2*/) {
			//nem();
			diphai();
		}
		if (bavo_1->getPositionX() >= visibleSize.width - 70 /*+ bavo_1->getContentSize().width/2*/) {
			//nem();
			ditrai();
		}
	}	
	
}


bavo::~bavo()
{
}

void bavo::capnhatanimate() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bavo/bavodi.plist", "bavo/bavodi.png");

	const int numberSprite = 3;
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(numberSprite);

	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	//
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bavo/ditrai.plist", "bavo/ditrai.png");
	Vector<SpriteFrame*> animFramestrai;
	animFramestrai.reserve(numberSprite);

	animFramestrai.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("trai0.png"));
	animFramestrai.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("trai1.png"));
	animFramestrai.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("trai2.png"));

	Animation* animationtrai = Animation::createWithSpriteFrames(animFramestrai, 0.2f);
	animate_trai = Animate::create(animationtrai);

	//animate nem
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bavo/nem.plist", "bavo/nem.png");
	Vector<SpriteFrame*> animFramesnem;
	animFramesnem.reserve(2);
	animFramesnem.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("nem1.png"));
	animFramesnem.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("nem2.png"));

	Animation* animationnem = Animation::createWithSpriteFrames(animFramesnem, 0.2f);
	animate_nem = Animate::create(animationnem);

	//
	//
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bavo/nemtrai.plist", "bavo/nemtrai.png");
	Vector<SpriteFrame*> animFramesnemtrai;
	animFramesnemtrai.reserve(2);
	animFramesnemtrai.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("nemtrai1.png"));
	animFramesnemtrai.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("nemtrai2.png"));

	Animation* animationnemtrai = Animation::createWithSpriteFrames(animFramesnemtrai, 0.2f);
	animate_nemtrai = Animate::create(animationnemtrai);
}
void bavo::dunggame() {
	bavo_1->stopAllActions();
	dunggame1 = true;
}
void bavo::tieptucgame() {
	dunggame1 = false;
}