
#include"toast.h"
//Add toast
void toast::addtoast(Node* node, Point p, std::string s, float time)
{
	auto pLabel = Label::createWithSystemFont(s.c_str(), "Arial", 20);
	pLabel->setColor(Color3B::WHITE);
	pLabel->ignoreAnchorPointForPosition(false);
	pLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto ly = LayerColor::create(Color4B(130, 120, 120, 255));
	ly->ignoreAnchorPointForPosition(false);
	ly->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ly->setContentSize(pLabel->getContentSize() + Size(20, 15));
	node->addChild(ly);
	node->addChild(pLabel);
	ly->setPosition(p);
	pLabel->setPosition(ly->getPosition());
	auto seq1 = Sequence::create(FadeIn::create(time / 5), DelayTime::create(time / 5 * 1.5), FadeOut::create(time / 5 * 2.5), CallFuncN::create(ly, callfuncN_selector(toast::removetoast)), nullptr);
	auto seq2 = Sequence::create(EaseSineIn::create(MoveBy::create(time / 5, Vec2(0, 50))), DelayTime::create(time / 5 * 2), EaseSineOut::create(MoveBy::create(time / 3, Vec2(0, -50))), nullptr);
	auto spawn = Spawn::create(seq1, seq2, nullptr);
	auto action = Repeat::create(spawn, 1);
	ly->setOpacity(0);
	pLabel->setOpacity(0);
	ly->runAction(action);
	pLabel->runAction(action->clone());
}

//Remove the toast
void toast::removetoast(Node* node)
{
	this->removeFromParentAndCleanup(true);
}