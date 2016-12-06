#include "Opportunity.h"
#include<toast.h>
#include<GameSceneScene.h>


std::vector <Forwards*> Forwards::Instances;
std::vector <Delay*> Delay::Instances;
std::vector <Wealth*> Wealth::Instances;

Opportunity::Opportunity()
{
}
Opportunity::~Opportunity()
{
}
Forwards::Forwards()
{
}
Forwards::~Forwards()
{
}
Delay::Delay()
{
}
Delay::~Delay()
{
}
Wealth::Wealth()
{
}
Wealth::~Wealth()
{
}



bool Opportunity::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Causes = "";

	return true;
}
bool Forwards::init()
{
	if (!Opportunity::init())
	{
		return false;
	}
	Steps = 0;
	return true;
}
bool Delay::init()
{
	if (!Opportunity::init())
	{
		return false;
	}
	Rounds = 0;
	Status = 0;
	return true;
}
bool Wealth::init()
{
	if (!Opportunity::init())
	{
		return false;
	}
	Profit = 0;
	return true;
}
//Adds particle system
void Opportunity::addparticle()
{
	auto particle = ParticleSystemQuad::create(PARTICLE_SYSTEM);
	auto batch = ParticleBatchNode::createWithTexture(particle->getTexture());
	batch->addChild(particle);
	GameScene::getmap()->addChild(batch);
	particle->setPosition(Director::getInstance()->getVisibleSize() / 2);
}


Forwards* Forwards::createWithSteps(std::string causes, int steps)
{
	auto temp = create();
	temp->Causes = causes;
	temp->Steps = steps;
	return temp;
}
//Create a Delay object,with Opportunity::causes, rounds, status
Delay* Delay::createWithRoundsAndStatus(std::string causes, int rounds, int status)
{
	auto temp = create();
	temp->Causes = causes;
	temp->Rounds = rounds;
	temp->Status = status;
	return temp;
}
//Creates the Wealth Object
Wealth* Wealth::createWithProfit(std::string causes, int profit)
{
	auto temp = create();
	temp->Causes = causes;
	temp->Profit = profit;
	return temp;
}





//Returns a layer showing the event
Layer*Opportunity::getShowOnScreen()
{

	auto VisibleSize = Director::getInstance()->getVisibleSize();

	auto causeLabel = Label::createWithSystemFont(getCauses(), SETTING_FONT, 50);
	causeLabel->setAnchorPoint(Vec2(0.5, 0.5));
	causeLabel->setPosition(VisibleSize / 2);
	addChild(causeLabel);

	return this;
}

bool Forwards::RunAction(player* p)
{
	toast::addtoast(GameScene::getmap(), p->getPosition(), this->getCauses(), 4.0f);
	route::getInstance()->getpath(p, GameScene::iswalk, this->Steps, GameScene::getcol_count(), GameScene::getrow_count());
	p->go(route::getInstance()->getpathrow(), route::getInstance()->getpathcol());
	return true;
}
//Pure virtual function to be overrided, realize the event
bool Delay::RunAction(player* p)
{
	toast::addtoast(GameScene::getmap(), p->getPosition(), this->getCauses(), 4.0f);
	p->set_stayRounds(Rounds);
	return true;

}
//Realize the event
bool Wealth::RunAction(player* p)
{
	toast::addtoast(GameScene::getmap(), p->getPosition(), this->getCauses(), 4.0f);
	GameScene::update_money(p, Profit);
	return true;
}
//Preload all the pictures needed to show on screen
void Opportunity::Load()
{
	auto temp1 = Forwards::createWithSteps(FORWARD_MESSAGE1, FORWARD_MESSAGE1_STEP); temp1->retain();
	auto temp2 = Forwards::createWithSteps(FORWARD_MESSAGE2, FORWARD_MESSAGE2_STEP); temp2->retain();
	auto temp3 = Forwards::createWithSteps(FORWARD_MESSAGE3, FORWARD_MESSAGE3_STEP); temp3->retain();
	auto temp4 = Forwards::createWithSteps(FORWARD_MESSAGE4, FORWARD_MESSAGE4_STEP); temp4->retain();
	auto temp5 = Forwards::createWithSteps(FORWARD_MESSAGE5, FORWARD_MESSAGE5_STEP); temp5->retain();
	auto temp6 = Forwards::createWithSteps(FORWARD_MESSAGE6, FORWARD_MESSAGE6_STEP); temp6->retain();
	Forwards::getInstance()->push_back(temp1);
	Forwards::getInstance()->push_back(temp2);
	Forwards::getInstance()->push_back(temp3);
	Forwards::getInstance()->push_back(temp4);
	Forwards::getInstance()->push_back(temp5);
	Forwards::getInstance()->push_back(temp6);

	auto temp7 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE1, DELAY_MESSAGE1_ROUND, DELAY_MESSAGE1_STATUS); temp7->retain();
	auto temp8 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE2, DELAY_MESSAGE2_ROUND, DELAY_MESSAGE2_STATUS); temp8->retain();
	auto temp9 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE3, DELAY_MESSAGE3_ROUND, DELAY_MESSAGE3_STATUS); temp9->retain();
	auto temp10 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE4, DELAY_MESSAGE4_ROUND, DELAY_MESSAGE4_STATUS); temp10->retain();
	auto temp11 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE5, DELAY_MESSAGE5_ROUND, DELAY_MESSAGE5_STATUS); temp11->retain();
	auto temp12 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE6, DELAY_MESSAGE6_ROUND, DELAY_MESSAGE6_STATUS); temp12->retain();
	auto temp13 = Delay::createWithRoundsAndStatus(DELAY_MESSAGE7, DELAY_MESSAGE7_ROUND, DELAY_MESSAGE7_STATUS); temp13->retain();
	Delay::getInstance()->push_back(temp7);
	Delay::getInstance()->push_back(temp8);
	Delay::getInstance()->push_back(temp9);
	Delay::getInstance()->push_back(temp10);
	Delay::getInstance()->push_back(temp11);
	Delay::getInstance()->push_back(temp12);
	Delay::getInstance()->push_back(temp13);

	auto temp14 = Wealth::createWithProfit(WEALTH_MESSAGE1, WEALTH_MESSAGE1_MONEY); temp14->retain();
	auto temp15 = Wealth::createWithProfit(WEALTH_MESSAGE2, WEALTH_MESSAGE2_MONEY); temp15->retain();
	auto temp16 = Wealth::createWithProfit(WEALTH_MESSAGE3, WEALTH_MESSAGE3_MONEY); temp16->retain();
	auto temp17 = Wealth::createWithProfit(WEALTH_MESSAGE4, WEALTH_MESSAGE4_MONEY); temp17->retain();
	auto temp18 = Wealth::createWithProfit(WEALTH_MESSAGE5, WEALTH_MESSAGE5_MONEY); temp18->retain();
	auto temp19 = Wealth::createWithProfit(WEALTH_MESSAGE6, WEALTH_MESSAGE6_MONEY); temp19->retain();
	auto temp20 = Wealth::createWithProfit(WEALTH_MESSAGE7, WEALTH_MESSAGE7_MONEY); temp20->retain();
	auto temp21 = Wealth::createWithProfit(WEALTH_MESSAGE8, WEALTH_MESSAGE8_MONEY); temp21->retain();
	auto temp22 = Wealth::createWithProfit(WEALTH_MESSAGE9, WEALTH_MESSAGE9_MONEY); temp22->retain();

	Wealth::getInstance()->push_back(temp14);
	Wealth::getInstance()->push_back(temp15);
	Wealth::getInstance()->push_back(temp16);
	Wealth::getInstance()->push_back(temp17);
	Wealth::getInstance()->push_back(temp18);
	Wealth::getInstance()->push_back(temp19);
	Wealth::getInstance()->push_back(temp20);
	Wealth::getInstance()->push_back(temp21);
	Wealth::getInstance()->push_back(temp22);

}


Lottery::Lottery()
{
	name = new char[20];
}

Lottery::~Lottery()
{
	free(name);
}


bool Lottery::init()
{
	if (!Sprite::init())
		return false;
	addAnimation();
	SpriteFrame* spf;
	spf = Sprite_Frame->getSpriteFrameByName("publish_ly01.png");

	Sprite::initWithSpriteFrame(spf);
	setItemAnimate();
	return true;
}

//Adds a lottery publishing animation
void Lottery::addAnimation()
{
	Sprite_Frame = SpriteFrameCache::getInstance();
	Sprite_Frame->addSpriteFramesWithFile("publish_ly.plist", "publish_ly.png");

	memset(name, 0, 20);

	for (int i = 1; i <= 21; i++)
	{
		sprintf(name, "publish_ly%02d.png", i);
		animate.pushBack(Sprite_Frame->getSpriteFrameByName(name));
	}
}


void Lottery::setItemAnimate()
{
	if (!AnimationCache::getInstance()->getAnimation("publish_ly_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(animate, 0.1f), "publish_ly_animation");
	}
	normal_anmi = Animate::create(AnimationCache::getInstance()->getAnimation("publish_ly_animation"));
	normal_anmi->retain();
}

