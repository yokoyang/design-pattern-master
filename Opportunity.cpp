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



bool Opportunity::Init()
{
	if (!Layer::Init())
	{
		return false;
	}

	Causes = "";

	return true;
}
bool Forwards::Init()
{
	if (!Opportunity::Init())
	{
		return false;
	}
	Steps = 0;
	return true;
}
bool Delay::Init()
{
	if (!Opportunity::Init())
	{
		return false;
	}
	Rounds = 0;
	Status = 0;
	return true;
}
bool Wealth::Init()
{
	if (!Opportunity::Init())
	{
		return false;
	}
	Profit = 0;
	return true;
}
//Adds particle system
void Opportunity::AddParticle()
{
	auto particle = ParticleSystemQuad::Create(PARTICLE_SYSTEM);
	auto batch = ParticleBatchNode::createWithTexture(particle->getTexture());
	batch->AddChild(particle);
	GameScene::GetMap()->AddChild(batch);
	particle->SetPosition(Director::GetInstance()->GetVisibleSize() / 2);
}


Forwards* Forwards::CreateWithSteps(std::string causes, int steps)
{
	auto temp = Create();
	temp->Causes = causes;
	temp->Steps = steps;
	return temp;
}
//Create a Delay object,with Opportunity::causes, rounds, status
Delay* Delay::CreateWithRoundsAndStatus(std::string causes, int rounds, int status)
{
	auto temp = Create();
	temp->Causes = causes;
	temp->Rounds = rounds;
	temp->Status = status;
	return temp;
}
//Creates the Wealth Object
Wealth* Wealth::CreateWithProfit(std::string causes, int profit)
{
	auto temp = Create();
	temp->Causes = causes;
	temp->Profit = profit;
	return temp;
}





//Returns a layer showing the event
Layer*Opportunity::GetShowOnScreen()
{

	auto VisibleSize = Director::GetInstance()->GetVisibleSize();

	auto causeLabel = Label::createWithSystemFont(getCauses(), SETTING_FONT, 50);
	causeLabel->SetAnchorPoint(Vec2(0.5, 0.5));
	causeLabel->SetPosition(VisibleSize / 2);
	AddChild(causeLabel);

	return this;
}

bool Forwards::RunAction(Player* p)
{
	toast::addtoast(GameScene::GetMap(), p->GetPosition(), this->getCauses(), 4.0f);
	Route::GetInstance()->GetPath(p, GameScene::isWalk, this->Steps, GameScene::GetColCount(), GameScene::GetRowCount());
	p->Go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
	return true;
}
//Pure virtual function to be overrided, realize the event
bool Delay::RunAction(Player* p)
{
	toast::addtoast(GameScene::GetMap(), p->GetPosition(), this->getCauses(), 4.0f);
	p->set_stayRounds(Rounds);
	return true;

}
//Realize the event
bool Wealth::RunAction(Player* p)
{
	toast::addtoast(GameScene::GetMap(), p->GetPosition(), this->getCauses(), 4.0f);
	GameScene::UpdateMoney(p, Profit);
	return true;
}
//Preload all the pictures needed to show on screen
void Opportunity::Load()
{
	auto temp1 = Forwards::CreateWithSteps(FORWARD_MESSAGE1, FORWARD_MESSAGE1_STEP); temp1->retain();
	auto temp2 = Forwards::CreateWithSteps(FORWARD_MESSAGE2, FORWARD_MESSAGE2_STEP); temp2->retain();
	auto temp3 = Forwards::CreateWithSteps(FORWARD_MESSAGE3, FORWARD_MESSAGE3_STEP); temp3->retain();
	auto temp4 = Forwards::CreateWithSteps(FORWARD_MESSAGE4, FORWARD_MESSAGE4_STEP); temp4->retain();
	auto temp5 = Forwards::CreateWithSteps(FORWARD_MESSAGE5, FORWARD_MESSAGE5_STEP); temp5->retain();
	auto temp6 = Forwards::CreateWithSteps(FORWARD_MESSAGE6, FORWARD_MESSAGE6_STEP); temp6->retain();
	Forwards::GetInstance()->push_back(temp1);
	Forwards::GetInstance()->push_back(temp2);
	Forwards::GetInstance()->push_back(temp3);
	Forwards::GetInstance()->push_back(temp4);
	Forwards::GetInstance()->push_back(temp5);
	Forwards::GetInstance()->push_back(temp6);

	auto temp7 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE1, DELAY_MESSAGE1_ROUND, DELAY_MESSAGE1_STATUS); temp7->retain();
	auto temp8 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE2, DELAY_MESSAGE2_ROUND, DELAY_MESSAGE2_STATUS); temp8->retain();
	auto temp9 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE3, DELAY_MESSAGE3_ROUND, DELAY_MESSAGE3_STATUS); temp9->retain();
	auto temp10 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE4, DELAY_MESSAGE4_ROUND, DELAY_MESSAGE4_STATUS); temp10->retain();
	auto temp11 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE5, DELAY_MESSAGE5_ROUND, DELAY_MESSAGE5_STATUS); temp11->retain();
	auto temp12 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE6, DELAY_MESSAGE6_ROUND, DELAY_MESSAGE6_STATUS); temp12->retain();
	auto temp13 = Delay::CreateWithRoundsAndStatus(DELAY_MESSAGE7, DELAY_MESSAGE7_ROUND, DELAY_MESSAGE7_STATUS); temp13->retain();
	Delay::GetInstance()->push_back(temp7);
	Delay::GetInstance()->push_back(temp8);
	Delay::GetInstance()->push_back(temp9);
	Delay::GetInstance()->push_back(temp10);
	Delay::GetInstance()->push_back(temp11);
	Delay::GetInstance()->push_back(temp12);
	Delay::GetInstance()->push_back(temp13);

	auto temp14 = Wealth::CreateWithProfit(WEALTH_MESSAGE1, WEALTH_MESSAGE1_MONEY); temp14->retain();
	auto temp15 = Wealth::CreateWithProfit(WEALTH_MESSAGE2, WEALTH_MESSAGE2_MONEY); temp15->retain();
	auto temp16 = Wealth::CreateWithProfit(WEALTH_MESSAGE3, WEALTH_MESSAGE3_MONEY); temp16->retain();
	auto temp17 = Wealth::CreateWithProfit(WEALTH_MESSAGE4, WEALTH_MESSAGE4_MONEY); temp17->retain();
	auto temp18 = Wealth::CreateWithProfit(WEALTH_MESSAGE5, WEALTH_MESSAGE5_MONEY); temp18->retain();
	auto temp19 = Wealth::CreateWithProfit(WEALTH_MESSAGE6, WEALTH_MESSAGE6_MONEY); temp19->retain();
	auto temp20 = Wealth::CreateWithProfit(WEALTH_MESSAGE7, WEALTH_MESSAGE7_MONEY); temp20->retain();
	auto temp21 = Wealth::CreateWithProfit(WEALTH_MESSAGE8, WEALTH_MESSAGE8_MONEY); temp21->retain();
	auto temp22 = Wealth::CreateWithProfit(WEALTH_MESSAGE9, WEALTH_MESSAGE9_MONEY); temp22->retain();

	Wealth::GetInstance()->push_back(temp14);
	Wealth::GetInstance()->push_back(temp15);
	Wealth::GetInstance()->push_back(temp16);
	Wealth::GetInstance()->push_back(temp17);
	Wealth::GetInstance()->push_back(temp18);
	Wealth::GetInstance()->push_back(temp19);
	Wealth::GetInstance()->push_back(temp20);
	Wealth::GetInstance()->push_back(temp21);
	Wealth::GetInstance()->push_back(temp22);

}


Lottery::Lottery()
{
	name = new char[20];
}

Lottery::~Lottery()
{
	free(name);
}


bool Lottery::Init()
{
	if (!Sprite::Init())
		return false;
	AddAnimation();
	SpriteFrame* spf;
	spf = Sprite_Frame->getSpriteFrameByName("publish_ly01.png");

	Sprite::initWithSpriteFrame(spf);
	SetItemAnimate();
	return true;
}

//Adds a lottery publishing animation
void Lottery::AddAnimation()
{
	Sprite_Frame = SpriteFrameCache::GetInstance();
	Sprite_Frame->addSpriteFramesWithFile("publish_ly.plist", "publish_ly.png");

	memset(name, 0, 20);

	for (int i = 1; i <= 21; i++)
	{
		sprintf(name, "publish_ly%02d.png", i);
		animate.PushBack(Sprite_Frame->getSpriteFrameByName(name));
	}
}


void Lottery::SetItemAnimate()
{
	if (!AnimationCache::GetInstance()->getAnimation("publish_ly_animation"))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::createWithSpriteFrames(animate, 0.1f), "publish_ly_animation");
	}
	normal_anmi = Animate::Create(AnimationCache::GetInstance()->getAnimation("publish_ly_animation"));
	normal_anmi->retain();
}

