#include"Toast.h"
//Add toast
void Toast::AddToast(Node* node, Point p, std::string s, float time)
{
	auto pLabel = Label::CreateWithSystemFont(s.c_str(), "Arial", 20);
	pLabel->SetColor(Color3B::WHITE);
	pLabel->IgnoreAnchorPointForPosition(false);
	pLabel->SetAnchorPoint(Vec2::ANCHOR_MIDDLE);
	auto ly = LayerColor::Create(Color4B(130, 120, 120, 255));
	ly->IgnoreAnchorPointForPosition(false);
	ly->SetAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ly->SetContentSize(pLabel->GetContentSize() + Size(20, 15));
	node->AddChild(ly);
	node->AddChild(pLabel);
	ly->SetPosition(p);
	pLabel->SetPosition(ly->GetPosition());
	auto seq1 = Sequence::Create(FadeIn::Create(time / 5), DelayTime::Create(time / 5 * 1.5), FadeOut::Create(time / 5 * 2.5), CallFuncN::Create(ly, callfuncN_selector(Toast::RemoveToast)), nullptr);
	auto seq2 = Sequence::Create(EaseSineIn::Create(MoveBy::Create(time / 5, Vec2(0, 50))), DelayTime::Create(time / 5 * 2), EaseSineOut::Create(MoveBy::Create(time / 3, Vec2(0, -50))), nullptr);
	auto spawn = Spawn::Create(seq1, seq2, nullptr);
	auto action = Repeat::Create(spawn, 1);
	ly->SetOpacity(0);
	pLabel->SetOpacity(0);
	ly->RunAction(action);
	pLabel->RunAction(action->clone());
}

//Remove the toast
void Toast::RemoveToast(Node* node)
{
	this->RemoveFromParentAndCleanup(true);
}