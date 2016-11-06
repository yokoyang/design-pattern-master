#pragma once
#pragma warning(disable:4996)
#include "cocos2d.h"

#include "cocos-ext.h"
#include"player.h"
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
	virtual bool init();
	CREATE_FUNC(PopupLayer);
	Vector<player*>players_vec;
	std::vector<int>lotterynum;
	static PopupLayer * create(const char* backgroundImage);
	void setTitle(const char* title, int fontsize = Pop_FontSize);
	void setContentText(const char* text, int fontsize = Pop_FontSize, int padding = 50, int paddintTop = 100);
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	void setPlayerVector(Vector<player*>_vector);
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);

	void addplayerlottery();
	void runanmi();
	virtual void onEnter();
	virtual void onExit();
	void addplayerinfo(Size size);
	void setlotterycontext(Size size);
	void settype(int i){ type = i; };
private:
	void buttonCallback(Object* pSender);

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
	void realRunAnmi(float dt);
	void dismissFromParent(float dt);
	int type=0;
};
