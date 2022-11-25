//
//  StageMng.h
//  projectH
//
//  Created by JungYonghoon on 2014. 10. 20..
//
//

#ifndef __STAGE_MNG_H__
#define __STAGE_MNG_H__

#include <cocos2d.h>
#include "AppMacros.h"
#include "GamePlayScene.h"
#include "ObjectMng.h"
#include "Terrain.h"
#include "NpcWoman.h"
#include "DeadZone.h"

class C_STAGEMNG
{
    
public:
    enum E_STAGE
    {
        E_STAGE_DEFAULT,
        E_STAGE1,
        E_STAGE2,
        E_STAGE3,
        E_STAGE4,
        E_STAGE5,
        E_STAGE6,
        E_STAGE7,
        E_STAGE8,
        E_STAGE9,
        E_STAGE10,
        E_STAGE11,
        E_STAGE12,
        E_STAGE13,
        E_STAGE14,
        E_STAGE15,
        E_STAGE16,
        E_STAGE17,
        E_STAGE18,
        E_STAGE19,
        E_STAGE20,
        E_STAGE21,
        E_STAGE22,
        E_STAGE23,
        E_STAGE24,
        E_STAGE25,
        E_STAGE26,
        E_STAGE27,
        E_STAGE28,
        E_STAGE29,
        E_STAGE30,
        E_STAGE31,
        E_STAGE_MAX
    };

private:
    static C_STAGEMNG* m_pInstance;
    
private:
    int m_nStageNum;
    
    //for Shadow And Light
    cocos2d::LayerColor* m_pShadowLayer;
    cocos2d::ClippingNode* m_pLight;
    cocos2d::Sprite* m_pSprLightStencil;
	cocos2d::Sprite* m_pSprLightShader;
    
    
private:
    C_PLAYER *m_pPlayer;
    C_OBJECTMNG *m_pObject;
    C_TERRAIN *m_pTerrain;
    C_NPCWOMAN *m_pNPCWoman;
    C_DEADZONE *m_pDeadZone;
    
    cocos2d::Sprite* m_pSprBG;
    cocos2d::Texture2D* m_pTextureBG;
    
    bool m_isEventLock;
	bool m_isAllClear;
    int m_nEventTimer;
    
private:
    
    C_STAGEMNG();
    
    C_STAGEMNG(C_STAGEMNG&);
    C_STAGEMNG& operator = (C_STAGEMNG&);
    //Do not use Copy Constructor, Destructor, Operator=

public:
    static void createInstance();
    static void releaseInstance();
    static C_STAGEMNG* getInstance();
    
    
public:
    
    void initStageToScene(GamePlayScene* pScene);
    
    void setStageToScene(GamePlayScene* pScene, int nStage);
    void releaseStageToScene(cocos2d::Layer* pScene);

    void checkEventToScene(GamePlayScene* pScene);
    
    int getStageNum();
    int getStageNumFromSaveData();


	bool isAllClear();
    
    void saveStageNum();
    
    void setStageNum(int nStage);
    
public:
    
    void init(C_PLAYER* pPlayer, C_OBJECTMNG* pObject, C_TERRAIN* pTerrain, C_NPCWOMAN* pNPCWoman, C_DEADZONE *pDeadZone);
    
public:
    void loadBG(int nStage);
    void setBGToScene(cocos2d::Layer* pScene);
    void destroyBGFromScene(cocos2d::Layer* pScene);

    
    
    //event check functions
private:
    inline bool isFalled(float fObjectPosY, float fPontY);
    inline bool isCheckPoint(float fObjectPosX, float fPointX);
    inline bool isCollusion(const cocos2d::Rect &rDest, const cocos2d::Rect &rSrc);
    
	void checkCollutionBushAndTorch(cocos2d::Layer* pScene);

private:
    void createShadowAndLight(cocos2d::Layer *pScene);
    void setLightPosition(const cocos2d::Vec2& lightPos);
    void releaseShadowAndLight(cocos2d::Layer *pScene);
    
private:
	void callbackWithCase(cocos2d::Ref* pSender, int nSituation);
	
private:
    
    void (C_STAGEMNG::*m_pStageData[E_STAGE_MAX])(cocos2d::Layer* pScene);
    void (C_STAGEMNG::*m_pStageEvent[E_STAGE_MAX])(cocos2d::Layer* pScene);
    
    void stageData3(cocos2d::Layer* pScene);
    
    void stageData5(cocos2d::Layer* pScene);
    
    void stageData6(cocos2d::Layer* pScene);
    void stageEvent6(cocos2d::Layer* pScene);
    
    void stageData7(cocos2d::Layer* pScene);
    void stageEvent7(cocos2d::Layer* pScene);
    
    void stageData8(cocos2d::Layer* pScene);
    void stageEvent8(cocos2d::Layer* pScene);
    
    void stageData9(cocos2d::Layer* pScene);
    void stageEvent9(cocos2d::Layer* pScene);
    
    void stageData10(cocos2d::Layer* pScene);
    void stageEvent10(cocos2d::Layer* pScene);
    
    void stageData11(cocos2d::Layer* pScene);
    void stageEvent11(cocos2d::Layer* pScene);
    
    void stageData12(cocos2d::Layer* pScene);
    void stageEvent12(cocos2d::Layer* pScene);
    
    void stageData13(cocos2d::Layer* pScene);
    void stageEvent13(cocos2d::Layer* pScene);
    
    void stageData14(cocos2d::Layer* pScene);
    void stageEvent14(cocos2d::Layer* pScene);
    
    void stageData15(cocos2d::Layer* pScene);
    void stageEvent15(cocos2d::Layer* pScene);
    
    void stageData16(cocos2d::Layer* pScene);
    void stageEvent16(cocos2d::Layer* pScene);
    
    void stageData17(cocos2d::Layer* pScene);
    void stageEvent17(cocos2d::Layer* pScene);
    
    void stageData18(cocos2d::Layer* pScene);
    void stageEvent18(cocos2d::Layer* pScene);
    
    void stageData19(cocos2d::Layer* pScene);
    void stageEvent19(cocos2d::Layer* pScene);
    
    void stageData20(cocos2d::Layer* pScene);
    void stageEvent20(cocos2d::Layer* pScene);
    
    void stageData21(cocos2d::Layer* pScene);
    void stageEvent21(cocos2d::Layer* pScene);
    
    void stageData22(cocos2d::Layer* pScene);
    void stageEvent22(cocos2d::Layer* pScene);
    
    void stageData23(cocos2d::Layer* pScene);
    void stageEvent23(cocos2d::Layer* pScene);
    
    void stageData24(cocos2d::Layer* pScene);
    void stageEvent24(cocos2d::Layer* pScene);
    
    void stageData25(cocos2d::Layer* pScene);
    void stageEvent25(cocos2d::Layer* pScene);
    
    void stageData26(cocos2d::Layer* pScene);
    void stageEvent26(cocos2d::Layer* pScene);
    
    void stageData27(cocos2d::Layer* pScene);
    void stageEvent27(cocos2d::Layer* pScene);
    
    void stageData28(cocos2d::Layer* pScene);
    void stageEvent28(cocos2d::Layer* pScene);
    
    void stageData29(cocos2d::Layer* pScene);
    void stageEvent29(cocos2d::Layer* pScene);

    void stageData30(cocos2d::Layer* pScene);
    void stageEvent30(cocos2d::Layer* pScene);
    
    void stageData31(cocos2d::Layer* pScene);
    void stageEvent31(cocos2d::Layer* pScene);
    
    void stageDataDefaultOnePlayer(cocos2d::Layer* pScene);
    void stageEventDefaultOnePlayer(cocos2d::Layer* pScene);

};

#endif /* defined(__projectH__StageMng__) */
