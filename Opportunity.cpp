#include "Opportunity.h"
#include "Toast.h"
#include "GameSceneScene.h"
#include "Route.h"


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
void Opportunity::Addparticle()
{
	auto particle = ParticleSystemQuad::Create("particle_texture.plist");
	auto batch = ParticleBatchNode::CreateWithTexture(particle->GetTexture());
	batch->AddChild(particle);
	GameScene::Getmap()->AddChild(batch);
	particle->setPosition(Director::GetInstance()->GetvisibleSize() / 2);
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

	auto visibleSize = Director::GetInstance()->GetvisibleSize();

	auto causeLabel = Label::CreateWithSystemFont(GetCauses(), "Gothic", 50);
	causeLabel->setAnchorPoint(Vec2(0.5, 0.5));
	causeLabel->setPosition(visibleSize / 2);
	AddChild(causeLabel);

	return this;
}

bool Forwards::RunAction(Player* p)
{
	Toast::AddToast(GameScene::Getmap(), p->GetPosition(), this->GetCauses(), 4.0f);
	Route::GetInstance()->GetPath(p, GameScene::isWalk, this->Steps, GameScene::Getcol_count(), GameScene::Getrow_count());
	p->go(Route::GetInstance()->GetPathRow(), Route::GetInstance()->GetPathCol());
	return true;
}
//Pure virtual function to be overrided, realize the event
bool Delay::RunAction(Player* p)
{
	Toast::AddToast(GameScene::Getmap(), p->GetPosition(), this->GetCauses(), 4.0f);
	p->Set_stayRounds(Rounds);
	return true;

}
//Realize the event
bool Wealth::RunAction(Player* p)
{
	Toast::AddToast(GameScene::Getmap(), p->GetPosition(), this->GetCauses(), 4.0f);
	GameScene::UpdateMoney(p, Profit);
	return true;
}
//Preload all the pictures needed to show on screen
void Opportunity::Load()
{	
	auto temp1 = Forwards::CreateWithSteps("Take A Bus, Go Two Steps Ahead", 2); temp1->Retain();
	auto temp2 = Forwards::CreateWithSteps("Take The Subway,Go Six Steps Ahead", 6); temp2->Retain();
	auto temp3 = Forwards::CreateWithSteps("Came Across An Old Friend,Take You For A Ride For Five Steps", 5); temp3->Retain();
	auto temp4 = Forwards::CreateWithSteps("Take A Taxi, Go Three Steps Ahead", 3); temp4->Retain();
	auto temp5 = Forwards::CreateWithSteps("Ride A Bicycle,Go One Steps,Ahead", 1); temp5->Retain();
	auto temp6 = Forwards::CreateWithSteps("Across The Street, Four Steps Ahead", 4); temp6->Retain();
	Forwards::GetInstance()->push_back(temp1);
	Forwards::GetInstance()->push_back(temp2);
	Forwards::GetInstance()->push_back(temp3);
	Forwards::GetInstance()->push_back(temp4);
	Forwards::GetInstance()->push_back(temp5);
	Forwards::GetInstance()->push_back(temp6);

	auto temp7 = Delay::CreateWithRoundsAndStatus("Biten By A Fierce Dog, Stay In Hospital For Two Days", 2, 1); temp7->Retain();
	auto temp8 = Delay::CreateWithRoundsAndStatus("Arrested For Tax Evasion,Being in Jail For Two Days", 2, 2); temp8->Retain();
	auto temp9 = Delay::CreateWithRoundsAndStatus("Stay In A Five-Star Hotel For One Night", 1, 0); temp9->Retain();
	auto temp10 = Delay::CreateWithRoundsAndStatus("Raining! Stay Where You Are For One Day", 1, 0); temp10->Retain();
	auto temp11 = Delay::CreateWithRoundsAndStatus("Under Construction Ahead, Stop! Stay For Two Days", 2, 0); temp11->Retain();
	auto temp12 = Delay::CreateWithRoundsAndStatus("Caught A Cold! Stay In Hospital For One Day", 1, 1); temp12->Retain();
	auto temp13 = Delay::CreateWithRoundsAndStatus("Arrested For Overspeed, Stay In Jail For One Day", 1, 2); temp13->Retain();
	Delay::GetInstance()->push_back(temp7);
	Delay::GetInstance()->push_back(temp8);
	Delay::GetInstance()->push_back(temp9);
	Delay::GetInstance()->push_back(temp10);
	Delay::GetInstance()->push_back(temp11);
	Delay::GetInstance()->push_back(temp12);
	Delay::GetInstance()->push_back(temp13);

	auto temp14 = Wealth::CreateWithProfit("In A High-Class French Restaurant, cost $500", -500); temp14->Retain();
	auto temp15 = Wealth::CreateWithProfit("Win A Lottery, Get $500", 500); temp15->Retain();
	auto temp16 = Wealth::CreateWithProfit("Tax Paying Day, cost $1000", -1000); temp16->Retain();
	auto temp17 = Wealth::CreateWithProfit("Buy Something In The Department Store , cost $1500", -1500); temp17->Retain();
	auto temp18 = Wealth::CreateWithProfit("Get Fund, Get $2000", 2000); temp18->Retain();
	auto temp19 = Wealth::CreateWithProfit("Birthday! Get Present, $800, Get $800", 800); temp19->Retain();
	auto temp20 = Wealth::CreateWithProfit("Bank interests! Get $1000", 1000); temp20->Retain();
	auto temp21 = Wealth::CreateWithProfit("Lucky Money! Get $1000",1000); temp21->Retain();
	auto temp22 = Wealth::CreateWithProfit("Salary Day! Get $1500", 1500); temp22->Retain();

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
	spf = Sprite_Frame->GetSpriteFrameByName("publish_ly01.png");

	Sprite::InitWithSpriteFrame(spf);
	SetItemAnimate();
	return true;
}

//Adds a lottery publishing animation
void Lottery::AddAnimation()
{
	Sprite_Frame = SpriteFrameCache::GetInstance();
	Sprite_Frame->AddSpriteFramesWithFile("publish_ly.plist", "publish_ly.png");

	MemSet(name, 0, 20);

	for (int i = 1; i <= 21; i++)
	{
		sprintf(name, "publish_ly%02d.png", i);
		animate.PushBack(Sprite_Frame->GetSpriteFrameByName(name));
	}
}


void Lottery::SetItemAnimate()
{
	if (!AnimationCache::GetInstance()->GetAnimation("publish_ly_animation"))
	{
		AnimationCache::GetInstance()->AddAnimation(Animation::CreateWithSpriteFrames(animate, 0.1f), "publish_ly_animation");
	}
	normal_anmi = Animate::Create(AnimationCache::GetInstance()->GetAnimation("publish_ly_animation"));
	normal_anmi->Retain();
}

