//
//  NpcWoman.h
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 14..
//
//

#ifndef __ProjectH__NpcWoman__
#define __ProjectH__NpcWoman__

#include <cocos2d.h>
#include "AppMacros.h"
#include "GamePlayScene.h"
#include "WorldMng.h"
#include "Box2D/Box2D.h"
#include "Player.h"
#include "DeadZone.h"


class C_NPCWOMAN
{
public:
    enum E_NPC_STATE
    {
        E_NPC_DEFUALT,
        E_STAND,
        E_HAND,
        E_HAND_WALK,
        E_WALK,
        E_WARNING,
        E_DEAD,
        E_NPC_MAX
    };
    
private:
    
    static C_NPCWOMAN* m_pInstance;
    
private:
    
    C_WORLDMNG* m_pWorldMng;

    int m_nState;
    float m_fHorizontalVelocity;
    float m_fHalfBodyHeight;
    float m_fhalfBodyWidth;
    
    bool m_isLeft;
    
    bool m_bAniFlag;
    int m_nCurrentState;
    
    bool m_bDead;
    bool m_isRemoteMode;
    
    b2Body* m_bNPC;
    
    cocos2d::Rect m_rFoot;
    
    cocos2d::CallFunc* m_pCallBack;
    cocos2d::Sequence* m_pDeadSequence;
        
    cocos2d::Texture2D* m_pTexture[E_NPC_MAX];
    cocos2d::Sprite* m_pSprite[E_NPC_MAX];
    cocos2d::Animation* m_pAnimation[E_NPC_MAX];
    cocos2d::Animate* m_pAnimate[E_NPC_MAX];
    cocos2d::RepeatForever* m_pRepeatForever[E_NPC_MAX];
    
private:
    
    C_NPCWOMAN();
    //this class is singleton pattern..
    
    C_NPCWOMAN(C_NPCWOMAN&);
    C_NPCWOMAN& operator = (C_NPCWOMAN&);
    //Do not use Copy Constructor, Destructor, Operator=
    
private:
    
    void createAnimation(E_NPC_STATE eState, int nMaxFrame, int nMaxColumn, int nFrameWidth, int nFrameHeight, float fSpeed);
    
    void createAnimationOneFrame(E_NPC_STATE eState, int nX, int nY, int nWidth, int nHeight);
    
    
public:
    
    void loadTexture();
    void releaseTexture();
    
    void initSprites();
    void releaseSprites();
    
    void initAnimations();
    void releaseAnimation();
    
    void setHorizontalVelocity(float fVelocity);
    const float getHorizontalVelocity();
  
public:
    static C_NPCWOMAN* getInstance();
    
    static void createInstance();
    static void releaseInstance();
    
public:
    
    void init(C_WORLDMNG* pWorldMng);
    void releaseNPC(cocos2d::Layer *pScene);
    
    void createNPCBodyWithSprite(const cocos2d::Vec2& position);
    
    void createNPC(cocos2d::Layer* pScene, float fX, float fY, float fVelocity);
    
    void controlNPC(C_PLAYER* pPlayer);
    void controlFSM(C_PLAYER* pPlayer, C_DEADZONE* pDeadZone, cocos2d::Layer* pScene);
    void drawNPC(C_PLAYER* pPlayer);
    
    
    void remoteNPC(float fMoveToPosX);
    
    const int getNPCState();
    
    void removeAndinitNPC(cocos2d::Layer *pScene);
    
    void stopAction();
    
    void setPositionBody(float fX, float fY);
    void setNPCFlippedX(bool bFflippedX);
    
    cocos2d::Sprite* getNPCSprite();
    const float getPositionBodyX();
    const float getPositionX();
    
    cocos2d::Rect getPositionFoot();
    
    b2Body* getNPCBody();
    const float getHalfBodyHeight();
    
    void runDead();
    
private:
    void setDead();
    
public:
    const bool isDead();
    
    void setRemoteMode();
    const bool isRemoteMode();

	
    
};

#endif /* defined(__ProjectH__NpcWoman__) */