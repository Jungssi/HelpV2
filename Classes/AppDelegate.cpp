//AppDelegate.cpp
//This is App's Main Fuction
//1.Init Managers
//2.Load datas

#include "AppDelegate.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
        glview = GLViewImpl::create("HELP v2");
        director->setOpenGLView(glview);
    }
    
#if(defined _WIN32) || (defined _W64)
    
    glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);
    
#endif

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);

    
    // turn on display FPS
    //director->setDisplayStats(true);
    
    
    createInstance();
    loadData();


    auto scene = MenuScene::createScene();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::loadData()
{

    C_PLAYER*    pPlayer   = C_PLAYER::getInstance();
    C_TERRAIN*   pTerrain  = C_TERRAIN::getInstance();
    C_OBJECTMNG* pObject   = C_OBJECTMNG::getInstance();
    C_STAGEMNG*  pStageMng = C_STAGEMNG::getInstance();
    C_WORLDMNG*  pWorldMng = C_WORLDMNG::getInstance();
    C_DEADZONE*  pDeadZone = C_DEADZONE::getInstance();
    C_NPCWOMAN*  pNPCWoman = C_NPCWOMAN::getInstance();
    C_UIMNG*     pUIMng    = C_UIMNG::getInstance();
    C_SOUNDMNG*  pSoundMng = C_SOUNDMNG::getInstance();
    
    pSoundMng->init();
    pSoundMng->loadSoundData();
    
    pUIMng->loadUiData();
    pUIMng->initSprites();
    
    pWorldMng->createWorld(b2Vec2(0.0f, -30.0f), IS_DEBUG);

    pPlayer->loadTexture();
    pPlayer->init(pWorldMng);
    pPlayer->initSprites();
    pPlayer->initAnimations();
    pPlayer->setHorizontalVelocity(4.0f); //player left, right move speed

    pTerrain->loadTexture();
    pTerrain->init(pWorldMng);


    pObject->loadTexture();
    pObject->init(pWorldMng);
    
    pDeadZone->init();
    pDeadZone->setDeadZoneVelocity(1.0f);
    
    pNPCWoman->loadTexture();
    pNPCWoman->init(pWorldMng);
    pNPCWoman->initAnimations();
    pNPCWoman->setHorizontalVelocity(3.8f);
    
    pStageMng->init(pPlayer, pObject, pTerrain, pNPCWoman, pDeadZone);
}

void AppDelegate::createInstance()
{
    C_UIMNG::createInstance();
    C_PLAYER::createInstance();
    C_TERRAIN::createInstance();
    C_STAGEMNG::createInstance();
    C_WORLDMNG::createInstance();
    C_OBJECTMNG::createInstance();
    C_DEADZONE::createInstance();
    C_NPCWOMAN::createInstance();
    C_SOUNDMNG::createInstance();
    
}

void AppDelegate::releaseInstance()
{
    C_SOUNDMNG::releaseInstance();
    C_NPCWOMAN::releaseInstance();
    C_DEADZONE::releaseInstance();
    C_OBJECTMNG::releaseInstance();
    C_WORLDMNG::releaseInstance();
    C_STAGEMNG::releaseInstance();
    C_TERRAIN::releaseInstance();
    C_PLAYER::releaseInstance();
    C_UIMNG::releaseInstance();
}
