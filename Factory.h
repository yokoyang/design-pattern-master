#include"control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"toast.h"
#include"FinalScene.h"


class Factory    
{    
public:    
    virtual Player* CreatePlayer() = 0;  
};

//A B C D 四种不同样式的Player
class FactoryA
{
public:    
    PlayerA* CreatePlayer(){
    	return new PlayerA();
    }
}

class FactoryB
{
public:    
    PlayerB* CreatePlayer(){
    	return new PlayerB();
    }
}

class FactoryC
{
public:    
    PlayerC* CreatePlayer(){
    	return new PlayerC();
    }
}

class FactoryD
{
public:    
    PlayerD* CreatePlayer(){
    	return new PlayerD();
    }
}