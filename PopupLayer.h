#pragma once
#pragma warning(disable:4996)
#include "cocos2d.h"

#include "cocos-ext.h"
#include"Player.h"
#include"Opportunity.h"
USING_NS_CC_EXT;


USING_NS_CC;

const int Pop_FontSize = 20;

class PopupLayer :public Layer
{
public:
	//Constructor and destructor 
	PopupLayer();
	~PopupLayer();
	virtual bool Init();
	CREATE_FUNC(PopupLayer);
	Vector<Player*> players_vec;
	std::vector<int>lotterynum;
	static PopupLayer * Create(const char* backgroundImage);
	void SetTitle(const char* title, int fontsize = Pop_FontSize);
	void SetContentText(const char* text, int fontsize = Pop_FontSize, int padding = 50, int paddintTop = 100);
	void SetCallbackFunc(Object* target, SEL_CallFuncN callfun);
	void SetPlayerVector(Vector<Player*>_vector);
	bool AddButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

	void AddPlayerlottery();
	void RunAnmi();
	virtual void OnEnter();
	virtual void OnExit();
	void AddPlayerInfo(Size size);
	void SetLotteryContext(Size size);
	void SetType(int i){ type = i; };
private:
	void ButtonCallback(Object* pSender);

	//Margins
	int m_contentPadding;
	int m_contentPaddingTop;

	Object* m_callbackListener;
	SEL_CallFuncN m_callback;

	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);

	CC_SYNTHESIZE(int, dataTag, DataTag);
	Lottery* lp;
	void RealRunAnmi(float dt);
	void DismissFromParent(float dt);
	int type=0;
};
