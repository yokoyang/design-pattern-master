#include "PopupLayer.h"
#include"GameSceneScene.h"

PopupLayer::PopupLayer() :
m__pMenu(NULL)
, m_contentPAdding(0)
, m_contentPAddingTop(0)
, m_callbackListener(NULL)
, m_callback(NULL)
, m__sfBackGround(NULL)
, m__s9BackGround(NULL)
, m__ltContentText(NULL)
, m__ltTitle(NULL)
{

}

PopupLayer::~PopupLayer()
{
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}

bool PopupLayer::Init()
{
	if (!Layer::Init())
	{
		return false;
	}
	this->SetContentSize(Size::ZERO);

	// 初始化需要的 Menu
	Menu* menu = Menu::Create();
	menu->setPosition(Point::ZERO);
	SetMenuButton(menu);
	SetTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto listener = EventListenerTouchOneByOne::Create();
	listener->SetSwallowTouches(true);

	listener->onTouchBegan = [](Touch *t, Event *e){
		
		return true;
	};
	// _eventDispatcher->AddEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::Create(const char *backgroundImage)
{
	PopupLayer* ml = PopupLayer::Create();
	ml->SetSpriteBackGround(Sprite::Create(backgroundImage));
	ml->SetSprite9BackGround(Scale9Sprite::Create(backgroundImage));
	return ml;
}

void PopupLayer::SetTitle(const char *title, int fontsize)
{
	LabelTTF* ltfTitle = LabelTTF::Create(title, "", fontsize);
	SetLabelTitle(ltfTitle);
}

void PopupLayer::SetContentText(const char *text, int fontsize, int pAdding, int pAddingTop)
{
	LabelTTF* ltf = LabelTTF::Create(text, "", fontsize);
	SetLabelContentText(ltf);
	m_contentPAdding = pAdding;
	m_contentPAddingTop = pAddingTop;
}

void PopupLayer::SetCallbackFunc(cocos2d::Object *tarGet, SEL_CallFuncN callfun)
{
	m_callbackListener = tarGet;
	m_callback = callfun;
}


bool PopupLayer::AddButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::GetInstance()->GetWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	MenuItemImage* menuImage = MenuItemImage::Create(normalImage, selectedImage, this, menu_selector(PopupLayer::ButtonCallback));
	menuImage->SetTag(tag);
	menuImage->setPosition(pCenter);

	// 添加文字说明并设置位置

	Size imenu = menuImage->GetContentSize();
	LabelTTF* ttf = LabelTTF::Create(title, "", 20);
	ttf->SetColor(Color3B(0, 0, 0));
	ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
	menuImage->AddChild(ttf);


	GetMenuButton()->AddChild(menuImage);
	return true;
}

void PopupLayer::ButtonCallback(cocos2d::Object *pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
	
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
	// this->removeFromParent();
}

void PopupLayer::OnEnter()
{
	Layer::OnEnter();

	Size winSize = Director::GetInstance()->GetWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

	Size contentSize;
	// 设定好参数，在运行时加载
	if (GetContentSize().equals(Size::ZERO))
	{
		GetSpriteBackGround()->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->AddChild(GetSpriteBackGround(), 0, 0);
		contentSize = GetSpriteBackGround()->GetTexture()->GetContentSize();
	}
	else {
		Scale9Sprite *background = GetSprite9BackGround();
		background->SetContentSize(GetContentSize());
		background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->AddChild(background, 0, 0);
		contentSize = GetContentSize();
	}


	// 添加按钮，并设置其位置
	this->AddChild(GetMenuButton());
	float btnWidth = contentSize.width / (GetMenuButton()->GetChildrenCount() + 1);

	Vector<Node*> vecArray = GetMenuButton()->GetChildren();

	int j = 0;
	for (auto it = vecArray.Begin(); it != vecArray.End(); it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth*(j + 1), winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	// 显示对话框标题
	if (GetLabelTitle())
	{
		GetLabelTitle()->setPosition(Point(pCenter, Vec2(0, contentSize.height / 2 - 20)));
		GetLabelTitle()->SetColor(Color3B(0, 0, 0));
		this->AddChild(GetLabelTitle());
	}

	if (type == 1)
	{
		SetLotteryContext(contentSize);
	}

	else
	{
		// 显示文本内容
		if (GetLabelContentText())
		{
			LabelTTF* ltf = GetLabelContentText();
			ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			ltf->SetDimensions(Size(contentSize.width - m_contentPAdding * 2, contentSize.height - m_contentPAddingTop));
			ltf->SetHorizontalAlignment(kCCTextAlignmentLeft);
			ltf->SetColor(Color3B(0, 0, 0));
			this->AddChild(ltf);
		}
	}

	// 弹出效果
	Action* popupLayer = Sequence::Create(ScaleTo::Create(0.0, 0.0),
		ScaleTo::Create(0.15f, 1.05f),
		ScaleTo::Create(0.08f, 0.95f),
		ScaleTo::Create(0.08f, 1.0f),
		NULL);
	this->RunAction(popupLayer);

}



void PopupLayer::SetPlayerVector(Vector<Player*> _vector)
{
	for (int i = 0; i<_vector.size(); i++)
	{
		players_vec.PushBack(_vector.at(i));

	}

}

void PopupLayer::AddPlayerLottery()
{
	for (int i = 1; i <= 30; i++)
	{
		if (this->GetChildByTag(1000 + i) != NULL)
		{
			this->RemoveChildByTag(1000 + i);
		}

	}
	Size winSize = Director::GetInstance()->GetWinSize();
	Size size = this->GetContentSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	for (auto it = players_vec.Begin(); it != players_vec.End(); it++)
	{
		Player* player = dynamic_cast<Player*>(*it);

		lotterynum.Clear();
		for (int i = 0; i < player->vec.size(); i++)
		{

			LabelTTF* labelLotteryNumber = LabelTTF::Create(String::CreateWithFormat("%i", player->vec.at(i))->GetCString(), "", 15);
			labelLotteryNumber->setPosition(Vec2(center.width + 20 + (i + 1) * 20, (winSize.height / 2 + 30) + j * 50));
			labelLotteryNumber->SetColor(Color3B(255, 100, 100));
			labelLotteryNumber->SetTag(1000 + player->vec.at(i));
			AddChild(labelLotteryNumber);
		}
	}
}


void PopupLayer::RunAnmi()
{
	ScheduleOnce(schedule_selector(PopupLayer::realRunAnmi), 0.2f);
}

void PopupLayer::realRunAnmi(float t)
{
	lp->RunAction(Sequence::Create(lp->GetNormal_anmi(),
		CallFunc::Create([this]()
	{
		int lott = rand() % (30) + 1;
		ScheduleOnce(schedule_selector(PopupLayer::DismissFromParent), 0.2f);
		Sprite* ball = Sprite::Create("orange_ball.png");
		ball->setPosition(lp->GetPosition() - lp->GetContentSize() / 2 + Vec2(0, 13));
		ball->setAnchorPoint(Vec2(0, 0));
		AddChild(ball);
		LabelTTF* ltf = LabelTTF::Create(String::CreateWithFormat("%02d", lott)->GetCString(), "", 20);
		ltf->setPosition(ball->GetPosition() + Vec2(5, 6));
		ltf->setAnchorPoint(Vec2(0, 0));
		AddChild(ltf);
		Size winSize = Director::GetInstance()->GetWinSize();
		Size center = (winSize) / 2;
		int j = 0;
		for (auto it = players_vec.Begin(); it != players_vec.End(); it++)
		{
			Player* player = dynamic_cast<Player*>(*it);
			

			for (int i = 0; i < player->vec.size(); i++)
			{
				if (player->vec.at(i) == lott)
				{
					Opportunity::Addparticle();
					GameScene::UpdateMoney(player, 50000);
				}
			}
			player->vec.Clear();
			j++;
		}
	}
	), NULL));
}


void PopupLayer::DismissFromParent(float t)
{
	this->setVisible(false);
}


void PopupLayer::AddPlayerInfo(Size size)
{
	Size winSize = Director::GetInstance()->GetWinSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	Sprite* playerSprite = NULL;
	for (auto it = players_vec.Begin(); it != players_vec.End(); it++)
	{
		Player* player = dynamic_cast<Player*>(*it);
		int tag = player->GetTag();
		if (tag == 1)
		{
			playerSprite = Sprite::Create("player1.jpg");
		}
		else if (tag == 2)
		{
			playerSprite = Sprite::Create("player2.png");
		}
		else if (tag == 3)
		{
			playerSprite = Sprite::Create("player3.png");
		}
		else if (tag == 4)
		{
			playerSprite = Sprite::Create("player4.png");
		}
		playerSprite->setPosition(center.width + 20, (winSize.height / 2 + 50) + j * 50);
		AddChild(playerSprite);
		j++;
	}
}

void PopupLayer::SetLotteryContext(Size size)
{
	Size winSize = Director::GetInstance()->GetWinSize();
	lp = Lottery::Create();
	AddChild(lp);
	lp->setPosition((winSize) / 2);

	AddPlayerInfo(size);

}

void PopupLayer::OnExit()
{

	
	//this->removeFromParent();
	Layer::OnExit();
}
