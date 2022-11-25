//
//  NpcWomen.cpp
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 14..
//
//

#include "NpcWoman.h"

USING_NS_CC;

C_NPCWOMAN* C_NPCWOMAN::m_pInstance = NULL;

C_NPCWOMAN::C_NPCWOMAN():
m_pWorldMng(NULL),
m_nState(0),
m_fHorizontalVelocity(0.0f),
m_fHalfBodyHeight(0.0f),
m_fhalfBodyWidth(0.0f),
m_isLeft(false),
m_bAniFlag(false),
m_nCurrentState(0),
m_bDead(false),
m_isRemoteMode(false),
m_rFoot(),
m_bNPC(NULL),
m_pCallBack(NULL),
m_pDeadSequence(NULL)
{
    for(int i = E_NPC_DEFUALT; i < E_NPC_MAX; i++)
    {
        m_pTexture[i] = NULL;
        m_pSprite[i] = NULL;
        m_pAnimation[i] = NULL;
        m_pAnimate[i] = NULL;
        m_pRepeatForever[i] = NULL;
    }
}

void C_NPCWOMAN::createAnimation(E_NPC_STATE eState, int nMaxFrame, int nMaxColumn, int nFrameWidth, int nFrameHeight, float fSpeed)
{
    m_pAnimation[eState] = Animation::create();
    m_pAnimation[eState]->setDelayPerUnit(fSpeed);
    
    animationCreator(m_pAnimation[eState], m_pTexture[eState], nMaxFrame, nMaxColumn, nFrameWidth, nFrameHeight);
    m_pAnimate[eState] = Animate::create(m_pAnimation[eState]);
    m_pAnimate[eState]->retain();
    
    m_pRepeatForever[eState] = RepeatForever::create(m_pAnimate[eState]);
    m_pRepeatForever[eState]->retain();
    
}

void C_NPCWOMAN::createAnimationOneFrame(E_NPC_STATE eState, int nX, int nY, int nWidth, int nHeight)
{
    m_pAnimation[eState] = Animation::create();
    m_pAnimation[eState]->setDelayPerUnit(0.3f);
    
    m_pAnimation[eState]->addSpriteFrameWithTexture(m_pTexture[eState], cocos2d::Rect(nX, nY, nWidth, nHeight));
    
    m_pAnimate[eState] = Animate::create(m_pAnimation[eState]);
    m_pAnimate[eState]->retain();
    
    m_pRepeatForever[eState] = RepeatForever::create(m_pAnimate[eState]);
    m_pRepeatForever[eState]->retain();
    
}

void C_NPCWOMAN::initAnimations()
{
    createAnimationOneFrame(E_STAND, 0, 0, 30, 85);
    
    createAnimation(E_WALK, 2, 2, 30, 85, 0.3f);
    createAnimationOneFrame(E_HAND, 0, 0, 30, 85);
    createAnimation(E_HAND_WALK, 2, 2, 30, 85, 0.3f);
    
    createAnimation(E_WARNING, 2, 2, 30, 85, 0.3f);
    createAnimation(E_DEAD, 2, 2, 70, 80, 1.0f);
    
    m_pCallBack = CallFunc::create(CC_CALLBACK_0(C_NPCWOMAN::setDead, this));
    m_pCallBack->retain();
    
    m_pDeadSequence = Sequence::create(m_pAnimate[E_DEAD], m_pCallBack, NULL);
    m_pDeadSequence->retain();

}


void C_NPCWOMAN::createNPC(Layer* pScene, float fX, float fY, float fVelocity)
{
    m_pSprite[E_STAND]->setPosition(Vec2(fX, fY));
    pScene->addChild(m_pSprite[E_STAND], TAG_NPC);
}

void C_NPCWOMAN::createNPCBodyWithSprite(const cocos2d::Vec2& position)
{
    if(!m_pSprite[E_STAND])
    {
        log("C_NPCWOMAN :: createNPCBodyWithSprite : basic Sprite node is null, sprite body create fail");
        return;
    }
    
    m_pSprite[E_STAND]->setPosition(position);
    m_bNPC = m_pWorldMng->createNPCBodyWithSprite(m_pSprite[E_STAND]);
}

void C_NPCWOMAN::init(C_WORLDMNG* pWorldMng)
{
    m_pWorldMng = pWorldMng;
}

const int C_NPCWOMAN::getNPCState()
{
    return m_nState;
}

void C_NPCWOMAN::controlNPC(C_PLAYER* pPlayer)
{
    float fPlayerPosX = pPlayer->getPositionX();
    
    float fABSBetweenNPCAndPlayer = fabs(m_pSprite[E_STAND]->getPositionX() - fPlayerPosX);
    
    
    if(pPlayer->isItem() && pPlayer->isParty())//player is use item(torch) and party mode
    {
        if(pPlayer->getState() == C_PLAYER::E_HANDFRONT_WALK)
        {
            if(pPlayer->isLeft())
            {
                if(fABSBetweenNPCAndPlayer <= 20.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(- (m_fHorizontalVelocity - 1.0f), 0));
                }
                else if(m_isLeft && fABSBetweenNPCAndPlayer >= 23.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(-m_fHorizontalVelocity, 0));
                }
                
            }
            else
            {
                
                if(fABSBetweenNPCAndPlayer <= 20.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity - 1.0f, 0));
                }
                else if(!m_isLeft && fABSBetweenNPCAndPlayer >= 23.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity, 0));
                }
            }
        }
        
    }
    else if(!pPlayer->isItem() && pPlayer->isParty())//player is NOT use item(torch) and party mode
    {
        if(pPlayer->getState() == C_PLAYER::E_P_STATE::E_HANDBACK_WALK)
        {
            if(pPlayer->isLeft())
            {
                if(fABSBetweenNPCAndPlayer <= 20.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(- (m_fHorizontalVelocity - 1.0f), 0));
                }
                else if(m_isLeft && fABSBetweenNPCAndPlayer >= 23.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(-m_fHorizontalVelocity, 0));
                }
                
            }else
            {
                
                if(fABSBetweenNPCAndPlayer <= 20.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity - 1.0f, 0));
                }
                else if(!m_isLeft && fABSBetweenNPCAndPlayer >= 23.0f)
                {
                    m_bNPC->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity, 0));
                }
            }
        }
    }

}

void C_NPCWOMAN::controlFSM(C_PLAYER* pPlayer, C_DEADZONE* pDeadZone, cocos2d::Layer* pScene)
{
    m_nCurrentState = m_nState;
    
    if(!pPlayer->isItem())//player NOT use item(torch) mode
    {
        if(pPlayer->getState() == C_PLAYER::E_HANDBACK || pPlayer->getState() == C_PLAYER::E_HANDFRONT)
        {
            m_nState = E_NPC_STATE::E_HAND;
        }
        else if(pPlayer->getState() == C_PLAYER::E_HANDBACK_WALK || pPlayer->getState() == C_PLAYER::E_HANDFRONT_WALK)
        {
            m_nState = E_NPC_STATE::E_HAND_WALK;
        }
        else if(pScene->getChildByTag(TAG_DEADZONE) && m_pSprite[E_STAND]->getPositionX() < pDeadZone->getDeadZoneLength())
        {
            if(pDeadZone->getDeadZoneLength() - m_pSprite[E_STAND]->getPositionX() >= 80.0f)
            {
                m_nState = E_DEAD;
            }
            else
            {
                m_nState = E_WARNING;
            }
        }
        else
        {
            m_nState = E_STAND;
        }
    }
    else//player use item(torch) mode
    {
        if(pPlayer->isParty())
        {
            if(pPlayer->getState() == C_PLAYER::E_HANDFRONT)
            {
                m_nState = E_HAND;
            }
            else if(pPlayer->getState() == C_PLAYER::E_HANDFRONT_WALK)
            {
                m_nState = E_HAND_WALK;
            }
        }
        else if(pScene->getChildByTag(TAG_DEADZONE) && m_pSprite[E_STAND]->getPositionX() < pDeadZone->getDeadZoneLength())
        {
            if(pDeadZone->getDeadZoneLength() - m_pSprite[E_STAND]->getPositionX() >= 100.0f)
            {
                m_nState = E_DEAD;
            }
            else
            {
                m_nState = E_WARNING;
            }
        }
        else
        {
            m_nState = E_NPC_STATE::E_STAND;
        }

    }

}

void C_NPCWOMAN::drawNPC(C_PLAYER* pPlayer)
{
    
    if(pPlayer->getPositionX() < m_bNPC->GetPosition().x * PTM_RATIO)
    {
        m_pSprite[E_STAND]->setFlippedX(true);
        m_isLeft = true;
    }
    else
    {
        m_pSprite[E_STAND]->setFlippedX(false);
        m_isLeft = false;
    }
    
    if(!m_bAniFlag)
    {
        if(m_nState != E_DEAD)
        {
            m_pSprite[E_STAND]->runAction(m_pRepeatForever[m_nState]);
        }
        else
        {
            m_pSprite[E_STAND]->runAction(m_pDeadSequence);
        }
        
        m_bAniFlag = true;
        return;
        
    }
    
    if(m_nCurrentState != m_nState)
    {
        m_bAniFlag = false;
        m_pSprite[E_STAND]->stopAllActions();
    }

}

void C_NPCWOMAN::remoteNPC(float fMoveToPosX)
{
    m_nCurrentState = m_nState;
    
    float fNPCPosX = m_pSprite[E_STAND]->getPositionX();
    
    if((int)fNPCPosX >= fMoveToPosX - 7.0f && (int)fNPCPosX <= fMoveToPosX + 7.0f)
    {
        m_nState = E_STAND;
        m_bNPC->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    }
    else
    {
        //NPC left to right
        if(fNPCPosX < fMoveToPosX)
        {
            m_pSprite[E_STAND]->setFlippedX(false);
            m_nState = E_WALK;
            m_bNPC->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity, 0.0f));
        }
        //NPC right to left
        else if(fNPCPosX > fMoveToPosX)
        {
            m_pSprite[E_STAND]->setFlippedX(true);
            m_nState = E_WALK;
            m_bNPC->SetLinearVelocity(b2Vec2(-m_fHorizontalVelocity, 0.0f));
        }
        
    }
    
    
    if(!m_bAniFlag)
    {
        m_pSprite[E_STAND]->runAction(m_pRepeatForever[m_nState]);
        
        m_bAniFlag = true;
        return;
    }
    
    if(m_nCurrentState != m_nState)
    {
        m_bAniFlag = false;
        m_pSprite[E_STAND]->stopAllActions();
        
    }
}

void C_NPCWOMAN::removeAndinitNPC(cocos2d::Layer *pScene)
{
    if(!m_pSprite[E_STAND])
    {
        initSprites();
        return;
    }
    
    
    pScene->removeChild(m_pSprite[E_STAND], false);
    
    if(m_bNPC)
    {
        C_WORLDMNG::g_world->DestroyBody(m_bNPC);
        m_bNPC = NULL;
    }
    
    m_pSprite[E_STAND]->stopAllActions();
    m_nState = E_STAND;
    m_bDead = false;
    m_isRemoteMode = false;
    
    m_pSprite[E_STAND]->release();
    m_pSprite[E_STAND] = NULL;
    initSprites();
    log("C_NPCWOMAN :: removeNPC() : NPC removed from Scene");
    
}

void C_NPCWOMAN::stopAction()
{
    m_bAniFlag = false;
    m_pSprite[E_STAND]->stopAllActions();
    m_pSprite[E_STAND]->runAction(m_pRepeatForever[E_STAND]);
    m_bAniFlag = true;
}

void C_NPCWOMAN::setPositionBody(float fX, float fY)
{
    if(!m_pSprite[E_STAND])
    {
        log("C_NPCWOMAN :: setPositionBody() : main Sprite is not created, setPosition Fails");
        return;
    }
    
    m_pSprite[E_STAND]->setPosition(Vec2(fX, fY));
    m_bNPC->SetTransform(b2Vec2(fX  / PTM_RATIO, fY / PTM_RATIO), 0);
}

void C_NPCWOMAN::setNPCFlippedX(bool bFflippedX)
{
    m_pSprite[E_STAND]->setFlippedX(bFflippedX);
}

const float C_NPCWOMAN::getPositionBodyX()
{
    float _fPlayerPosX = m_bNPC->GetPosition().x;
    
    _fPlayerPosX = _fPlayerPosX * PTM_RATIO;
    
    return _fPlayerPosX;
}

const float C_NPCWOMAN::getPositionX()
{
    return m_pSprite[E_STAND]->getPositionX();
}


Rect C_NPCWOMAN::getPositionFoot()
{
    Rect _PlayerRect = m_pSprite[E_STAND]->getBoundingBox();
    
    float _fplayerHeight = _PlayerRect.size.height;
    
    _fplayerHeight = (_fplayerHeight / 8);
    
    m_rFoot.setRect(_PlayerRect.origin.x + 0.2f, _PlayerRect.origin.y, _PlayerRect.size.width - 0.2f, _fplayerHeight);
    
    return m_rFoot;
}

cocos2d::Sprite* C_NPCWOMAN::getNPCSprite()
{
    if(!m_pSprite[E_STAND])
    {
        log("C_NPCWOMAN :: getNPCSprite() : main sprite is null, return sprite fails");
        return NULL;
    }
    
    return m_pSprite[E_STAND];
}

b2Body* C_NPCWOMAN::getNPCBody()
{
    return m_bNPC;
}

const float C_NPCWOMAN::getHalfBodyHeight()
{
    return m_fHalfBodyHeight;
}

void C_NPCWOMAN::runDead()
{
    m_pSprite[E_STAND]->stopAllActions();
    m_nState = E_DEAD;
    m_pSprite[E_STAND]->runAction(m_pDeadSequence);
    
}

void C_NPCWOMAN::setDead()
{
    m_bDead = true;
}

const bool C_NPCWOMAN::isDead()
{
    return m_bDead;
}

void C_NPCWOMAN::setRemoteMode()
{
    m_isRemoteMode = true;
}

const bool C_NPCWOMAN::isRemoteMode()
{
    return m_isRemoteMode;
}

void C_NPCWOMAN::loadTexture()
{
    m_pTexture[E_NPC_STATE::E_STAND] = Director::getInstance()->getTextureCache()->addImage("image/npc_walone.png");
    m_pTexture[E_NPC_STATE::E_WALK] = Director::getInstance()->getTextureCache()->addImage("image/npc_wwalkalone.png");
    m_pTexture[E_NPC_STATE::E_HAND] = Director::getInstance()->getTextureCache()->addImage("image/npc_wparty.png");
    m_pTexture[E_NPC_STATE::E_HAND_WALK] = Director::getInstance()->getTextureCache()->addImage("image/npc_wparty.png");
    m_pTexture[E_NPC_STATE::E_WARNING] = Director::getInstance()->getTextureCache()->addImage("image/npc_wdeadzone.png");
    m_pTexture[E_NPC_STATE::E_DEAD] = Director::getInstance()->getTextureCache()->addImage("image/npc_wd.png");
}

void C_NPCWOMAN::releaseTexture()
{
    for(int i = 0; i < E_NPC_STATE::E_NPC_MAX; i++)
    {
        if(m_pTexture[i])
        {
            Director::getInstance()->getTextureCache()->removeTexture(m_pTexture[i]);
        }
    }
}

void C_NPCWOMAN::initSprites()
{
    m_pSprite[E_STAND] = Sprite::createWithTexture(m_pTexture[E_NPC_STATE::E_STAND], Rect(0, 0, 34, 85));
    m_pSprite[E_STAND]->setTag(TAG_NPC);
    m_pSprite[E_STAND]->retain();
    
    m_fHalfBodyHeight = (m_pSprite[E_STAND]->getBoundingBox().size.height / 2) + 0.5f;
    m_fhalfBodyWidth = (m_pSprite[E_STAND]->getBoundingBox().size.width / 2);
}

void C_NPCWOMAN::releaseSprites()
{
    for(int i = E_NPC_DEFUALT; i < E_NPC_MAX; i++)
    {
        if(m_pSprite[i])
        {
            m_pSprite[i]->release();
        }
    }
}

void C_NPCWOMAN::releaseAnimation()
{
    for(int i = E_NPC_DEFUALT; i < E_NPC_MAX; i++)
    {
        if(m_pAnimate[i])
        {
            m_pAnimate[i]->release();
        }
        if(m_pAnimation[i])
        {
            m_pAnimation[i]->release();
        }
    }
}

void C_NPCWOMAN::setHorizontalVelocity(float fVelocity)
{
    m_fHorizontalVelocity = fVelocity;
}

const float C_NPCWOMAN::getHorizontalVelocity()
{
    return m_fHorizontalVelocity;
}

void C_NPCWOMAN::releaseNPC(cocos2d::Layer *pScene)
{
    pScene->removeChild(m_pSprite[E_STAND], false);
    
    m_nState = E_NPC_DEFUALT;
    
    releaseAnimation();
    releaseSprites();
    releaseTexture();

}

C_NPCWOMAN* C_NPCWOMAN::getInstance()
{
    return m_pInstance;
}

void C_NPCWOMAN::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_NPCWOMAN;
        log("C_NPCWOMAN :: NpcWomen Instance created");
    }
}

void C_NPCWOMAN::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_NPCWOMAN :: NpcWomen Instance released");
    }
}

