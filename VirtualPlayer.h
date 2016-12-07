#pragma once
#pragma warning(disable:4996)
#include"cocos2d.h"
#include"Ui.h"

USING_NS_CC;

class VirtualPlayer :public Sprite
{
protected:
    //The player's name , shown on screen
    Label* _name;
    //The property
    float _money;
    float saveMony;
    //The path
    std::vector<int> pathRow;
    std::vector<int> pathCol;
    float tileWidth=32;
    float tileHeigh=32;
    //Coming direction
    int comeX;
    int comeY;
    //Steps taken
    int _step;
    //Steps in total
    int _stepCount;
    //Current coordinate
    int nowRow;
    int nowCol;
    //The coordinate of next step
    int row;
    int col;
    //Rounds to stay 
    int stayRounds;
    //Whether the player is able to move
    bool turnMe;
    //Whether the round has ended
    bool oneRoundend;
    //Get a string to show property
    Label* money_string;
    //Animation names
    char left_animation[20];
    char right_animation[20];
    char down_animation[20];
    char up_animation[20];
    //Animations
    Vector<SpriteFrame*>Left;
    Vector<SpriteFrame*>Right;
    Vector<SpriteFrame*>Down;
    Vector<SpriteFrame*>Up;
    //The ID of the character' estates of level 1,2,3
    std::vector<int>id;
    //Initiate the animation
    void InitAnimate();
    void SetAnimate();
    //The number animation to show the steps to take
    void Addstep_image_running(std::vector<int>pathRow, std::vector<int>pathCol);
public:
    std::vector<int>vec;
    Animate* left;
    Animate* right;
    Animate* up;
    Animate* down;
    Player();
    ~Player();
    //Deal with turnMe,whether the character can move
    virtual void Setturnme(bool turn){ turnMe = turn; };
    virtual bool Getturnme(){ return turnMe; };
    //Deal with the coming directon coordinate
    virtual int Getcomex(){ return comeX; };
    virtual int Getcomey(){ return comeY; };
    virtual void Setcomex(int comeX){ this->comeX = comeX; };
    virtual void Setcomey(int comeY){ this->comeY = comeY; };
    static Player* Createwith (char* name, int tag, SpriteFrame* imag, float& money);
    CREATE_FUNC(player);
    //Set pathRow and pathCol after the acquisition of the path
    virtual void Initpathrowandcol();
    virtual int Get_stayRounds(){ return stayRounds; };
    virtual void Set_stayRounds(int i){ stayRounds = i; };
    //Begin the player's motion
    virtual void Go(std::vector<int>pathRow,std::vector<int>pathCol);
    //Acquire a lottery
    virtual void GetLottery();
    //Set the ID of the estates of the player of level 1,2,3
    virtual void Set_id(int id1, int id2, int id3){ id.push_back(id1); id.push_back(id2); id.push_back(id3); };
    virtual std::vector<int> Get_id(){ return id; };
    //Get personal info
    virtual Label* Get_name(){ return _name; };
    virtual Label* Getmoney_string(){ return money_string; };
    virtual void Settilesize(float tileWidth, float tileHeigh);
    //Deal with the money
    virtual void Setmoney(float money){ _money = money; };
    virtual float Getmoney(){ return _money; };
    //Initaite the player info
    virtual bool Init();
    virtual void AddPlayerAnimation(char* left_animation, char* right_animation, char* down_animation, char* up_animation);
};
