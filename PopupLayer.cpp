#include "PopupLayer.h"
#include"GameSceneScene.h"

PopupLayer::PopupLayer() :
m__pMenu(NULL)
, m_contentPadding(0)
, m_contentPaddingTop(0)
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
	this->setContentSize(Size::ZERO);

	// 初始化需要的 Menu
	Menu* menu = Menu::Create();
	menu->SetPosition(Point::ZERO);
	setMenuButton(menu);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto listener = EventListenerTouchOneByOne::Create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch *t, Event *e){
		
		return true;
	};
	// _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::Create(const char *backgroundImage)
{
	PopupLayer* ml = PopupLayer::Create();
	ml->setSpriteBackGround(Sprite::Create(backgroundImage));
	ml->setSprite9BackGround(Scale9Sprite::Create(backgroundImage));
	return ml;
}

void PopupLayer::setTitle(const char *title, int fontSize)
{
	LabelTTF* ltfTitle = LabelTTF::Create(title, "", fontSize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontSize, int padding, int paddingTop)
{
	LabelTTF* ltf = LabelTTF::Create(text, "", fontSize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupLayer::SetCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}


bool PopupLayer::AddButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::GetInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	MenuItemImage* menuImage = MenuItemImage::Create(normalImage, selectedImage, this, menu_selector(PopupLayer::ButtonCallback));
	menuImage->SetTag(tag);
	menuImage->SetPosition(pCenter);

	// 添加文字说明并设置位置

	Size imenu = menuImage->GetContentSize();
	LabelTTF* ttf = LabelTTF::Create(title, "", 20);
	ttf->SetColor(Color3B(0, 0, 0));
	ttf->SetPosition(Vec2(imenu.width / 2, imenu.height / 2));
	menuImage->AddChild(ttf);


	GetMenuButton()->AddChild(menuImage);
	return true;
}
//popup call back button
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

	Size winSize = Director::GetInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

	Size contentSize;
	// 设定好参数，在运行时加载
	if (GetContentSize().equals(Size::ZERO))
	{
		GetSpriteBackGround()->SetPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->AddChild(GetSpriteBackGround(), 0, 0);
		contentSize = GetSpriteBackGround()->getTexture()->GetContentSize();
	}
	else {
		Scale9Sprite *background = GetSprite9BackGround();
		background->setContentSize(GetContentSize());
		background->SetPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->AddChild(background, 0, 0);
		contentSize = GetContentSize();
	}


	// 添加按钮，并设置其位置
	this->AddChild(GetMenuButton());
	float btnWidth = contentSize.width / (GetMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vecArray = GetMenuButton()->getChildren();

	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->SetPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth*(j + 1), winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	// 显示对话框标题
	if (GetLabelTitle())
	{
		GetLabelTitle()->SetPosition(Point(pCenter, Vec2(0, contentSize.height / 2 - 20)));
		GetLabelTitle()->SetColor(Color3B(0, 0, 0));
		this->AddChild(GetLabelTitle());
	}

	if (type == 1)
	{
		Setlotterycontext(contentSize);
	}

	else
	{
		// 显示文本内容
		if (GetLabelContentText())
		{
			LabelTTF* ltf = GetLabelContentText();
			ltf->SetPosition(Vec2(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(Size(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
			ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
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
	for (int i = 1; i <= POPUPLAYER_BALL_NUMBER; i++)
	{
		if (this->getChildByTag(1000 + i) != NULL)
		{
			this->removeChildByTag(1000 + i);
		}

	}
	Size winSize = Director::GetInstance()->getWinSize();
	Size size = this->GetContentSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	for (auto it = players_vec.begin(); it != players_vec.end(); it++)
	{
		Player* player = dynamic_cast<Player*>(*it);

		lotteryNum.clear();
		for (int i = 0; i < Player->vec.size(); i++)
		{

			LabelTTF* labelLotteryNumber = LabelTTF::Create(String::createWithFormat("%i", Player->vec.at(i))->getCString(), "", 15);
			labelLotteryNumber->SetPosition(Vec2(center.width + 20 + (i + 1) * 20, (winSize.height / 2 + 30) + j * 50));
			labelLotteryNumber->SetColor(Color3B(255, 100, 100));
			labelLotteryNumber->SetTag(1000 + Player->vec.at(i));
			AddChild(labelLotteryNumber);
		}
	}
}


void PopupLayer::RunAnmi()
{
	ScheduleOnce(schedule_selector(PopupLayer::RealRunAnmi), 0.2f);
}

void PopupLayer::RealRunAnmi(float t)
{
	lp->RunAction(Sequence::Create(lp->getNormal_anmi(),
		CallFunc::Create([this]()
	{
		int lott = rand() % (30) + 1;
		ScheduleOnce(schedule_selector(PopupLayer::DismissFromParent), 0.2f);
		Sprite* ball = Sprite::Create(BALL);
		ball->SetPosition(lp->GetPosition() - lp->GetContentSize() / 2 + Vec2(0, 13));
		ball->SetAnchorPoint(Vec2(0, 0));
		AddChild(ball);
		LabelTTF* ltf = LabelTTF::Create(String::createWithFormat("%02d", lott)->getCString(), "", 20);
		ltf->SetPosition(ball->GetPosition() + Vec2(5, 6));
		ltf->SetAnchorPoint(Vec2(0, 0));
		AddChild(ltf);
		Size winSize = Director::GetInstance()->getWinSize();
		Size center = (winSize) / 2;
		int j = 0;
		for (auto it = players_vec.begin(); it != players_vec.end(); it++)
		{
			Player* player = dynamic_cast<Player*>(*it);
			

			for (int i = 0; i < Player->vec.size(); i++)
			{
				if (Player->vec.at(i) == lott)
				{
					Opportunity::AddParticle();
					GameScene::UpdateMoney(Player, LOTTERY_WIN_MONEY);
				}
			}
			Player->vec.clear();
			j++;
		}
	}
	), NULL));
}


void PopupLayer::DismissFromParent(float t)
{
	this->SetVisible(false);
}


void PopupLayer::Addplayerinfo(Size size)
{
	Size winSize = Director::GetInstance()->getWinSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	Sprite* playerSprite = NULL;
	for (auto it = players_vec.begin(); it != players_vec.end(); it++)
	{
		Player* player = dynamic_cast<Player*>(*it);
		int tag = Player->getTag();
		if (tag == 1)
		{
			playerSprite = Sprite::Create(PLAYER_ME);
		}
		else if (tag == 2)
		{
			playerSprite = Sprite::Create(PLAYER_ENEMY1);
		}
		else if (tag == 3)
		{
			playerSprite = Sprite::Create(PLAYER_ENEMY2);
		}
		else if (tag == 4)
		{
			playerSprite = Sprite::Create(PLAYER_ENEMY3);
		}
		playerSprite->SetPosition(center.width + 20, (winSize.height / 2 + 50) + j * 50);
		AddChild(playerSprite);
		j++;
	}
}

void PopupLayer::Setlotterycontext(Size size)
{
	Size winSize = Director::GetInstance()->getWinSize();
	lp = Lottery::Create();
	AddChild(lp);
	lp->SetPosition((winSize) / 2);

	Addplayerinfo(size);

}

void PopupLayer::OnExit()
{

	
	//this->removeFromParent();
	Layer::OnExit();
}
