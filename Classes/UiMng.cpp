//
//  UiMng.cpp
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 11..
//
//

#include "UiMng.h"
#include "AppMacros.h"

USING_NS_CC;

C_UIMNG* C_UIMNG::m_pInstance = NULL;

C_UIMNG::C_UIMNG()
{
    for(int i = E_UI_DEAFUALT; i < E_UI_MAX; i++)
    {
        m_pTextureUiBtn[i] = NULL;
        m_pSprUiBtn[i] = NULL;
    }
}

void C_UIMNG::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_UIMNG;
        log("C_UIMNG :: UIMMR Instance created");
    }
    
}

C_UIMNG* C_UIMNG::getInstance()
{
    return m_pInstance;
}

void C_UIMNG::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_UIMNG :: UIMNG Instance released");
    }
}

void C_UIMNG::loadUiData()
{
    
    m_pTextureUiBtn[E_UI_NEWGAME_ON]     = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_newgamea.png");
    m_pTextureUiBtn[E_UI_NEWGAME_OFF]    = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_newgamed.png");
    
    m_pTextureUiBtn[E_UI_RESUMEGAME_ON]  = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_resumea.png");
    m_pTextureUiBtn[E_UI_RESUMEGAME_OFF] = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_resumed.png");

	m_pTextureUiBtn[E_UI_SND_ON]         = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_soundon.png");
	m_pTextureUiBtn[E_UI_SND_OFF]        = Director::getInstance()->getTextureCache()->addImage("image/menu_ui_soundoff.png");
    
    m_pTextureUiBtn[E_UI_MENU_BTN]       = Director::getInstance()->getTextureCache()->addImage("image/ui_menu.png");
    m_pTextureUiBtn[E_UI_LEFT]           = Director::getInstance()->getTextureCache()->addImage("image/ui_left.png");
    m_pTextureUiBtn[E_UI_RIGHT]          = Director::getInstance()->getTextureCache()->addImage("image/ui_right.png");
    m_pTextureUiBtn[E_UI_USE]            = Director::getInstance()->getTextureCache()->addImage("image/ui_use.png");
    m_pTextureUiBtn[E_UI_JUMP]           = Director::getInstance()->getTextureCache()->addImage("image/ui_up.png");
    
    
    for(int i = E_UI_DEAFUALT + 1; i < E_UI_MAX; i++)
    {
        m_pSprUiBtn[i] = Sprite::createWithTexture(m_pTextureUiBtn[i]);
        m_pSprUiBtn[i]->retain();
    }
    
    log("C_UIMNG :: initUiData() : UI texture, sprites created");
}


void C_UIMNG::initSprites()
{
    
    drawSpriteAtRect(m_pSprUiBtn[E_UI_NEWGAME_ON], Rect(450.0f, 280.0f, 230.0f, 50.0f));
	m_pSprUiBtn[E_UI_NEWGAME_OFF]->setVisible(false);
    m_pSprUiBtn[E_UI_NEWGAME_ON]->setTag(TAG_UI_ON);
    
    drawSpriteAtRect(m_pSprUiBtn[E_UI_NEWGAME_OFF], Rect(450.0f, 280.0f, 230.0f, 50.0f));
    
    m_pSprUiBtn[E_UI_NEWGAME_OFF]->setTag(TAG_UI_OFF);
    
    drawSpriteAtRect(m_pSprUiBtn[E_UI_RESUMEGAME_ON], Rect(500.0f, 190.0f, 230.0f, 50.0f));
	m_pSprUiBtn[E_UI_NEWGAME_OFF]->setVisible(false);
    m_pSprUiBtn[E_UI_RESUMEGAME_ON]->setTag(TAG_UI_ON);
    drawSpriteAtRect(m_pSprUiBtn[E_UI_RESUMEGAME_OFF], Rect(500.0f, 190.0f, 230.0f, 50.0f));
    m_pSprUiBtn[E_UI_RESUMEGAME_OFF]->setTag(TAG_UI_OFF);
    
	drawSpriteAtRect(m_pSprUiBtn[E_UI_SND_ON], Rect(GAME_WIDTH - 60.0f, GAME_HEIGHT - 60.0f, 50.0f, 50.0f));
	m_pSprUiBtn[E_UI_SND_ON]->setTag(TAG_UI_ON);
	drawSpriteAtRect(m_pSprUiBtn[E_UI_SND_OFF], Rect(GAME_WIDTH - 60.0f, GAME_HEIGHT - 60.0f, 50.0f, 50.0f));
	m_pSprUiBtn[E_UI_SND_OFF]->setVisible(false);
	m_pSprUiBtn[E_UI_SND_OFF]->setTag(TAG_UI_OFF);

    drawSpriteAtRect(m_pSprUiBtn[E_UI_MENU_BTN], Rect(0.0f, 480.0f - 59.0f, 139.0f, 59.0f));
    
    drawSpriteAtRect(m_pSprUiBtn[E_UI_LEFT], Rect(10.0f , 16.0f, 120.0f, 65.0f));
    drawSpriteAtRect(m_pSprUiBtn[E_UI_RIGHT], Rect(140.0f, 16.0f, 120.0f, 65.0f));
    
    drawSpriteAtRect(m_pSprUiBtn[E_UI_USE], Rect(540.0f, 16.0f, 120.0f, 65.0f));
    drawSpriteAtRect(m_pSprUiBtn[E_UI_JUMP], Rect(670.0f, 16.0f, 120.0f, 65.0f));
    
    for(int i = E_UI_MENU_BTN; i <= E_UI_JUMP; i++)
    {
        m_pSprUiBtn[i]->setTag(TAG_UI);
        m_pSprUiBtn[i]->setOpacity(100);
    }
    
    log("C_UIMNG :: initSprites() : UI Initialization complete");
}

void C_UIMNG::addMenuUI(cocos2d::Layer* pScene)
{
	for (int i = E_UI_NEWGAME_ON; i <= E_UI_SND_OFF; i++)
    {
        pScene->addChild(m_pSprUiBtn[i], m_pSprUiBtn[i]->getTag());
    }
}

void C_UIMNG::removeMenuUI(cocos2d::Layer* pScene)
{
	for (int i = E_UI_NEWGAME_ON; i <= E_UI_SND_OFF; i++)
    {
        pScene->removeChild(m_pSprUiBtn[i]);
    }
}

void C_UIMNG::addGameSceneUI(cocos2d::Layer* pScene)
{
    for(int i = E_UI_MENU_BTN; i <= E_UI_JUMP; i++)
    {
        pScene->addChild(m_pSprUiBtn[i], m_pSprUiBtn[i]->getTag());
    }
}

void C_UIMNG::removeGameSceneUI(cocos2d::Layer* pScene)
{
    if(!pScene->getChildByTag(TAG_UI))
    {
        log("C_UIMNG :: removeGameSceneUI() : UI has been already removed");
        return;
    }
    
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    
    for(int i = E_UI_MENU_BTN; i <= E_UI_JUMP; i++)
    {
        pScene->removeChild(m_pSprUiBtn[i]);
    }
}

void C_UIMNG::releaseUiData()
{
    for(int i = E_UI_DEAFUALT + 1; i < E_UI_MAX; i++)
    {
        m_pSprUiBtn[i]->release();
        Director::getInstance()->getTextureCache()->removeTexture(m_pTextureUiBtn[i]);
        m_pSprUiBtn[i] = NULL;
    }
    
}

Sprite* C_UIMNG::getSprUiBtn(int eUi)
{
    return m_pSprUiBtn[eUi];
}

const Rect C_UIMNG::getSprUiBtnRect(int eUi)
{   
    return m_pSprUiBtn[eUi]->getBoundingBox();
}