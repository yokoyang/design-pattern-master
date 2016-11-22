#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"


//唯一的工厂 在内部判断    
class Factory    
{    
public:     
    Singleplayer* CreatePlayer();
};  