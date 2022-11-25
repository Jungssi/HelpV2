/*
 * MenuScene.cpp
 *
 *  Created on: 2014. 9. 30.
 *      Author: jungyonghoon
 */

#include "MenuScene.h"
#include "GamePlayScene.h"
#include "StageMng.h"
#include "AppMacros.h"
#include "UiMng.h"
#include "SoundMng.h"

USING_NS_CC;

MenuScene::MenuScene():
m_isSndOn(false),
m_isNew(false),
m_isResume(false),
m_SceneGamePlay(NULL),
m_pTouchListener(NULL)
{
    
}

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();
	scene->addChild(layer);
    
	return scene;
}

void MenuScene::onEnter()
{
    Layer::onEnter();
    
    m_pTouchListener = EventListenerTouchAllAtOnce::create();
    
    m_pTouchListener->onTouchesBegan = CC_CALLBACK_2(MenuScene::onTouchesBegan, this);
    m_pTouchListener->onTouchesMoved = CC_CALLBACK_2(MenuScene::onTouchesMoved, this);
    m_pTouchListener->onTouchesEnded = CC_CALLBACK_2(MenuScene::onTouchesEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pTouchListener, this);
    
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	if (C_STAGEMNG::getInstance()->isAllClear())
	{
		C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU_CLEAR);
	}
	else
	{
		C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU);
	}
    
    
    log("MenuScene onEnter");
}

void MenuScene::onExit()
{

    this->removeAllChildrenWithCleanup(true);
    
    Layer::onExit();
    log("MenuScene onExit");
}

bool MenuScene::init()
{
    if( !Layer::init() )
	{
		return false;
	}

	this->setKeypadEnabled(true);
	

    initBG();
    initLabel();
    C_UIMNG* pUIMng = C_UIMNG::getInstance();
    pUIMng->addMenuUI(this);
    
	m_isSndOn = UserDefault::getInstance()->getBoolForKey("bool_snd_onoff");

    this->schedule(schedule_selector(MenuScene::scheduleCallback),0.1f);
    
    log("MenuScene : inited");
	return true;
}

void MenuScene::changeScene()
{
    C_SOUNDMNG::getInstance()->stopBG();

    if(!m_SceneGamePlay)
    {
        m_SceneGamePlay = TransitionFade::create(1.0, GamePlayScene::createScene());
        log("MenuScene :: GamePlayScene Created");
    }

	Director::getInstance()->pushScene(m_SceneGamePlay);
}

void MenuScene::initBG()
{
	Sprite* pSprBg[6];

    ParallaxNode* pParallaxBG = ParallaxNode::create();
    
    char _cStage[128];
    
    for(int i = 0; i < 6; i++)
    {
        sprintf(_cStage, "image/bg_%02d.png", i + 1);
        pSprBg[i] = Sprite::create(_cStage);
        pSprBg[i]->getTexture()->setAliasTexParameters();
        pSprBg[i]->setAnchorPoint(Vec2::ZERO);
        pSprBg[i]->setOpacity(0);
        pSprBg[i]->setTag(TAG_BG_ALPHA);
        pParallaxBG->addChild(pSprBg[i], 1, Vec2(1.0f, 0.0f), Vec2(GAME_WIDTH * i, 0.0f));
    }

    pParallaxBG->setTag(TAG_BG);
    
    MoveBy* pMove = MoveBy::create(100.0f, Vec2(-(GAME_WIDTH * 5), 0.0f));
    RepeatForever* pRepeatAction = RepeatForever::create(pMove);
    
    pParallaxBG->runAction(pRepeatAction);
    
    this->addChild(pParallaxBG);
}

void MenuScene::initLabel()
{

    auto labelTeamName = Label::createWithSystemFont("   Team_Girin", "Thonburi", 18, Size(designResolutionSize.width, 130), TextHAlignment::LEFT);
    labelTeamName->setPosition(Vec2(0, 0));
    labelTeamName->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelTeamName);

    auto labelDesigner = Label::createWithSystemFont("   Designer : earl", "Thonburi", 18, Size(designResolutionSize.width, 110), TextHAlignment::LEFT);
    labelDesigner->setPosition(Vec2(0, 0));
    labelDesigner->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelDesigner);
    
    auto labelProgrammer = Label::createWithSystemFont("   Programmer : Jungssi", "Thonburi", 18, Size(designResolutionSize.width, 90), TextHAlignment::LEFT);
    labelProgrammer->setPosition(Vec2(0, 0));
    labelProgrammer->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelProgrammer);
    

    
    
    auto labelCopyRight = Label::createWithSystemFont("Copyright 2014. Team_Girin all rights reserved.", "Thonburi", 20, Size(designResolutionSize.width, 45), TextHAlignment::CENTER);
    labelCopyRight->setPosition(Vec2(0, 0));
    labelCopyRight->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelCopyRight);
    
    auto labelPoweredBy = Label::createWithSystemFont("Powered By Cocos2D-X, Box2D", "Thonburi", 13, Size(designResolutionSize.width, 20), TextHAlignment::CENTER);
    labelPoweredBy->setPosition(Vec2(0, 0));
    labelPoweredBy->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelPoweredBy);
    
    auto labelVersion = Label::createWithSystemFont("Version : 2.000v", "Thonburi", 15, Size(designResolutionSize.width, 20), TextHAlignment::RIGHT);
    labelVersion->setPosition(Vec2(0, 0));
    labelVersion->setAnchorPoint(Vec2(0, 0));
    this->addChild(labelVersion);
}

void MenuScene::scheduleCallback(float delta)
{
    
    auto BGpic = this->getChildByTag(TAG_BG);
    auto BGpics = BGpic->getChildren();
    
    float fBGPosX = BGpic->getPositionX();
    float fLimit = -(GAME_WIDTH * 3);
    
    if(fBGPosX >= fLimit)
    {
        for(auto pic : BGpics)
        {
            GLubyte nAlpha = pic->getOpacity();
            if(nAlpha < 255 - 7)
            {
                pic->setOpacity(nAlpha + 7);
            }
        }
    }
    else if(fBGPosX < fLimit && fBGPosX > fLimit - GAME_WIDTH)
    {
        for(auto pic : BGpics)
        {
            GLubyte nAlpha = pic->getOpacity();
            if(nAlpha >= 0)
            {
                pic->setOpacity(nAlpha - 3);
                
                if(nAlpha < 5)
                {
                    pic->setOpacity(0);
                    BGpic->setPosition(Vec2::ZERO);
                }
            }
        }
    }
    
    
 
    C_UIMNG* pUIMng = C_UIMNG::getInstance();

	pUIMng->getSprUiBtn(C_UIMNG::E_UI_SND_OFF)->setVisible(!m_isSndOn);
    
	pUIMng->getSprUiBtn(C_UIMNG::E_UI_NEWGAME_OFF)->setVisible(!m_isNew);
	pUIMng->getSprUiBtn(C_UIMNG::E_UI_RESUMEGAME_OFF)->setVisible(!m_isResume);
    
}

void MenuScene::onTouchesBegan(const std::vector<Touch*> &touches, Event *event)
{
    
    float fX = 0.0f;
    float fY = 0.0f;
    
    C_UIMNG *pUIMng = C_UIMNG::getInstance();

	Rect rSndIcon = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_SND_OFF);
    Rect rNewGame = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_NEWGAME_OFF);
    Rect rNewResume = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_RESUMEGAME_OFF);
    
    for(auto &item : touches)
    {
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
		if (rSndIcon.containsPoint(Vec2(fX, fY)))
		{
			m_isSndOn = !m_isSndOn;
			C_SOUNDMNG::getInstance()->setSoundToggle();
		}

		m_isNew = rNewGame.containsPoint(Vec2(fX, fY));
        m_isResume = rNewResume.containsPoint(Vec2(fX, fY));
        
    }
    
}


void MenuScene::onTouchesMoved(const std::vector<Touch*> &touches, Event *event)
{
    float fX = 0.0f;
    float fY = 0.0f;
    
    C_UIMNG *pUIMng = C_UIMNG::getInstance();
    Rect rNewGame = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_NEWGAME_OFF);
    Rect rNewResume = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_RESUMEGAME_OFF);
    
    
    for(auto &item : touches)
    {
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
		m_isNew = rNewGame.containsPoint(Vec2(fX, fY));
        
		m_isResume = rNewResume.containsPoint(Vec2(fX, fY));
               
    }
}


void MenuScene::onTouchesEnded(const std::vector<Touch*> &touches, Event *event)
{
    log("onTouchesEnded");

    float fX = 0.0f;
    float fY = 0.0f;
    
    C_UIMNG *pUIMng = C_UIMNG::getInstance();
    Rect rNewGame = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_NEWGAME_OFF);
    Rect rNewResume = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_RESUMEGAME_OFF);
    
    m_isNew = false;
    m_isResume = false;
    
    for(auto &item : touches)
    {
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
        if(rNewGame.containsPoint(Vec2(fX, fY)))
        {
            newGame();
        }
        
        if(rNewResume.containsPoint(Vec2(fX, fY)))
        {
            LoadGame();
        }
        
    }
}


void MenuScene::onTouchesCancelled(const std::vector<Touch*> &touches, Event *event)
{
    log("onTouchesCancelled");
    
    onTouchesEnded(touches, event);
    
}


void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		
		Director::getInstance()->end();

	}
}



void MenuScene::newGame()
{
    C_STAGEMNG* pStageMng = C_STAGEMNG::getInstance();
    
    if(IS_DEBUG)
    {
        pStageMng->setStageNum(DEBUG_STAGE);
        changeScene();
        return;
    }
    
    int nStageNum = pStageMng->getStageNumFromSaveData();
    
    
    if(nStageNum <= 1)
    {
        pStageMng->setStageNum(1);
        changeScene();
    }
    else
    {
        Node* pMenuTemp = this->getChildByTag(TAG_MENU_DIALOG_BOX);
        
        if(!pMenuTemp)
        {
            Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
            

            DrawNode* pBlackBGDrawNode = DrawNode::create();
            
            Vec2 rectangle[4];
            rectangle[0] = Vec2(0.0f, 0.0f);
            rectangle[1] = Vec2(GAME_WIDTH , 0.0f);
            rectangle[2] = Vec2(GAME_WIDTH, 170.0f);
            rectangle[3] = Vec2(0.0f, 170.0f);
            
            Color4F tmpColor4F(0, 0, 0, 70);
            
            pBlackBGDrawNode->drawPolygon(rectangle, 4, tmpColor4F, 0, tmpColor4F);
            pBlackBGDrawNode->setPosition(-(GAME_WIDTH / 2), -(GAME_HEIGHT / 7));
            
            Node* pMenuNode = Node::create();
            
            Label* pLabelMenuTitle = Label::createWithSystemFont("Saved data will be deleted, Are you sure?", "Thonburi", 25, Size(designResolutionSize.width, 50), TextHAlignment::CENTER);
            pLabelMenuTitle->setPosition(Vec2(0, 50));
            
            MenuItemFont* pBtnYES = MenuItemFont::create("YES", CC_CALLBACK_0(MenuScene::callBackNewGameYES, this));
            pBtnYES->setPosition(Vec2(-100, -10));
            MenuItemFont* pBtnNo = MenuItemFont::create("NO", CC_CALLBACK_0(MenuScene::callBackNewGameNO, this));
            pBtnNo->setPosition(Vec2(100, -10));
            
            Menu* pMenu = Menu::create(pBtnYES, pBtnNo, nullptr);
            pMenu->setPosition(0.0f, 0.0f);
            pMenuNode->setTag(TAG_MENU_DIALOG_BOX);
            
            pMenuNode->addChild(pBlackBGDrawNode);
            pMenuNode->addChild(pLabelMenuTitle);
            pMenuNode->addChild(pMenu);
            
            pMenuNode->setPosition(Vec2(GAME_WIDTH / 2, GAME_HEIGHT / 2));
            this->addChild(pMenuNode, TAG_MENU_DIALOG_BOX);
        }
    }

    
    
}

void MenuScene::callBackNewGameYES()
{
    C_STAGEMNG::getInstance()->setStageNum(1);
    changeScene();
}

void MenuScene::callBackNewGameNO()
{
    auto pMenuNode = this->getChildByTag(TAG_MENU_DIALOG_BOX);
    this->removeChild(pMenuNode);
    
    m_pTouchListener = EventListenerTouchAllAtOnce::create();
    
    m_pTouchListener->onTouchesBegan = CC_CALLBACK_2(MenuScene::onTouchesBegan, this);
    m_pTouchListener->onTouchesMoved = CC_CALLBACK_2(MenuScene::onTouchesMoved, this);
    m_pTouchListener->onTouchesEnded = CC_CALLBACK_2(MenuScene::onTouchesEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_pTouchListener, this);
    
}

void MenuScene::LoadGame()
{
    C_STAGEMNG* pStageMng = C_STAGEMNG::getInstance();
    int nStageNum = pStageMng->getStageNumFromSaveData();
    
    if(nStageNum == 0)
    {
        pStageMng->setStageNum(1);
    }
    else
    {
        pStageMng->setStageNum(nStageNum);
    }
    
    changeScene();
    return;
}
