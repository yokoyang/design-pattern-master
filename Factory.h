#include "control.h"
#include "GameSceneScene.h"
#include "route.h"
#include "toast.h"
#include "FinalScene.h"


class Factory    
{    
public:    
    virtual VirtualPlayer* CreatePlayer() = 0;  
};

//A B C D 四种不同样式的Player
class FactoryA
{
public:    
    PlayerA* CreatePlayer(){
    	return create("player1.jpg");
    }
}

class FactoryB
{
public:    
    PlayerB* CreatePlayer(){
    	return create("player2.jpg");
    }
}

class FactoryC
{
public:    
    PlayerC* CreatePlayer(){
    	return create("player3.jpg");
    }
}

class FactoryD
{
public:    
    PlayerD* CreatePlayer(){
    	return create("player4.jpg");
    }
}