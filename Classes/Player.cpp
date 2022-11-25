/*
 * PlayerMng.cpp
 *
 *  Created on: 2014. 10. 1.
 *      Author: jungyonghoon
 */

#include "Player.h"
#include "NpcWoman.h"
#include "ObjectMng.h"
#include "SoundMng.h"


USING_NS_CC;

C_PLAYER* C_PLAYER::m_pInstance = NULL;

C_PLAYER::C_PLAYER():
m_pWorldMng(NULL),
m_isRemoteMode(false),
m_isRayed(false),
m_bAniFlag(false),
m_isParty(false),
m_isItem(false),
m_isLeft(false),
m_bPlayer(NULL),
m_rPlayer(),
m_rFoot(),
m_fHorizontalVelocity(0.0f),
m_fHalfBodyHeight(0.0f),
m_fhalfBodyWidth(0.0f),
m_nState(0),
m_nCurrentState(0),
m_nStageType(0),
m_nEffectIndex(0),
m_bSndFlag(false)
{
    for(int i = 0; i < E_P_STATE_MAX; i++)
    {
        m_pTexture[i] = NULL;
        m_pSprite[i] = NULL;
        m_pAnimation[i] = NULL;
        m_pAnimate[i] = NULL;
        m_pRepeatForever[i] = NULL;
    }
    
    for(int i = 0; i < E_S_TYPE_MAX; i++)
    {
        m_pPlayEffect[i] = NULL;
    }
    
    m_pPlayEffect[E_STAGE_NORMAL] = &C_PLAYER::playEffectWalkNormal;
    m_pPlayEffect[E_STAGE_CAVE] = &C_PLAYER::playEffectWalkCave;
}


void C_PLAYER::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_PLAYER;
        log("C_PLAYER :: Player Instance created");
    }
}

void C_PLAYER::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_PLAYER :: Player Instance released");
    }
}

C_PLAYER* C_PLAYER::getInstance()
{
    return m_pInstance;
}

void C_PLAYER::init(C_WORLDMNG* pWorldMng)
{
    m_pWorldMng = pWorldMng;
    m_rPlayer.setRect(10.0f, 295.0f, 34, 85);
}

void C_PLAYER::loadTexture()
{
    m_pTexture[E_P_STATE::E_STAND] = Director::getInstance()->getTextureCache()->addImage("image/player_malone.png");
    m_pTexture[E_P_STATE::E_WALK] = Director::getInstance()->getTextureCache()->addImage("image/player_malone.png");
    m_pTexture[E_P_STATE::E_HANDBACK] = Director::getInstance()->getTextureCache()->addImage("image/player_mpartyb.png");
    m_pTexture[E_P_STATE::E_HANDBACK_WALK] = Director::getInstance()->getTextureCache()->addImage("image/player_mpartyb.png");
    m_pTexture[E_P_STATE::E_HANDFRONT] = Director::getInstance()->getTextureCache()->addImage("image/player_mpartyf.png");
    m_pTexture[E_P_STATE::E_HANDFRONT_WALK] = Director::getInstance()->getTextureCache()->addImage("image/player_mpartyf.png");
    m_pTexture[E_P_STATE::E_JUMP] = Director::getInstance()->getTextureCache()->addImage("image/player_malone.png");
    m_pTexture[E_P_STATE::E_JUMP_HANDFRONT] = Director::getInstance()->getTextureCache()->addImage("image/player_mpartyf.png");
}


void C_PLAYER::releaseTexture()
{
    for(int i = 0; i < E_P_STATE::E_P_STATE_MAX; i++)
    {
        if(m_pTexture[i])
        {
            Director::getInstance()->getTextureCache()->removeTexture(m_pTexture[i]);
        }
    }
}

void C_PLAYER::initSprites()
{
    m_pSprite[E_STAND] = Sprite::createWithTexture(m_pTexture[E_P_STATE::E_WALK], Rect(0, 0, 34, 85));
    m_pSprite[E_STAND]->setTag(TAG_PLAYER);
    m_pSprite[E_STAND]->retain();
}

void C_PLAYER::releaseSprites()
{
    for(int i = E_P_STATE_DEFUALT; i < E_P_STATE_MAX; i++)
    {
        if(m_pSprite[i])
        {
            m_pSprite[i]->release();
        }
    }
}

void C_PLAYER::createAnimation(E_P_STATE eState, int nMaxFrame, int nMaxColumn, int nFrameWidth, int nFrameHeight)
{
    m_pAnimation[eState] = Animation::create();
    m_pAnimation[eState]->setDelayPerUnit(0.3f);
    
    animationCreator(m_pAnimation[eState], m_pTexture[eState], nMaxFrame, nMaxColumn, nFrameWidth, nFrameHeight);
    m_pAnimate[eState] = Animate::create(m_pAnimation[eState]);
    m_pAnimate[eState]->retain();
    
    m_pRepeatForever[eState] = RepeatForever::create(m_pAnimate[eState]);
    m_pRepeatForever[eState]->retain();
    
}

void C_PLAYER::createAnimationOneFrame(E_P_STATE eState, int nX, int nY, int nWidth, int nHeight)
{
    m_pAnimation[eState] = Animation::create();
    m_pAnimation[eState]->setDelayPerUnit(0.3f);
    
    m_pAnimation[eState]->addSpriteFrameWithTexture(m_pTexture[eState], cocos2d::Rect(nX, nY, nWidth, nHeight));
    
    m_pAnimate[eState] = Animate::create(m_pAnimation[eState]);
    m_pAnimate[eState]->retain();
    
    m_pRepeatForever[eState] = RepeatForever::create(m_pAnimate[eState]);
    m_pRepeatForever[eState]->retain();

}

void C_PLAYER::initAnimations()
{
    createAnimationOneFrame(E_STAND, 0, 0, 34, 85);
    
    createAnimation(E_WALK, 2, 2, 34, 85);

    createAnimationOneFrame(E_HANDBACK, 0, 0, 34, 85);
    createAnimation(E_HANDBACK_WALK, 2, 2, 34, 85);
    
    createAnimationOneFrame(E_HANDFRONT, 0, 0, 34, 85);
    createAnimation(E_HANDFRONT_WALK, 2, 2, 34, 85);
    
    createAnimationOneFrame(E_JUMP, 34, 0, 34, 85);
    createAnimationOneFrame(E_JUMP_HANDFRONT, 34, 0, 34, 85);

}

void C_PLAYER::releaseAnimations()
{
    for(int i = E_P_STATE_DEFUALT; i < E_P_STATE_MAX; i++)
    {
        if(m_pAnimate[i])
        {
            m_pAnimate[i]->release();
        }
        if(m_pAnimation[i])
        {
            m_pAnimation[i]->release();
        }
        if(m_pRepeatForever[i])
        {
            m_pRepeatForever[i]->release();
        }
    }
}

void C_PLAYER::initAtStage()
{
    m_isParty = false;
    m_isRemoteMode = false;
    m_isLeft = false;
    m_nStageType = E_STAGE_NORMAL;
    m_nState = E_STAND;
    stopAction();
    C_SOUNDMNG::getInstance()->stopEffect(m_nEffectIndex);
}

void C_PLAYER::controlPlayerWithSprite(bool* arrBtn)
{
    if(m_isRemoteMode)
    {
        return;
    }
    
    float fSpeedNPC = C_NPCWOMAN::getInstance()->getHorizontalVelocity();
    
    b2Vec2 v2_player_vel = m_bPlayer->GetLinearVelocity();
    
    if(m_pSprite[E_STAND]->getPositionY() < 100.0f)
    {
        return;
    }
    
    
    //NOT party mode walk
    if(!m_isParty)
    {
		if (arrBtn[GamePlayScene::E_LEFT])
		{
			m_bPlayer->SetLinearVelocity(b2Vec2(-(m_fHorizontalVelocity), v2_player_vel.y));
		}

		if (arrBtn[GamePlayScene::E_RIGHT])
		{
			m_bPlayer->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity, v2_player_vel.y));
		}
        
    }
    //party mode walk
    else
    {
        if(arrBtn[GamePlayScene::E_LEFT])
        {
            m_bPlayer->SetLinearVelocity(b2Vec2(-fSpeedNPC, v2_player_vel.y));
        }
        
        if(arrBtn[GamePlayScene::E_RIGHT])
        {
            m_bPlayer->SetLinearVelocity(b2Vec2(fSpeedNPC, v2_player_vel.y));
        }
        
    }
    
    if(!m_isParty && m_isRayed && arrBtn[GamePlayScene::E_JUMP] && v2_player_vel.y <= 0)
    {
        m_bPlayer->SetLinearVelocity(b2Vec2(v2_player_vel.x, 11.0f));
    }
    
}

void C_PLAYER::remotePlayer(float fMoveToPosX)
{
    m_nCurrentState = m_nState;
    
    float fPlayerPosX = m_pSprite[E_STAND]->getPositionX();
    
    //left to right
    if(fPlayerPosX < fMoveToPosX)
    {
        m_pSprite[E_STAND]->setFlippedX(false);
        m_nState = E_WALK;
        m_bPlayer->SetLinearVelocity(b2Vec2(m_fHorizontalVelocity, 0.0f));
    }
    //right to left
    else if(fPlayerPosX > fMoveToPosX)
    {
        m_pSprite[E_STAND]->setFlippedX(true);
        m_nState = E_WALK;
        m_bPlayer->SetLinearVelocity(b2Vec2(-m_fHorizontalVelocity, 0.0f));
    }
    else if(fPlayerPosX == fMoveToPosX)
    {
        m_nState = E_STAND;
        m_bPlayer->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
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

void C_PLAYER::setRemoteMode()
{
    m_isRemoteMode = true;
}

const bool C_PLAYER::isRemoteMode()
{
    return m_isRemoteMode;
}

void C_PLAYER::stopAction()
{
    m_nState = E_STAND;
    m_bAniFlag = false;
    m_pSprite[E_STAND]->stopAllActions();
    m_pSprite[E_STAND]->runAction(m_pRepeatForever[E_STAND]);
    m_bAniFlag = true;
}


void C_PLAYER::setStageType(E_STAGE_TYPE eStageType)
{
    m_nStageType = eStageType;
}

void C_PLAYER::setHorizontalVelocity(float fVelocity)
{
    m_fHorizontalVelocity = fVelocity;
}

void C_PLAYER::setPositionBody(float fX, float fY)
{
	if (!m_pSprite[E_STAND] || !m_bPlayer)
    {
        log("C_PLAYER :: setPositionBody() : main Sprite is not created, setPosition Fails");
    }
    
    m_pSprite[E_STAND]->setPosition(Vec2(fX, fY));
    m_bPlayer->SetTransform(b2Vec2(fX  / PTM_RATIO, fY / PTM_RATIO), 0);
}

void C_PLAYER::setPlayerFlippedX(bool bFflippedX)
{
    m_pSprite[E_STAND]->setFlippedX(bFflippedX);
}

const float C_PLAYER::getPositionBodyX()
{
    float _fPlayerPosX = m_bPlayer->GetPosition().x;

    _fPlayerPosX = _fPlayerPosX * PTM_RATIO;
    
    return _fPlayerPosX;
}

const float C_PLAYER::getPositionBodyY()
{
    float _fPlayerPosY = m_bPlayer->GetPosition().y;
    
    _fPlayerPosY = _fPlayerPosY * PTM_RATIO;
    
    return _fPlayerPosY;
}

const Vec2 C_PLAYER::getPosition()
{
    Vec2 position = m_pSprite[E_STAND]->getPosition();
    position = position + Vec2(0.0f, 40.0f);
    return position;
}

const float C_PLAYER::getPositionX()
{
    return  m_pSprite[E_STAND]->getPositionX();
}

const float C_PLAYER::getPositionY()
{
    float _fPlayerPosY = m_pSprite[E_STAND]->getPositionY();
    
    return _fPlayerPosY + 40.0f;
}

Rect C_PLAYER::getPositionFoot()
{
    Sprite* _playerSpr = (Sprite*)m_bPlayer->GetUserData();
    Rect _PlayerRect = _playerSpr->getBoundingBox();
    
    float _fplayerHeight = _PlayerRect.size.height;
    
    _fplayerHeight = (_fplayerHeight / 8);
    
    m_rFoot.setRect(_PlayerRect.origin.x + 0.2f, _PlayerRect.origin.y, _PlayerRect.size.width - 0.2f, _fplayerHeight);
    
    return m_rFoot;
}

b2Body* C_PLAYER::getPlayerBody()
{
    return m_bPlayer;
}

const float C_PLAYER::getHalfBodyWidth()
{
    return m_fhalfBodyWidth;
}

const float C_PLAYER::getHalfBodyHeight()
{
    return m_fHalfBodyHeight;
}

void C_PLAYER::createPlayerBodyWithSprite(const cocos2d::Vec2& position)
{
    if(!m_pSprite[E_STAND])
    {
        log("C_PLAYER :: createPlayerBodyWithSprite : basic Sprite node is null, sprite body create fail");
        return;
    }
    
    m_pSprite[E_STAND]->setPosition(position);
    m_bPlayer = m_pWorldMng->createPlayerBodyWithSprite(m_pSprite[E_STAND]);
    
    Sprite* pSprPlayer = (Sprite*)m_bPlayer->GetUserData();
    m_fHalfBodyHeight = (pSprPlayer->getBoundingBox().size.height / 2) + 0.5f;
    m_fhalfBodyWidth = (pSprPlayer->getBoundingBox().size.width / 2);
}

void C_PLAYER::controlFSM(bool* arrBtn, cocos2d::Layer* pScene)
{
    if(m_isRemoteMode || !m_bPlayer)
    {
        return;
    }
    
    m_nCurrentState = m_nState;
    b2Vec2 b2_player_pos = m_bPlayer->GetPosition();
    
    
    C_NPCWOMAN * pNpcWoman = C_NPCWOMAN::getInstance();
    C_OBJECTMNG* pObjectMng = C_OBJECTMNG::getInstance();
    Rect rectNPC = pNpcWoman->getNPCSprite()->getBoundingBox();
    
    float fBetweenPlayerAndNPC = m_pSprite[E_STAND]->getPositionX() - pNpcWoman->getPositionX();
    
    m_isRayed= false;
    C_WORLDMNG::g_world->RayCast(this, b2_player_pos + b2Vec2(0.0f, -1.0f / PTM_RATIO), b2_player_pos + b2Vec2(0.0f,( -1.0f - 5.5f )/ PTM_RATIO));
    
    //showStatus();
    
    if(arrBtn[GamePlayScene::E_LEFT])
    {
        m_isLeft = true;
    }
    else if(arrBtn[GamePlayScene::E_RIGHT])
    {
        m_isLeft = false;
    }
    
    if(m_pSprite[E_STAND]->getChildByTag(TAG_TORCH))
    {
        m_isItem = true;
        
        if(!m_isLeft)
        {
            m_pSprite[E_STAND]->getChildByTag(TAG_TORCH)->setPosition(Vec2(m_fhalfBodyWidth, m_fHalfBodyHeight));
        }
        else
        {
            m_pSprite[E_STAND]->getChildByTag(TAG_TORCH)->setPosition(Vec2(-m_fhalfBodyWidth, m_fHalfBodyHeight));
        }
    }
    else
    {
        m_isItem = false;
    }

    if(!m_isItem) //NOT use item(torch) mode
    {
        if(pScene->getChildByTag(TAG_NPC) && m_isParty) // in party mode
        {
            if(arrBtn[GamePlayScene::E_USE])
            {
                m_isParty = false;
                m_nState = E_P_STATE::E_STAND;
                arrBtn[GamePlayScene::E_USE] = false;
                return;
            }
            
            if(pNpcWoman->getPositionX() <= m_pSprite[E_STAND]->getPositionX())
            {
                if(m_isLeft)
                {
                    m_nState = E_HANDFRONT;

                }
                else
                {
                    m_nState = E_HANDBACK;
                }
                
            }
            else
            {
                if(m_isLeft)
                {
                    m_nState = E_HANDBACK;
                }
                else
                {
                    m_nState = E_HANDFRONT;
                }
            }
            
            if(arrBtn[GamePlayScene::E_LEFT] || arrBtn[GamePlayScene::E_RIGHT])
            {
                
                if(m_nState == E_HANDBACK)
                {
                    m_nState = E_HANDBACK_WALK;
                }
                else if(m_nState == E_HANDFRONT)
                {
                    m_nState = E_HANDFRONT_WALK;
                }
            }
            
            
        }
        else // not party mode
        {
            
            if(arrBtn[GamePlayScene::E_LEFT] || arrBtn[GamePlayScene::E_RIGHT])
            {
                m_nState = E_P_STATE::E_WALK;
            }
            else
            {
                m_nState = E_P_STATE::E_STAND;
            }
            
            //find torch from scene,
            for(int i = 0; i < (int)pObjectMng->getObjectArrayWithType(C_OBJECTMNG::E_OBJ_TORCH)->size(); i++)
            {
                //when torch found
                if(pObjectMng->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, i))
                {
                    //when torch added from scene,
                    if(pObjectMng->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, i)->pSprite)
                    {
                        const Sprite* pTourchTemp = pObjectMng->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, i)->pSprite;
                    
                        //when this torch and player collide,
                        if(pTourchTemp->getBoundingBox().containsPoint(Vec2(getPositionX(), getPositionY())))
                        {
                            //when player input USE button,
                            if(arrBtn[GamePlayScene::E_USE])
                            {
                                //modify torch's parent Scene to Player, and remove torch's box2d body(this is work in modifyObjectParent Function.
                                pObjectMng->modifyObjectParent(C_OBJECTMNG::E_OBJ_TORCH, i, pScene, m_pSprite[E_STAND]);
                                pObjectMng->lockObjectModify(C_OBJECTMNG::E_OBJ_TORCH, i);
                            
                                //player's torch position setting for player direction
                                if(!m_isLeft)
                                {
                                    m_pSprite[E_STAND]->getChildByTag(TAG_TORCH)->setPosition(Vec2(m_fhalfBodyWidth, m_fHalfBodyHeight));
                                }
                                else
                                {
                                    m_pSprite[E_STAND]->getChildByTag(TAG_TORCH)->setPosition(Vec2(-m_fhalfBodyWidth, m_fHalfBodyHeight));
                                }
                            
                                arrBtn[GamePlayScene::E_USE] = false;
                            }
                        }
                    }
                }
            }
            
            
            if(pScene->getChildByTag(TAG_NPC) && arrBtn[GamePlayScene::E_USE] && m_isRayed)
            {
                if(fabs(fBetweenPlayerAndNPC) < 34 && fBetweenPlayerAndNPC <= 0.0f)
                {
                    if(m_isLeft)
                    {
                        m_nState = E_P_STATE::E_HANDBACK;
                    }
                    else
                    {
                        m_nState = E_P_STATE::E_HANDFRONT;
                    }
                    
                    m_isParty = true;
                    arrBtn[GamePlayScene::E_USE] = false;
                    return;
                }
                else if(fabs(fBetweenPlayerAndNPC) < 34 && fBetweenPlayerAndNPC > 0.0f)
                {
                    if(m_isLeft)
                    {
                        m_nState = E_P_STATE::E_HANDFRONT;
                    }
                    else
                    {
                        m_nState = E_P_STATE::E_HANDBACK;
                    }
                    
                    m_isParty = true;
                    arrBtn[GamePlayScene::E_USE] = false;
                    return;
                }
            }
        }
        
    }
    else //use item(torch) mode
    {
        if(arrBtn[GamePlayScene::E_LEFT] || arrBtn[GamePlayScene::E_RIGHT])
        {
            m_nState = E_P_STATE::E_HANDFRONT_WALK;
        }
        else
        {
            m_nState = E_P_STATE::E_HANDFRONT;
        }
        
        if(m_isParty) //use item and party mode
        {
            if(arrBtn[GamePlayScene::E_USE])
            {
                m_isParty = false;
                arrBtn[GamePlayScene::E_USE] = false;
                return;
            }
        }
        else//use item and not party mode
        {
            if(pScene->getChildByTag(TAG_NPC) && arrBtn[GamePlayScene::E_USE] && m_isRayed)
            {
                if(fabs(fBetweenPlayerAndNPC) < 35)
                {
                    m_isParty = true;
                    arrBtn[GamePlayScene::E_USE] = false;
                    return;
                }
            }
            
        }
    }
    
    if(!m_isRayed && !m_isItem)
    {
        m_nState = E_P_STATE::E_JUMP;
        return;
    }
    else if(!m_isRayed && m_isItem)
    {
        m_nState = E_P_STATE::E_JUMP_HANDFRONT;
        return;
    }

}

void C_PLAYER::showStatus()
{
    log("Player state : %d, bodyPosX : %f, bodyPosY : %f, party mode : %d, isLeft : %d", m_nState, getPositionBodyX(), getPositionBodyY(), m_isParty, m_isLeft);
    log("Player state : %d, sprPosX : %f, sprPosY : %f", m_nState, m_pSprite[E_STAND]->getPositionX(), m_pSprite[E_STAND]->getPositionY());
}

const int C_PLAYER::getState()
{
    return m_nState;
}

const bool C_PLAYER::isLeft()
{
    return m_isLeft;
}

void C_PLAYER::setPartyFalse()
{
    m_isParty = false;
}

const bool C_PLAYER::isParty()
{
    return m_isParty;
}

const bool C_PLAYER::isItem()
{
    return m_isItem;
}

void C_PLAYER::drawPlayer()
{
    if(m_isRemoteMode)
    {
        return;
    }
    
    m_pSprite[E_STAND]->setFlippedX(m_isLeft);
    
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

Sprite* C_PLAYER::getSpriteWithType(E_P_STATE eState)
{
    return m_pSprite[eState];
}

float32 C_PLAYER::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
    if(fixture->GetFilterData().groupIndex == -8)
    {
        m_isRayed = false;
        return 0;
    }
    
    m_isRayed = true;
    
    return 0;
}

void C_PLAYER::playSoundPlayer()
{
    if(m_nState == E_STAND || m_nState == E_HANDFRONT || m_nState == E_HANDBACK || m_nState == E_JUMP || m_nState == E_JUMP_HANDFRONT)
    {
        m_bSndFlag = false;
        C_SOUNDMNG::getInstance()->stopEffect(m_nEffectIndex);
        return;
    }
    
    
    if(!m_bSndFlag)
    {
        (this->*m_pPlayEffect[m_nStageType])();
        m_bSndFlag = true;
        return;
    }
    
    if(m_nCurrentState != m_nState)
    {
        m_bSndFlag = false;
        C_SOUNDMNG::getInstance()->stopEffect(m_nEffectIndex);
    }
    
    
}

void C_PLAYER::stopSound()
{
    m_bSndFlag = false;
    C_SOUNDMNG::getInstance()->stopEffect(m_nEffectIndex);
}


void C_PLAYER::playEffectWalkNormal()
{
    m_nEffectIndex = C_SOUNDMNG::getInstance()->playEffectForever(SND_EF_STEP);
}

void C_PLAYER::playEffectWalkCave()
{
    m_nEffectIndex = C_SOUNDMNG::getInstance()->playEffectForever(SND_EF_CAVESTEP);
}
