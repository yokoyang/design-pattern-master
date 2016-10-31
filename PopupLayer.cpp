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

bool PopupLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setContentSize(Size::ZERO);

	// 初始化需要的 Menu
	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenuButton(menu);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch *t, Event *e){
		
		return true;
	};
	// _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::create(const char *backgroundImage)
{
	PopupLayer* ml = PopupLayer::create();
	ml->setSpriteBackGround(Sprite::create(backgroundImage));
	ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	return ml;
}

void PopupLayer::setTitle(const char *title, int fontsize)
{
	LabelTTF* ltfTitle = LabelTTF::create(title, "", fontsize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// 创建图片菜单按钮
	MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	// 添加文字说明并设置位置

	Size imenu = menuImage->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);


	getMenuButton()->addChild(menuImage);
	return true;
}

void PopupLayer::buttonCallback(cocos2d::Object *pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
	
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
	// this->removeFromParent();
}

void PopupLayer::onEnter()
{
	Layer::onEnter();

	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

	Size contentSize;
	// 设定好参数，在运行时加载
	if (getContentSize().equals(Size::ZERO))
	{
		getSpriteBackGround()->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->addChild(getSpriteBackGround(), 0, 0);
		contentSize = getSpriteBackGround()->getTexture()->getContentSize();
	}
	else {
		Scale9Sprite *background = getSprite9BackGround();
		background->setContentSize(getContentSize());
		background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
		this->addChild(background, 0, 0);
		contentSize = getContentSize();
	}


	// 添加按钮，并设置其位置
	this->addChild(getMenuButton());
	float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vecArray = getMenuButton()->getChildren();

	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth*(j + 1), winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	// 显示对话框标题
	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(Point(pCenter, Vec2(0, contentSize.height / 2 - 20)));
		getLabelTitle()->setColor(Color3B(0, 0, 0));
		this->addChild(getLabelTitle());
	}

	if (type == 1)
	{
		setlotterycontext(contentSize);
	}

	else
	{
		// 显示文本内容
		if (getLabelContentText())
		{
			LabelTTF* ltf = getLabelContentText();
			ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(Size(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
			ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
			ltf->setColor(Color3B(0, 0, 0));
			this->addChild(ltf);
		}
	}

	// 弹出效果
	Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.15f, 1.05f),
		ScaleTo::create(0.08f, 0.95f),
		ScaleTo::create(0.08f, 1.0f),
		NULL);
	this->runAction(popupLayer);

}



void PopupLayer::setPlayerVector(Vector<player*> _vector)
{
	for (int i = 0; i<_vector.size(); i++)
	{
		players_vec.pushBack(_vector.at(i));

	}

}

void PopupLayer::addplayerlottery()
{
	for (int i = 1; i <= 30; i++)
	{
		if (this->getChildByTag(1000 + i) != NULL)
		{
			this->removeChildByTag(1000 + i);
		}

	}
	Size winSize = Director::getInstance()->getWinSize();
	Size size = this->getContentSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	for (auto it = players_vec.begin(); it != players_vec.end(); it++)
	{
		player* Player = dynamic_cast<player*>(*it);

		lotterynum.clear();
		for (int i = 0; i < Player->vec.size(); i++)
		{

			LabelTTF* labelLotteryNumber = LabelTTF::create(String::createWithFormat("%i", Player->vec.at(i))->getCString(), "", 15);
			labelLotteryNumber->setPosition(Vec2(center.width + 20 + (i + 1) * 20, (winSize.height / 2 + 30) + j * 50));
			labelLotteryNumber->setColor(Color3B(255, 100, 100));
			labelLotteryNumber->setTag(1000 + Player->vec.at(i));
			addChild(labelLotteryNumber);
		}
	}
}


void PopupLayer::runanmi()
{
	scheduleOnce(schedule_selector(PopupLayer::realRunAnmi), 0.2f);
}

void PopupLayer::realRunAnmi(float t)
{
	lp->runAction(Sequence::create(lp->getNormal_anmi(),
		CallFunc::create([this]()
	{
		int lott = rand() % (30) + 1;
		scheduleOnce(schedule_selector(PopupLayer::dismissFromParent), 0.2f);
		Sprite* ball = Sprite::create("orange_ball.png");
		ball->setPosition(lp->getPosition() - lp->getContentSize() / 2 + Vec2(0, 13));
		ball->setAnchorPoint(Vec2(0, 0));
		addChild(ball);
		LabelTTF* ltf = LabelTTF::create(String::createWithFormat("%02d", lott)->getCString(), "", 20);
		ltf->setPosition(ball->getPosition() + Vec2(5, 6));
		ltf->setAnchorPoint(Vec2(0, 0));
		addChild(ltf);
		Size winSize = Director::getInstance()->getWinSize();
		Size center = (winSize) / 2;
		int j = 0;
		for (auto it = players_vec.begin(); it != players_vec.end(); it++)
		{
			player* Player = dynamic_cast<player*>(*it);
			

			for (int i = 0; i < Player->vec.size(); i++)
			{
				if (Player->vec.at(i) == lott)
				{
					Duang::addparticle();
					GameScene::update_money(Player, 50000);
				}
			}
			Player->vec.clear();
			j++;
		}
	}
	), NULL));
}


void PopupLayer::dismissFromParent(float t)
{
	this->setVisible(false);
}


void PopupLayer::addplayerinfo(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();
	Size center = (winSize - size) / 2;
	int j = 0;
	Sprite* playerSprite = NULL;
	for (auto it = players_vec.begin(); it != players_vec.end(); it++)
	{
		player* Player = dynamic_cast<player*>(*it);
		int tag = Player->getTag();
		if (tag == 1)
		{
			playerSprite = Sprite::create("player1.jpg");
		}
		else if (tag == 2)
		{
			playerSprite = Sprite::create("player2.png");
		}
		else if (tag == 3)
		{
			playerSprite = Sprite::create("player3.png");
		}
		else if (tag == 4)
		{
			playerSprite = Sprite::create("player4.png");
		}
		playerSprite->setPosition(center.width + 20, (winSize.height / 2 + 50) + j * 50);
		addChild(playerSprite);
		j++;
	}
}

void PopupLayer::setlotterycontext(Size size)
{
	Size winSize = Director::getInstance()->getWinSize();
	lp = Lottery::create();
	addChild(lp);
	lp->setPosition((winSize) / 2);

	addplayerinfo(size);

}

void PopupLayer::onExit()
{

	
	//this->removeFromParent();
	Layer::onExit();
}
