#include "GamePlayScene.h"
#include "MenuScene.h"
#include "AppMacros.h"
#include "Player.h"
#include "Terrain.h"
#include "StageMng.h"
#include "WorldMng.h"
#include "UiMng.h"
#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"


USING_NS_CC;

GamePlayScene::GamePlayScene():
m_SceneMenu(NULL)
{
    for(int i = E_BTN_DEFUALT; i < E_BTN_MAX; i++)
    {
        m_rBtn[i] = Rect();
        m_bBtn[i] = false;
    }
}

Scene* GamePlayScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GamePlayScene::create();

    scene->addChild(layer);

    return scene;
}

void GamePlayScene::onEnter()
{
    Layer::onEnter();
    
//for windows key listener setting

    
    auto keylistener = EventListenerKeyboard::create();
    keylistener->onKeyPressed = CC_CALLBACK_2(GamePlayScene::onKeyPressed, this);
    keylistener->onKeyReleased = CC_CALLBACK_2(GamePlayScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

    
    auto listener = EventListenerTouchAllAtOnce::create();
    
    listener->onTouchesBegan = CC_CALLBACK_2(GamePlayScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GamePlayScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GamePlayScene::onTouchesEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    C_WORLDMNG::g_world->SetContactListener(C_WORLDMNG::getInstance());

    log("GamePlayScene onEnter");
}

void GamePlayScene::onExit()
{   
    
    C_STAGEMNG::getInstance()->releaseStageToScene(this);

    Layer::onExit();
    
    log("GamePlayScene onExit");
}

bool GamePlayScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->removeAllChildrenWithCleanup(true);
    
    C_UIMNG *pUIMng = C_UIMNG::getInstance();
    m_rBtn[E_LEFT]  = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_LEFT);
    m_rBtn[E_RIGHT] = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_RIGHT);
    m_rBtn[E_USE]   = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_USE);
    m_rBtn[E_JUMP]  = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_JUMP);
    m_rBtn[E_MENU]  = pUIMng->getSprUiBtnRect(C_UIMNG::E_UI_MENU_BTN);
    
    C_PLAYER* pPlayer = C_PLAYER::getInstance();
    Sprite* pPlayerSpr = NULL;
    
    if(pPlayer->getSpriteWithType(C_PLAYER::E_STAND))
    {
        pPlayerSpr = pPlayer->getSpriteWithType(C_PLAYER::E_STAND);
        this->addChild(pPlayerSpr, TAG_PLAYER);
        pPlayer->createPlayerBodyWithSprite(Vec2(0.0f, 2000.0f));
        log("GamePlayScene::Player Sprite Mode Activate");
    }
    
    
    pUIMng->addGameSceneUI(this);
    
    int nStage = C_STAGEMNG::getInstance()->getStageNum();
    
    C_STAGEMNG::getInstance()->setStageToScene(this, nStage);
    
    this->schedule(schedule_selector(GamePlayScene::tick));
    
    createDebugMode(IS_DEBUG);

    return true;
}

void GamePlayScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    //This override function for Box2d Debug Mode draw
    //Not use in release version renderring
    
    Layer::draw(renderer, transform, flags);
    Director* director = Director::getInstance();
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION );
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    C_WORLDMNG::getInstance()->getB2World()->DrawDebugData();

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void GamePlayScene::tick(float dt)
{
    C_WORLDMNG::g_world->Step(dt, 8, 3);
    
    C_PLAYER* pPlayer = C_PLAYER::getInstance();
    
    pPlayer->controlPlayerWithSprite(m_bBtn);
    pPlayer->controlFSM(m_bBtn, this);
    pPlayer->drawPlayer();
#if(defined _WIN32) || (defined _W64)
#else
	pPlayer->playSoundPlayer();
#endif
    
    
    C_STAGEMNG::getInstance()->checkEventToScene(this);

    for(b2Body *b = C_WORLDMNG::g_world->GetBodyList(); b; b= b->GetNext())
    {
        if(b->GetUserData() != NULL)
        {
            Sprite* spr = (Sprite*)b->GetUserData();
          
            spr->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
        }
    }
    
    //sometimes, #define macro is not working.
    bool isDebug = IS_DEBUG;
    updateDebugMode(isDebug);

}

void GamePlayScene::changeScene(Ref *sender)
{
    
    if(!m_SceneMenu)
    {
        //m_SceneMenu = TransitionFade::create(1.0, MenuScene::createScene());
        //use releaseVersion!
        m_SceneMenu = MenuScene::createScene();
        log("GamePlayScene :: MenuScene Created");
    }
    
    Director::getInstance()->replaceScene(m_SceneMenu);
    
}

bool GamePlayScene::getBtn(E_BTN eBtn)
{
    return m_bBtn[eBtn];
}

void GamePlayScene::createDebugMode(bool isDEBUG)
{
    
    if(isDEBUG == 0)
        return;
    
    auto label = Label::createWithSystemFont("dddfdfdfdfdfdfddf.", "Thonburi", 10, Size(150, 50), TextHAlignment::CENTER);
    
    label->setTag(TAG_DEBUG_TEXT);
    
    this->addChild(label);   
}

/*
 *--------------------------------------------------------
 *DebugMode Function : Do not use release version.
 *1.All Sprite's Alpha value 255(max)->100
 *2.Player X,Y Position smart drawing
 *--------------------------------------------------------
 */
void GamePlayScene::updateDebugMode(bool isDEBUG)
{
    if(isDEBUG == 0)
    {
        return;
    }
    
    
    
    Vector<Node*> &node = this->getChildren();
    for(auto &item : node)
    {
        auto label = this->getChildByTag(TAG_DEBUG_TEXT);
        auto _player = this->getChildByTag(TAG_PLAYER);
        
        //All Sprite Alpha value 255 to 100
        if(!item->getChildByTag(TAG_FADELAYER))
        {
            item->setOpacity(100);
        }
        
        
        float fSprPosX = item->getPositionX();
        float fSprPosY = item->getPositionY();
        
        int nPosX = (int)fSprPosX;
        int nPosY = (int)fSprPosY;
        
        char _strPosData[256] = {0};
        sprintf(_strPosData, "X : %d, Y : %d", nPosX, nPosY);
        
        if(item == _player)
        {
            ((Label*)label)->setString(_strPosData);
        }
        
        if(fSprPosX >  designResolutionSize.width)
        {
            fSprPosX = designResolutionSize.width - 50.0f;
        }
        
        if(fSprPosX < 0)
        {
            fSprPosX = 0 + 50.0f;
        }
        
        if(fSprPosY > designResolutionSize.height)
        {
            fSprPosY = designResolutionSize.height - 30.0f;
        }
        
        if(fSprPosY < 0)
        {
            fSprPosY = 0 + 30.0f;
        }
        
        if(item == _player)
        {
            label->setPosition(Vec2(fSprPosX, fSprPosY));
        }
        
    }
    

}



void GamePlayScene::onTouchesBegan(const std::vector<Touch*> &touches, Event *event)
{
    
    float fX = 0.0f;
    float fY = 0.0f;

    for(auto &item : touches)
    {
        
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
        bool isLeft  = m_rBtn[E_LEFT].containsPoint(Vec2(fX, fY));
        bool isRight = m_rBtn[E_RIGHT].containsPoint(Vec2(fX, fY));
        bool isJump  = m_rBtn[E_JUMP].containsPoint(Vec2(fX, fY));
        bool isUse   = m_rBtn[E_USE].containsPoint(Vec2(fX, fY));
        
        if(isLeft)
        {
            m_bBtn[E_LEFT] = true;
            m_bBtn[E_RIGHT] = false;
        }
        else if(isRight)
        {
            m_bBtn[E_RIGHT] = true;
            m_bBtn[E_LEFT] = false;
        }
        
        if(isJump)
        {
            m_bBtn[E_JUMP] = true;
        }
        

        if(m_rBtn[E_MENU].containsPoint(Vec2(fX, fY)))
        {
            changeScene(this);
        }
        
        if(isUse)
        {
            m_bBtn[E_USE] = true;
        }
        else
        {
            m_bBtn[E_USE] = false;
        }
        
    }
    
}

void GamePlayScene::onTouchesMoved(const std::vector<Touch*> &touches, Event *event)
{
    
    float fX = 0.0f;
    float fY = 0.0f;
    
    for(auto &item : touches)
    {
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
        bool isLeft = m_rBtn[E_LEFT].containsPoint(Vec2(fX, fY));
        bool isRight = m_rBtn[E_RIGHT].containsPoint(Vec2(fX, fY));
        bool isJump = m_rBtn[E_JUMP].containsPoint(Vec2(fX, fY));
        bool isUse = m_rBtn[E_USE].containsPoint(Vec2(fX, fY));

        if(isLeft)
        {
            m_bBtn[E_LEFT] = true;
            m_bBtn[E_RIGHT] = false;
            break;
        }
        else if(isRight)
        {
            m_bBtn[E_RIGHT] = true;
            m_bBtn[E_LEFT] = false;
            break;
        }

        if(isJump)
        {
            m_bBtn[E_JUMP] = true;
        }


        if(!isLeft && !isRight && !isUse && !isJump)
        {
        	m_bBtn[E_RIGHT] = false;
        	m_bBtn[E_LEFT] = false;
            m_bBtn[E_JUMP] = false;
            m_bBtn[E_USE] = false;
        }
        
    }
    
}


void GamePlayScene::onTouchesEnded(const std::vector<Touch*> &touches, Event *event)
{
    
    float fX = 0.0f;
    float fY = 0.0f;
    
    for(auto &item : touches)
    {
        fX = item->getLocation().x;
        fY = item->getLocation().y;
        
        if(m_rBtn[E_LEFT].containsPoint(Vec2(fX, fY)))
        {
            m_bBtn[E_LEFT] = false;
        }
        else if(m_rBtn[E_RIGHT].containsPoint(Vec2(fX, fY)))
        {
            m_bBtn[E_RIGHT] = false;
        }
        
        m_bBtn[E_JUMP] = false;
        m_bBtn[E_USE] = false;
    }

}


void GamePlayScene::onTouchesCancelled(const std::vector<Touch*> &touches, Event *event)
{
    log("onTouchesCancelled");
    
    
    onTouchesEnded(touches, event);
    
}

void GamePlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
#if(defined _WIN32) || (defined _W64)

    if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        m_bBtn[E_LEFT] = true;
		m_bBtn[E_RIGHT] = false;
    }
	else if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        m_bBtn[E_RIGHT] = true;
		m_bBtn[E_LEFT] = false;
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        m_bBtn[E_JUMP] = true;
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        m_bBtn[E_USE] = true;
    }
#endif
}

void GamePlayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
#if(defined _WIN32) || (defined _W64)
    if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        m_bBtn[E_LEFT] = false;
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        m_bBtn[E_RIGHT] = false;
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        m_bBtn[E_JUMP] = false;
    }
    
    if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        m_bBtn[E_USE] = false;
    }
#else

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE || keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}

#endif
    
}

