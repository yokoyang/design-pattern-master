#include "Control.h"
#include "GameSceneScene.h"
#include "Route.h"
#include "Toast.h"
#include "FinalScene.h"

//factory design pattern
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
    	return Create("player1.jpg");
    }
}

class FactoryB
{
public:    
    PlayerB* CreatePlayer(){
    	return Create("player2.jpg");
    }
}

class FactoryC
{
public:    
    PlayerC* CreatePlayer(){
    	return Create("player3.jpg");
    }
}

class FactoryD
{
public:    
    PlayerD* CreatePlayer(){
    	return Create("player4.jpg");
    }
}