/*
 * PlayerMng.h
 *
 *  Created on: 2014. 10. 1.
 *      Author: jungyonghoon
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "GamePlayScene.h"
#include "WorldMng.h"
#include "Box2D/Box2D.h"
#include "AppMacros.h"


class C_PLAYER : public b2RayCastCallback
{
public:
    
    enum E_P_STATE
    {
        E_P_STATE_DEFUALT,
        E_STAND,
        E_HANDBACK,
        E_HANDBACK_WALK,
        E_HANDFRONT,
        E_HANDFRONT_WALK,
        E_WALK,
        E_JUMP,
        E_JUMP_HANDFRONT,
        E_P_STATE_MAX
    };
    
public:
    
    enum E_STAGE_TYPE
    {
        E_S_TYPE_DEFUALT,
        E_STAGE_NORMAL,
        E_STAGE_CAVE,
        E_S_TYPE_MAX
    };
    
private:
    
    C_WORLDMNG* m_pWorldMng;
    
    bool m_isRemoteMode;
    
    bool m_isRayed;
    
    bool m_bAniFlag;
    
    bool m_isParty;
    
    bool m_isItem;
    
    bool m_isLeft;
    
    static C_PLAYER* m_pInstance;
    
    b2Body* m_bPlayer;
    
    cocos2d::Rect m_rPlayer;
    cocos2d::Rect m_rFoot;
    
    cocos2d::Texture2D* m_pTexture[E_P_STATE_MAX];
    cocos2d::Sprite* m_pSprite[E_P_STATE_MAX];
    cocos2d::Animation* m_pAnimation[E_P_STATE_MAX];
    cocos2d::Animate* m_pAnimate[E_P_STATE_MAX];
    cocos2d::RepeatForever* m_pRepeatForever[E_P_STATE_MAX];

    
    float m_fHorizontalVelocity;
    
    float m_fHalfBodyHeight;
    float m_fhalfBodyWidth;
    
    int m_nState;
    int m_nCurrentState;
    
    //sound var
    int m_nStageType;
    int m_nEffectIndex;
    bool m_bSndFlag;
    
private:
    
    C_PLAYER();
    
    C_PLAYER(C_PLAYER&);
    C_PLAYER& operator = (C_PLAYER&);
    //Do not use Copy Constructor, Destructor, Operator=
    
public:
    
    static void createInstance();
    static void releaseInstance();
    
    static C_PLAYER* getInstance();
    
private:
    void createAnimation(E_P_STATE eState, int nMaxFrame, int nMaxColumn, int nFrameWidth, int nFrameHeight);
    
    void createAnimationOneFrame(E_P_STATE eState, int nX, int nY, int nWidth, int nHeight);
    
    void showStatus();

public:
    
    void init(C_WORLDMNG* pWorldMng);
    
    void createArmature();
    
    void loadTexture();
    void releaseTexture();
    
    void initSprites();
    void initAnimations();
    
    void releaseSprites();
    void releaseAnimations();

    
public:
    
    void initAtStage();
    
    void controlPlayerWithSprite(bool* arrBtn);
    
    void remotePlayer(float fMoveToPosX);
    void setRemoteMode();
    const bool isRemoteMode();
    void stopAction();
    
    void setPositionBody(float fX, float fY);
    void setPlayerFlippedX(bool bFflippedX);

    const float getPositionBodyX();
    const float getPositionBodyY();
    
    const cocos2d::Vec2 getPosition();
    
    const float getPositionX();
    const float getPositionY();
    
    const float getHalfBodyWidth();
    const float getHalfBodyHeight();
    
    cocos2d::Rect getPositionFoot();
    
    b2Body* getPlayerBody();
    
    void setStageType(E_STAGE_TYPE eStageType);
    void setHorizontalVelocity(float fVelocity);
    
    void createPlayerBodyWithSprite(const cocos2d::Vec2& position);
    
    void controlFSM(bool* arrBtn, cocos2d::Layer* pScene);
    const int getState();
    
    const bool isLeft();
    
    void setPartyFalse();
    const bool isParty();
    const bool isItem();
    
    void drawPlayer();
    
    cocos2d::Sprite* getSpriteWithType(E_P_STATE eState);
    
    //This is raycast override funtion of b2RayCastCallback
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
    
    void playSoundPlayer();
    void stopSound();
    
private:
    
    void (C_PLAYER::*m_pPlayEffect[E_S_TYPE_MAX])();
    
    void playEffectWalkNormal();
    void playEffectWalkCave();

};



#endif /* __PLAYER_H__ */
