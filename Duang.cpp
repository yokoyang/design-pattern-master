#include "Duang.h"
#include<toast.h>
#include<GameSceneScene.h>


std::vector <Forwards*> Forwards::Instances;
std::vector <Delay*> Delay::Instances;
std::vector <Wealth*> Wealth::Instances;

Duang::Duang()
{
}
Duang::~Duang()
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



bool Duang::init()
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
	if (!Duang::init())
	{
		return false;
	}
	Steps = 0;
	return true;
}
bool Delay::init()
{
	if (!Duang::init())
	{
		return false;
	}
	Rounds = 0;
	Status = 0;
	return true;
}
bool Wealth::init()
{
	if (!Duang::init())
	{
		return false;
	}
	Profit = 0;
	return true;
}
//Adds particle system
void Duang::addparticle()
{
	auto particle = ParticleSystemQuad::create("particle_texture.plist");
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
//Create a Delay object,with Duang::causes, rounds, status
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
Layer*Duang::getShowOnScreen()
{

	auto VisibleSize = Director::getInstance()->getVisibleSize();

	auto causeLabel = Label::createWithSystemFont(getCauses(), "Gothic", 50);
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
void Duang::Load()
{
	auto temp1 = Forwards::createWithSteps("Take A Bus, Go Two Steps Ahead", 2); temp1->retain();
	auto temp2 = Forwards::createWithSteps("Take The Subway,Go Six Steps Ahead", 6); temp2->retain();
	auto temp3 = Forwards::createWithSteps("Came Across An Old Friend,Take You For A Ride For Five Steps", 5); temp3->retain();
	auto temp4 = Forwards::createWithSteps("Take A Taxi, Go Three Steps Ahead", 3); temp4->retain();
	auto temp5 = Forwards::createWithSteps("Ride A Bicycle,Go One Steps,Ahead", 1); temp5->retain();
	auto temp6 = Forwards::createWithSteps("Across The Street, Four Steps Ahead", 4); temp6->retain();
	Forwards::getInstance()->push_back(temp1);
	Forwards::getInstance()->push_back(temp2);
	Forwards::getInstance()->push_back(temp3);
	Forwards::getInstance()->push_back(temp4);
	Forwards::getInstance()->push_back(temp5);
	Forwards::getInstance()->push_back(temp6);

	auto temp7 = Delay::createWithRoundsAndStatus("Biten By A Fierce Dog, Stay In Hospital For Two Days", 2, 1); temp7->retain();
	auto temp8 = Delay::createWithRoundsAndStatus("Arrested For Tax Evasion,Being in Jail For Two Days", 2, 2); temp8->retain();
	auto temp9 = Delay::createWithRoundsAndStatus("Stay In A Five-Star Hotel For One Night", 1, 0); temp9->retain();
	auto temp10 = Delay::createWithRoundsAndStatus("Raining! Stay Where You Are For One Day", 1, 0); temp10->retain();
	auto temp11 = Delay::createWithRoundsAndStatus("Under Construction Ahead, Stop! Stay For Two Days", 2, 0); temp11->retain();
	auto temp12 = Delay::createWithRoundsAndStatus("Caught A Cold! Stay In Hospital For One Day", 1, 1); temp12->retain();
	auto temp13 = Delay::createWithRoundsAndStatus("Arrested For Overspeed, Stay In Jail For One Day", 1, 2); temp13->retain();
	Delay::getInstance()->push_back(temp7);
	Delay::getInstance()->push_back(temp8);
	Delay::getInstance()->push_back(temp9);
	Delay::getInstance()->push_back(temp10);
	Delay::getInstance()->push_back(temp11);
	Delay::getInstance()->push_back(temp12);
	Delay::getInstance()->push_back(temp13);

	auto temp14 = Wealth::createWithProfit("In A High-Class French Restaurant, cost $500", -500); temp14->retain();
	auto temp15 = Wealth::createWithProfit("Win A Lottery, get $500", 500); temp15->retain();
	auto temp16 = Wealth::createWithProfit("Tax Paying Day, cost $1000", -1000); temp16->retain();
	auto temp17 = Wealth::createWithProfit("Buy Something In The Department Store , cost $1500", -1500); temp17->retain();
	auto temp18 = Wealth::createWithProfit("Get Fund, get $2000", 2000); temp18->retain();
	auto temp19 = Wealth::createWithProfit("Birthday! Get Present, $800, get $800", 800); temp19->retain();
	auto temp20 = Wealth::createWithProfit("Bank interests! Get $1000", 1000); temp20->retain();
	auto temp21 = Wealth::createWithProfit("Lucky Money! Get $1000",1000); temp21->retain();
	auto temp22 = Wealth::createWithProfit("Salary Day! Get $1500", 1500); temp22->retain();

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

