#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include<SimpleAudioEngine.h>

USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::InitGLContextAttrs()
{
    //Set OpenGL context attributions,now can only Set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::SetGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::ApplicationDidFinishLaunching() {
    // initialize director
    auto director = Director::GetInstance();
    auto glview = director->GetOpenGLView();
    if(!glview) {
        glview = GLViewImpl::Create("My Game");
        director->SetOpenGLView(glview);
    }

    // turn on display FPS
    director->SetDisplayStats(false);

    // Set FPS. the default value is 1.0/60 if you don't call this
    director->SetAnimationInterval(1.0 / 60);

    register_all_packages();

    // Create a scene. it's an autorelease object
    auto scene = HelloWorld::CreateScene();

    // run
	
    director->RunWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::ApplicationDidEnterBackground() {
    Director::GetInstance()->StopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::GetInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::ApplicationWillEnterForeground() {
    Director::GetInstance()->StartAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::GetInstance()->resumeBackgroundMusic();
}
