#include "ongchong.h"



ongchong::ongchong()
{
	vitriro = Vec2(200,65);
	nguoi = Sprite::create("anh/chong.png");
	nguoi->setScale(0.7);
	ro = Sprite::create("anh/ro.png");
	ro->setScale(0.7);
	nguoi->setPosition(vitriro.x+45,vitriro.y+8);
	ro->setPosition(vitriro);//30 5
	//vat li ro
	auto bodyro = PhysicsBody::createBox(Size(ro->getContentSize().width-15, ro->getContentSize().height-20),PhysicsMaterial(0,0,0));
	bodyro->setGravityEnable(false);
	bodyro->setDynamic(false);
	bodyro->setCollisionBitmask(3);
	bodyro->setContactTestBitmask(true);

	ro->setPhysicsBody(bodyro);
	//
}
void ongchong::chamro() {
	auto scale = ScaleTo::create(0.2f, 0.9f, 0.6f);
	auto scale0 = ScaleTo::create(0.0f, 0.7f, 0.7f);
	auto sequence = Sequence::create(scale,scale0, nullptr);
	ro->runAction(sequence);
}


ongchong::~ongchong()
{
}
void ongchong::setvitri(Vec2 vt) {
	vitriro = vt;
	nguoi->setPosition(vitriro.x + 45, vitriro.y + 8);
	ro->setPosition(vitriro);
}
