#include"Factory.h"
#include"control.h"
#include"GameSceneScene.h"
#include"route.h"
#include"toast.h"
#include"FinalScene.h"

Factory::CreatePlayer(int PlayerType){

    string picName = "player";
    switch(PlayerType){
        case 1:
            picName+="1";
            break;
        case 2:
            picName+="2";
            break;
        case 3:
            picName+="3";
            break;
        case 4:
            picName+="4";
            break;
        default:
            //当前只支持4种类型
            //其他按默认为第一种
            picName+="1";
            log("error type");
            break;
    }
    picName += ".jpg";

}
