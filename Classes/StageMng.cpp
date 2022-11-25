//
//  StageMng.cpp
//  projectH
//
//  Created by JungYonghoon on 2014. 10. 20..
//
//

#include "StageMng.h"
#include "GamePlayScene.h"
#include "UiMng.h"
#include "SoundMng.h"

#define NUM 0
USING_NS_CC;

C_STAGEMNG* C_STAGEMNG::m_pInstance = NULL;

C_STAGEMNG::C_STAGEMNG():
m_nStageNum(0),
m_pShadowLayer(NULL),
m_pLight(NULL),
m_pSprLightStencil(NULL),
m_pSprLightShader(NULL),
m_pPlayer(NULL),
m_pObject(NULL),
m_pTerrain(NULL),
m_pNPCWoman(NULL),
m_pSprBG(NULL),
m_pTextureBG(NULL),
m_isEventLock(false),
m_isAllClear(false),
m_nEventTimer(0)
{
    for(int i = E_STAGE_DEFAULT; i < E_STAGE_MAX; i++)
    {
        m_pStageData[i] = NULL;
        m_pStageEvent[i] = NULL;
    }
    
    
    //FUNCTIONS ADDRESS MAPPING FOR FUCTION POINTER ARRAY CALL

    //STAGE DATA FUNCTION POINTER SETTING
    m_pStageData[E_STAGE1]  = &C_STAGEMNG::stageDataDefaultOnePlayer;
    m_pStageData[E_STAGE2]  = &C_STAGEMNG::stageDataDefaultOnePlayer;
    m_pStageData[E_STAGE3]  = &C_STAGEMNG::stageData3;
    m_pStageData[E_STAGE4]  = &C_STAGEMNG::stageDataDefaultOnePlayer;
    m_pStageData[E_STAGE5]  = &C_STAGEMNG::stageData5;
    m_pStageData[E_STAGE6]  = &C_STAGEMNG::stageData6;
    m_pStageData[E_STAGE7]  = &C_STAGEMNG::stageData7;
    m_pStageData[E_STAGE8]  = &C_STAGEMNG::stageData8;
    m_pStageData[E_STAGE9]  = &C_STAGEMNG::stageData9;
    m_pStageData[E_STAGE10] = &C_STAGEMNG::stageData10;
    m_pStageData[E_STAGE11] = &C_STAGEMNG::stageData11;
    m_pStageData[E_STAGE12] = &C_STAGEMNG::stageData12;
    m_pStageData[E_STAGE13] = &C_STAGEMNG::stageData13;
    m_pStageData[E_STAGE14] = &C_STAGEMNG::stageData14;
    m_pStageData[E_STAGE15] = &C_STAGEMNG::stageData15;
    m_pStageData[E_STAGE16] = &C_STAGEMNG::stageData16;
    m_pStageData[E_STAGE17] = &C_STAGEMNG::stageData17;
    m_pStageData[E_STAGE18] = &C_STAGEMNG::stageData18;
    m_pStageData[E_STAGE19] = &C_STAGEMNG::stageData19;
    m_pStageData[E_STAGE20] = &C_STAGEMNG::stageData20;
    m_pStageData[E_STAGE21] = &C_STAGEMNG::stageData21;
    m_pStageData[E_STAGE22] = &C_STAGEMNG::stageData22;
    m_pStageData[E_STAGE23] = &C_STAGEMNG::stageData23;
    m_pStageData[E_STAGE24] = &C_STAGEMNG::stageData24;
    m_pStageData[E_STAGE25] = &C_STAGEMNG::stageData25;
    m_pStageData[E_STAGE26] = &C_STAGEMNG::stageData26;
    m_pStageData[E_STAGE27] = &C_STAGEMNG::stageData27;
    m_pStageData[E_STAGE28] = &C_STAGEMNG::stageData28;
    m_pStageData[E_STAGE29] = &C_STAGEMNG::stageData29;
    m_pStageData[E_STAGE30] = &C_STAGEMNG::stageData30;
    m_pStageData[E_STAGE31] = &C_STAGEMNG::stageData31;
    
    
    //STAGE EVENT FUNCTION POINTER SETTING
    m_pStageEvent[E_STAGE1]  = &C_STAGEMNG::stageEventDefaultOnePlayer;
    m_pStageEvent[E_STAGE2]  = &C_STAGEMNG::stageEventDefaultOnePlayer;
    m_pStageEvent[E_STAGE3]  = &C_STAGEMNG::stageEventDefaultOnePlayer;
    m_pStageEvent[E_STAGE4]  = &C_STAGEMNG::stageEventDefaultOnePlayer;
    m_pStageEvent[E_STAGE5]  = &C_STAGEMNG::stageEventDefaultOnePlayer;
    m_pStageEvent[E_STAGE6]  = &C_STAGEMNG::stageEvent6;
    m_pStageEvent[E_STAGE7]  = &C_STAGEMNG::stageEvent7;
    m_pStageEvent[E_STAGE8]  = &C_STAGEMNG::stageEvent8;
    m_pStageEvent[E_STAGE9]  = &C_STAGEMNG::stageEvent9;
    m_pStageEvent[E_STAGE10] = &C_STAGEMNG::stageEvent10;
    m_pStageEvent[E_STAGE11] = &C_STAGEMNG::stageEvent11;
    m_pStageEvent[E_STAGE12] = &C_STAGEMNG::stageEvent12;
    m_pStageEvent[E_STAGE13] = &C_STAGEMNG::stageEvent13;
    m_pStageEvent[E_STAGE14] = &C_STAGEMNG::stageEvent14;
    m_pStageEvent[E_STAGE15] = &C_STAGEMNG::stageEvent15;
    m_pStageEvent[E_STAGE16] = &C_STAGEMNG::stageEvent16;
    m_pStageEvent[E_STAGE17] = &C_STAGEMNG::stageEvent17;
    m_pStageEvent[E_STAGE18] = &C_STAGEMNG::stageEvent18;
    m_pStageEvent[E_STAGE19] = &C_STAGEMNG::stageEvent19;
    m_pStageEvent[E_STAGE20] = &C_STAGEMNG::stageEvent20;
    m_pStageEvent[E_STAGE21] = &C_STAGEMNG::stageEvent21;
    m_pStageEvent[E_STAGE22] = &C_STAGEMNG::stageEvent22;
    m_pStageEvent[E_STAGE23] = &C_STAGEMNG::stageEvent23;
    m_pStageEvent[E_STAGE24] = &C_STAGEMNG::stageEvent24;
    m_pStageEvent[E_STAGE25] = &C_STAGEMNG::stageEvent25;
    m_pStageEvent[E_STAGE26] = &C_STAGEMNG::stageEvent26;
    m_pStageEvent[E_STAGE27] = &C_STAGEMNG::stageEvent27;
    m_pStageEvent[E_STAGE28] = &C_STAGEMNG::stageEvent28;
    m_pStageEvent[E_STAGE29] = &C_STAGEMNG::stageEvent29;
    m_pStageEvent[E_STAGE30] = &C_STAGEMNG::stageEvent30;
    m_pStageEvent[E_STAGE31] = &C_STAGEMNG::stageEvent31;
}



void C_STAGEMNG::setStageToScene(GamePlayScene* pScene, int nStage)
{
    m_nStageNum = nStage;
    saveStageNum();
    
    log("C_STAGEMNG :: setStage() : Stage = %d, Stage setting START........", m_nStageNum);
    
    releaseStageToScene(pScene);
    
    if(m_nStageNum > MAX_STAGE)
    {
        log("C_STAGEMNG :: setStage() : MAX STAGE reached! data will be reset");
        m_nStageNum = 0;
		m_isAllClear = true;
        saveStageNum();
        pScene->changeScene(pScene);
        return;
    }
    
    
    initStageToScene(pScene);
    
    log("C_STAGEMNG :: setStage() : Stage = %d, Stage setting .........END!", m_nStageNum);
}

void C_STAGEMNG::initStageToScene(GamePlayScene* pScene)
{
    loadBG(m_nStageNum);
    setBGToScene(pScene);
    
    (this->*m_pStageData[(E_STAGE)m_nStageNum])(pScene);
}


void C_STAGEMNG::checkEventToScene(GamePlayScene* pScene)
{
    (this->*m_pStageEvent[(E_STAGE)m_nStageNum])(pScene);
}



void C_STAGEMNG::releaseStageToScene(cocos2d::Layer* pScene)
{
    m_nEventTimer = 0;
    m_isEventLock = false;
    
    destroyBGFromScene(pScene);
    releaseShadowAndLight(pScene);
    m_pTerrain->releaseAllTerrain(pScene);
    m_pObject->releaseAndRemoveAllObject(pScene);
    m_pDeadZone->removeDeadZone(pScene);
    m_pNPCWoman->removeAndinitNPC(pScene);
    m_pPlayer->initAtStage();
    C_SOUNDMNG::getInstance()->stopBG();
    
    log("C_STAGEMNG :: releaseStage() : Stage objects has released");
}


int C_STAGEMNG::getStageNum()
{
    return m_nStageNum;
}

void C_STAGEMNG::setStageNum(int nStage)
{
    m_nStageNum = nStage;
}

int C_STAGEMNG::getStageNumFromSaveData()
{
    int _nSaveData = UserDefault::getInstance()->getIntegerForKey("int_save_stage");
    return _nSaveData;
}

bool C_STAGEMNG::isAllClear()
{
	return m_isAllClear;
}

void C_STAGEMNG::saveStageNum()
{
    UserDefault::getInstance()->setIntegerForKey("int_save_stage", m_nStageNum);
    log("C_STAGEMNG :: saveStageNum - %d : Stage Saved..", m_nStageNum);
}


void C_STAGEMNG::init(C_PLAYER* pPlayer, C_OBJECTMNG* pObject, C_TERRAIN* pTerrain, C_NPCWOMAN* pNPCWoman, C_DEADZONE *pDeadZone)
{
    m_pPlayer = pPlayer;
    m_pObject = pObject;
    m_pTerrain = pTerrain;
    m_pNPCWoman = pNPCWoman;
    m_pDeadZone = pDeadZone;
}


void C_STAGEMNG::setBGToScene(Layer* pScene)
{
    m_pSprBG->setPosition(GAME_WIDTH / 2, GAME_HEIGHT / 2);
    
    pScene->addChild(m_pSprBG, TAG_BG);
    
    log("C_STAGEMNG :: setBG() : Stage BackGround has been changed");
}

void C_STAGEMNG::destroyBGFromScene(cocos2d::Layer* pScene)
{
    if(!m_pSprBG)
    {
        log("C_STAGEMNG :: destroyBG() : m_pSprBG is NULL, m_pSprBG can not Destroy.");
        return;
    }
    pScene->removeChild(m_pSprBG);
    Director::getInstance()->getTextureCache()->removeTexture(m_pTextureBG);
    m_pTextureBG = NULL;
    m_pSprBG = NULL;
    
    log("C_STAGEMNG :: destroyBG() : m_pSprBG has been Destroyed.");
}

void C_STAGEMNG::loadBG(int nStage)
{
    if(m_pSprBG)
    {
        log("C_STAGEMNG :: loadBG() : m_pSprBG is not NULL, load stage BG canceled");
        return;
    }
    
    char _cStage[128];
    
    sprintf(_cStage, "image/bg_%02d.png", nStage);
    m_pTextureBG = Director::getInstance()->getTextureCache()->addImage(_cStage);
    m_pSprBG = Sprite::createWithTexture(m_pTextureBG);
    log("C_STAGEMNG :: loadBG() : Stage Background has been Loaded");
}

bool C_STAGEMNG::isFalled(float fObjectPosY, float fPontY)
{
    if(fObjectPosY < fPontY)
    {
        return true;
    }
    
    return false;
}

bool C_STAGEMNG::isCheckPoint(float fObjectPosX, float fPointX)
{
    if(fObjectPosX > fPointX)
    {
        return true;
    }
    
    return false;
}

bool C_STAGEMNG::isCollusion(const Rect &rDest, const Rect &rSrc)
{
    float fVecX = rDest.getMidX() - rSrc.getMidX();
    float fVecY = rDest.getMidY() - rSrc.getMidY();
    
    float fLength = sqrt(fVecX * fVecX + fVecY * fVecY);
    
    if (fLength < rDest.size.height * 0.8f + rSrc.size.height * 0.8f)
        return true;
    
    return false;
}

void C_STAGEMNG::checkCollutionBushAndTorch(cocos2d::Layer* pScene)
{
	Sprite* _pSprPlayer = m_pPlayer->getSpriteWithType(C_PLAYER::E_STAND);

	//when Player use item(torch)
	if (_pSprPlayer->getChildByTag(TAG_TORCH))
	{
		std::vector<C_OBJECTMNG::S_OBJECT*>* vBushs = m_pObject->getObjectArrayWithType(C_OBJECTMNG::E_OBJ_BUSH);

		//find bush
		for (int i = 0; i < (int)(vBushs->size()); i++)
		{
			auto bush = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BUSH, i);
			if (bush && bush->pSprite && !bush->isLock)
			{
				//when finded bush collides with player,
				if (bush->pSprite->getBoundingBox().containsPoint(Vec2(m_pPlayer->getPositionX(), m_pPlayer->getPositionY())))
				{
					//release bush and
					m_pObject->removeObjectBySeq(C_OBJECTMNG::E_OBJ_BUSH, i, pScene);

					std::vector<C_OBJECTMNG::S_OBJECT*>* vTorchs = m_pObject->getObjectArrayWithType(C_OBJECTMNG::E_OBJ_TORCH);

					//find torch
					for (int j = 0; j < (int)(vTorchs->size()); j++)
					{
						auto torch = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, j);

						if (torch && torch->pSprite)
						{
							//find torch of parent is player
							if (torch->pSprite->getParent() == _pSprPlayer)
							{
								//release this torch
								m_pObject->removeObject(C_OBJECTMNG::E_OBJ_TORCH, j, _pSprPlayer);
								break;
							}
						}
					}
					break;
				}
			}
		}
	}
}


void C_STAGEMNG::createShadowAndLight(cocos2d::Layer *pScene)
{
    m_pLight = ClippingNode::create();
    m_pLight->setInverted(true);
    m_pLight->setAlphaThreshold(0.5f);
    m_pLight->setTag(TAG_CLIPPINGNODE);
    m_pLight->retain();
    pScene->addChild(m_pLight, TAG_CLIPPINGNODE);

    m_pShadowLayer = LayerColor::create(Color4B(0, 0, 0, 255));
    
    m_pLight->addChild(m_pShadowLayer, -1);
    
    m_pSprLightStencil = Sprite::create("image/lightStencil.png");
    m_pSprLightStencil->setPosition(Vec2(999999.9f, 999999.9f));
	m_pSprLightStencil->setScale(1.3f);
    m_pLight->setStencil(m_pSprLightStencil);

	m_pSprLightShader = Sprite::create("image/lightShader.png");
	m_pSprLightShader->setPosition(Vec2(999999.9f, 999999.9f));
	m_pSprLightShader->setTag(TAG_LIGHTSTENCIL);
	m_pSprLightShader->setScale(1.9f);
	m_pSprLightShader->setOpacity(230);
	m_pSprLightShader->retain();
	pScene->addChild(m_pSprLightShader, TAG_LIGHTSTENCIL);

}

void C_STAGEMNG::setLightPosition(const cocos2d::Vec2& lightPos)
{
    //If you didn't create ClippingNode, It will be error.
    m_pSprLightStencil->setPosition(lightPos);
	m_pSprLightShader->setPosition(lightPos);
}

void C_STAGEMNG::releaseShadowAndLight(cocos2d::Layer *pScene)
{
    if(pScene->getChildByTag(TAG_CLIPPINGNODE))
    {
        pScene->removeChild(m_pLight);
        m_pLight->release();
    }

	if (pScene->getChildByTag(TAG_LIGHTSTENCIL))
	{
		pScene->removeChild(m_pSprLightShader);
		m_pSprLightShader->release();
	}
}

void C_STAGEMNG::callbackWithCase(Ref* pSender, int nSituation)
{
	switch (nSituation)
	{
	case 1: //C_NPC_DEAD
		m_pNPCWoman->runDead();
		break;
	}
}

void C_STAGEMNG::stageData3(cocos2d::Layer* pScene)
{
    C_SOUNDMNG::getInstance()->playBG(SND_BG_FOREST);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect(0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);
    
    m_pPlayer->setPositionBody(50.0f, 106.2f);
}

void C_STAGEMNG::stageData5(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 376.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(376.0f + 75.0f, 0.0f , 740.0f, 100.0f));

	m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
	m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect(0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);
    
    m_pPlayer->setPositionBody(50.0f, 106.2f);
    
}

void C_STAGEMNG::stageData6(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 109.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(109.0f + 75.0f, 0.0f , 401.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(585.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
	m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
	m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect(0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);

    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (400.0f, 100.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    m_pPlayer->setPositionBody(50.0f, 106.2f);
}

void C_STAGEMNG::stageEvent6(cocos2d::Layer* pScene)
{
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(400.0f, 100.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(550.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -80.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    if(isCheckPoint(m_pPlayer->getPositionX(), GAME_WIDTH + 5))
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
        return;
    }
    
}


void C_STAGEMNG::stageData7(cocos2d::Layer* pScene)
{
    C_SOUNDMNG::getInstance()->playBG(SND_BG_WIND);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f, 400.0f, 100.0f));

	m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
	m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect(0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);
    
    m_pPlayer->setPositionBody(50.0f, 106.2f);
}

void C_STAGEMNG::stageEvent7(cocos2d::Layer* pScene)
{
    
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
    }
    
}


void C_STAGEMNG::stageData8(cocos2d::Layer* pScene)
{
    m_pPlayer->setPositionBody(m_pPlayer->getPositionX(), 500.0f);
}

void C_STAGEMNG::stageEvent8(cocos2d::Layer* pScene)
{
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
    }
}

void C_STAGEMNG::stageData9(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 320.0f, GAME_HEIGHT));
    
    m_pPlayer->setPositionBody(400.0f, 500.0f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(630.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 630.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
}

void C_STAGEMNG::stageEvent9(cocos2d::Layer* pScene)
{
    
    
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
        {
            setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
            return;
        }
    }
}

void C_STAGEMNG::stageData10(cocos2d::Layer* pScene)
{
    C_SOUNDMNG::getInstance()->playEffectOnce(SND_EF_WOO);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}

void C_STAGEMNG::stageEvent10(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }
}

void C_STAGEMNG::stageData11(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 376.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(376.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (666.0f, 100.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    
    m_pDeadZone->addDeadZone(pScene);
}

void C_STAGEMNG::stageEvent11(cocos2d::Layer* pScene)
{
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(666.0f, 100.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(334.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData12(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(600.0f , 0.0f , 100.0f, GAME_HEIGHT));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (360.0f, 120.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (360.0f, 164.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (383.0f, 185.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_ALPHABG12, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_ALPHABG12, 0, Rect (0.0f, 0.0f, GAME_WIDTH, GAME_HEIGHT), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FRONTGROUND12, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FRONTGROUND12, 0, Rect (504.0f, 0.0f, 296.0f, GAME_HEIGHT), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect (460.0f, 100.0f, 50.0f, 300), pScene);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent12(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(383.0f, 185.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->removeObjectBySeq(C_OBJECTMNG::E_OBJ_ALPHABG12, 0, pScene);
        
        if(m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_VOIDBOX, 0))
        {
            m_pObject->removeObjectBySeq(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, pScene);
        }
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), 550.0f))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData13(cocos2d::Layer* pScene)
{
    m_pPlayer->setStageType(C_PLAYER::E_STAGE_CAVE);
    C_SOUNDMNG::getInstance()->playBG(SND_BG_CAVE);
    
    createShadowAndLight(pScene);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 1400.0f, 100.0f));

    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (360.0f, 120.0f, 40.0f, 44.0f), pScene);
    m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_TORCH, 0);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent13(cocos2d::Layer* pScene)
{
    if(m_pPlayer->isItem())
    {
        setLightPosition(m_pPlayer->getPosition());
        
    }
    else
    {
        if(pScene->getChildByTag(TAG_TORCH))
        {
            float fTorchMidX = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, 0)->pSprite->getBoundingBox().getMidX();
            float fTorchMidY = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_TORCH, 0)->pSprite->getBoundingBox().getMidY();
            setLightPosition(Vec2(fTorchMidX, fTorchMidY));
        }
    }
    
    //Player's Right side movement limit without NPC, item(torch)
    if((!m_pPlayer->isParty() || !m_pPlayer->isItem()) && m_pPlayer->getPositionX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(m_pPlayer->isItem() && isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData14(cocos2d::Layer* pScene)
{
    m_pPlayer->setStageType(C_PLAYER::E_STAGE_CAVE);
    
    createShadowAndLight(pScene);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 381.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(381.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (GAME_WIDTH, 100.0f, 40.0f, 44.0f), pScene);
    m_pObject->modifyObjectParent(C_OBJECTMNG::E_OBJ_TORCH, 0, pScene, m_pPlayer->getSpriteWithType(C_PLAYER::E_STAND));
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (666.0f, 100.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent14(cocos2d::Layer* pScene)
{
    setLightPosition(m_pPlayer->getPosition());
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(666.0f, 100.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(344.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData15(cocos2d::Layer* pScene)
{
    m_pPlayer->setStageType(C_PLAYER::E_STAGE_CAVE);
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (GAME_WIDTH, 100.0f, 40.0f, 44.0f), pScene);
    
    m_pObject->modifyObjectParent(C_OBJECTMNG::E_OBJ_TORCH, 0, pScene, m_pPlayer->getSpriteWithType(C_PLAYER::E_STAND));
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect (610.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent15(cocos2d::Layer* pScene)
{
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData16(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent16(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData17(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 465.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(465.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (430.0f, 164.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (450.0f, 182.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0, Rect (290.0f, 100.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent17(cocos2d::Layer* pScene)
{
    auto _ObjBtnRed = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0);
    
    bool _isCollusionRedPlayer = isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnRed->pSprite->getBoundingBox());
    
    bool _isCollusionRedNPC = isCollusion(m_pNPCWoman->getPositionFoot(), _ObjBtnRed->pSprite->getBoundingBox());
    
    
    if(_isCollusionRedPlayer || _isCollusionRedNPC)
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0, Rect(290.0f, 100.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0);
        m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect(350.0f, 120.0f, 80.0f, 30.0f), pScene);
    }
    else
    {
        Vector <Node*> &nodes = pScene->getChildren();
        
        if(m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_FLOOR, 1))
        {
            for(auto &node : nodes)
            {
                if(node->getTag() == TAG_FOOR)
                {
                    if(node == m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_FLOOR, 1)->pSprite)
                    {
                        m_pObject->removeObject(C_OBJECTMNG::E_OBJ_FLOOR, 1, pScene);
                        break;
                    }
                }
            }
        }
        
        m_pObject->unlockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0);
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_RED, 0, Rect(290.0f, 100.0f, 30.0f, 10.0f), Rect(0.0f, 0.0f, 30.0f, 12.0f), pScene);
        
        
    }
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(450.0f, 182.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(430.0f, 50.0f, 128.0f, 54.0f), pScene);
    }

    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData18(cocos2d::Layer* pScene)
{
    C_SOUNDMNG::getInstance()->playEffectOnce(SND_EF_WOLF);
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
        m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent18(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData19(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 450.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(450.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (50.0f, 130.0f, 40.0f, 44.0f), pScene);
    m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_TORCH, 0);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 1, Rect (750.0f, 130.0f, 40.0f, 44.0f), pScene);
    m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_TORCH, 1);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect (295.0f, 81.0f, 174.0f, 124.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 1, Rect (530.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (190.0f, 130.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (450.0f, 174.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (700.0f, 100.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent19(cocos2d::Layer* pScene)
{
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    auto _ObjBtnBlue = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(700.0f, 100.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(415.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData20(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 224.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(224.0f + 75.0f, 0.0f , 558.0f - 224.0f - 75.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(558.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 4);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (162.0f, 124.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (208.0f, 152.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 2, Rect (539.0f, 152.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 3, Rect (603.0f, 124.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (235.0f, 173.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (559.0f, 173.0f, 30.0f, 10.0f), pScene);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 2);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent20(cocos2d::Layer* pScene)
{
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(235.0f, 173.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(184.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect(559.0f, 173.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 1, Rect(511.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData21(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 219.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(219.0f + 150.0f, 0.0f , 740.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 3);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (258.0f, 155.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (338.0f, 155.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 2, Rect (414.0f, 121.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (144.0f, 99.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (434.0f, 140.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (272.0f, 205.0f, 40.0f, 44.0f), pScene);
    m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_TORCH, 0);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect (630.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 2);
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent21(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(144.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(260.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect(434.0f, 140.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 1, Rect(184.0f, 50.0f, 128.0f, 54.0f), pScene);

    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
            checkCollutionBushAndTorch(pScene);
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData22(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f , 0.0f , 220.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(220.0f + 75.0f, 0.0f , 555.0f - 220.0f - 75.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(555.0f + 73.0f, 0.0f , 740.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 3);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (210.0f, 130.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (230.0f, 210.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 2, Rect (634.0f, 320.0f, 80.0f, 30.0f), pScene);


    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 3);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (344.0f, 99.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (250.0f, 228.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2, Rect (660.0f, 99.0f, 30.0f, 10.0f), pScene);

    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect(650.0f, 373.0f, 40.0f, 44.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect(300.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 2);
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent22(cocos2d::Layer* pScene)
{
    
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(344.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 1, Rect(520.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect(250.0f, 228.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(189.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    auto _ObjBtnBlue2 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue2->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2, Rect (660.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
        m_pObject->removeObject(C_OBJECTMNG::E_OBJ_FLOOR, 2, pScene);
    }

    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData23(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 427.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(427.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (430.0f, 320.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (503.0f, 99.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (660.0f, 99.0f, 30.0f, 10.0f), pScene);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect(440.0f, 373.0f, 40.0f, 44.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect(600.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent23(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(503.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->removeObject(C_OBJECTMNG::E_OBJ_FLOOR, 0, pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (660.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(392.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);
            
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData24(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 292.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(292.0f + 75.0f, 0.0f , 740.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 4);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (300.0f, 420.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (70.0f, 120.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 2, Rect (210.0f, 200.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 3, Rect (250.0f, 240.0f, 80.0f, 30.0f), pScene);

    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (250.0f, 220.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (660.0f, 99.0f, 30.0f, 10.0f), pScene);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect(320.0f, 470.0f, 40.0f, 44.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect(100.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 1);

    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent24(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(250.0f, 220.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->removeObject(C_OBJECTMNG::E_OBJ_FLOOR, 0, pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (660.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(263.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);

        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData25(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 100.0f, GAME_HEIGHT));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(0.0f, 0.0f , 219.0f, 100.0f));
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(219.0f + 150.0f, 0.0f , 740.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_FLOOR, 4);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 0, Rect (157.0f, 130.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 1, Rect (280.0f, 145.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 2, Rect (220.0f, 410.0f, 80.0f, 30.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_FLOOR, 3, Rect (500.0f, 130.0f, 80.0f, 30.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 3);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect (410.0f, 99.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect (564.0f, 99.0f, 30.0f, 10.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2, Rect (184.0f, 150.0f, 30.0f, 10.0f), pScene);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_TORCH, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 0, Rect (230.0f, 460.0f, 40.0f, 44.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_TORCH, 1, Rect (723.0f, 136.0f, 40.0f, 44.0f), pScene);
    m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_TORCH, 1);
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BUSH, 2);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 0, Rect (358.0f, 81.0f, 174.0f, 124.0f), pScene);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_BUSH, 1, Rect (538.0f, 81.0f, 174.0f, 124.0f), pScene);
    
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_BRIDGE, 2);

    
    m_pPlayer->setPositionBody(10.0f, 106.2f);
    
    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    
    m_pDeadZone->addDeadZone(pScene);
}
void C_STAGEMNG::stageEvent25(cocos2d::Layer* pScene)
{
    
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    auto _ObjBtnBlue0 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue0->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0, Rect(410.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 0);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 0, Rect(260.0f, 50.0f, 128.0f, 54.0f), pScene);
    }
    
    auto _ObjBtnBlue1 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue1->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1, Rect(564.0f, 99.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 1);
        m_pObject->addObjectToSceneBySeq(C_OBJECTMNG::E_OBJ_BRIDGE, 1, Rect(184.0f, 50.0f, 128.0f, 54.0f), pScene);
        
    }
    
    auto _ObjBtnBlue2 = m_pObject->getObjectDataWithIndex(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
    
    if(isCollusion(m_pPlayer->getPositionFoot(), _ObjBtnBlue2->pSprite->getBoundingBox()))
    {
        m_pObject->modifyObjectSpriteTexture(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2, Rect(184.0f, 150.0f, 30.0f, 10.0f), Rect(30.0f, 0.0f, 30.0f, 12.0f), pScene);
        m_pObject->lockObjectModify(C_OBJECTMNG::E_OBJ_BTNSWITCH_BLUE, 2);
        m_pObject->removeObject(C_OBJECTMNG::E_OBJ_FLOOR, 2, pScene);
    }
    
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        m_pNPCWoman->controlNPC(m_pPlayer);
        m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
        m_pNPCWoman->drawNPC(m_pPlayer);
        
        if(m_pNPCWoman->isDead())
        {
            ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        }
        else
        {
            if(isCheckPoint(m_pNPCWoman->getPositionX(), GAME_WIDTH + 5))
            {
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
            
			checkCollutionBushAndTorch(pScene);
        }
    }
    
    if(pScene->getChildByTag(TAG_DEADZONE))
    {
        m_pDeadZone->moveDeadZone();
    }

}

void C_STAGEMNG::stageData26(cocos2d::Layer* pScene)
{
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
    m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect (0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);
    
    m_pPlayer->setPositionBody(10.0f, 106.2f);

    m_pNPCWoman->createNPCBodyWithSprite(Vec2(50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, 50.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);

}

void C_STAGEMNG::stageEvent26(cocos2d::Layer* pScene)
{
    //Player's Right side movement limit without NPC
    if(!m_pPlayer->isParty() && m_pPlayer->getPositionBodyX() >= GAME_WIDTH - m_pPlayer->getHalfBodyWidth())
    {
        m_pPlayer->setPositionBody(GAME_WIDTH - m_pPlayer->getHalfBodyWidth(), m_pPlayer->getPositionBodyY());
    }
    
    if(!m_pNPCWoman->isRemoteMode() && m_pPlayer->isParty() && isCheckPoint(m_pPlayer->getPositionX(), GAME_WIDTH / 2))
    {
        m_pPlayer->setPartyFalse();
        m_pNPCWoman->setRemoteMode();
        m_pNPCWoman->stopAction();
        
        m_pObject->removeBodyObject(C_OBJECTMNG::E_OBJ_VOIDBOX, 0);
    }
    
    
    
    if(m_pNPCWoman->isRemoteMode() && m_pPlayer->getPositionX() <= -50.0f)
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
        return;
    }
    
    if(pScene->getChildByTag(TAG_NPC))
    {
        if(!m_pNPCWoman->isRemoteMode())
        {
            m_pNPCWoman->controlNPC(m_pPlayer);
            m_pNPCWoman->controlFSM(m_pPlayer, m_pDeadZone, pScene);
            m_pNPCWoman->drawNPC(m_pPlayer);
        }
        else
        {
            m_pNPCWoman->remoteNPC(-80.0f);
        }
    }

}

void C_STAGEMNG::stageData27(cocos2d::Layer* pScene)
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    C_UIMNG::getInstance()->removeGameSceneUI(pScene);
	

    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));

    m_pPlayer->setPositionBody(GAME_WIDTH + 100.0f, 106.2f);
    m_pPlayer->setRemoteMode();
    m_pPlayer->stopAction();


    m_pNPCWoman->createNPCBodyWithSprite(Vec2(GAME_WIDTH + 100.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, GAME_WIDTH + 100.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    m_pNPCWoman->setRemoteMode();
    m_pNPCWoman->stopAction();

	C_SOUNDMNG::getInstance()->playBGOnce(SND_BG_ENDING);
}

void C_STAGEMNG::stageEvent27(cocos2d::Layer* pScene)
{
    m_nEventTimer += 1;

    if(m_nEventTimer < 200)
    {
        m_pNPCWoman->remoteNPC(600.0f);
        if(m_pNPCWoman->getPositionX() <= 600.0f + 7.0f)
        {
            m_pNPCWoman->setNPCFlippedX(false);
            m_pNPCWoman->stopAction();
            m_pNPCWoman->remoteNPC(m_pNPCWoman->getPositionX());
            m_nEventTimer = 300;
            //time 300~410 while NPC stop
        }
    }
    else if(m_nEventTimer >= 410)
    {
        m_pNPCWoman->remoteNPC(-80.0f);
    }
    
    if(m_pPlayer->isRemoteMode())
    {
        if(m_pNPCWoman->getPositionX() <= 0.0f)
        {
            m_pPlayer->remotePlayer(-80.0f);
        }
    }
    
    if(m_pPlayer->getSpriteWithType(C_PLAYER::E_STAND)->getPositionX() <= 0.0f - 50.f)
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
        return;
    }

}

void C_STAGEMNG::stageData28(cocos2d::Layer* pScene)
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    C_UIMNG::getInstance()->removeGameSceneUI(pScene);
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(GAME_WIDTH + 100.0f, 106.2f);
    m_pPlayer->stopAction();
    m_pPlayer->setRemoteMode();

    m_pNPCWoman->createNPCBodyWithSprite(Vec2(GAME_WIDTH + 100.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight()));
    m_pNPCWoman->createNPC(pScene, GAME_WIDTH + 100.0f, 100.0f + m_pNPCWoman->getHalfBodyHeight(), 40);
    m_pNPCWoman->setRemoteMode();
    
}
void C_STAGEMNG::stageEvent28(cocos2d::Layer* pScene)
{
    if(m_isEventLock)
    {
		if (pScene->getChildByTag(TAG_FADELAYER))
		{
			auto WhiteLayer = pScene->getChildByTag(TAG_FADELAYER);
			if (WhiteLayer->getOpacity() == 255)
			{
				setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
				return;
			}
		}
        return;
    }
    
    if(m_nEventTimer < 160)
    {
        m_pNPCWoman->remoteNPC(400.0f);
        m_nEventTimer += 1;
    }
	else if (m_nEventTimer == 160)
    {
		m_pNPCWoman->stopAction();
        m_pNPCWoman->setNPCFlippedX(false);

		auto delay3 = DelayTime::create(3.0f);
		auto callbackDead = CallFuncN::create(CC_CALLBACK_1(C_STAGEMNG::callbackWithCase, this, 1));
		auto seq = Sequence::create(delay3, callbackDead, NULL);
		m_pNPCWoman->getNPCSprite()->runAction(seq);
		m_nEventTimer += 1;
        
        
    }
    
    if(m_pNPCWoman->isDead())
    {
        m_isEventLock = true;
        
        auto WhiteLayer = LayerColor::create(Color4B(255, 255, 255, 0));
        auto FadeInAction = FadeIn::create(3);
        WhiteLayer->setTag(TAG_FADELAYER);
        pScene->addChild(WhiteLayer, TAG_FADELAYER);
        WhiteLayer->runAction(FadeInAction);
        
        m_nEventTimer = 0;
    }

}

void C_STAGEMNG::stageData29(cocos2d::Layer* pScene)
{
    C_SOUNDMNG::getInstance()->playBG(SND_BG_FOREST);
    
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    C_UIMNG::getInstance()->removeGameSceneUI(pScene);
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(355.0f, 106.2f);
    m_pPlayer->setRemoteMode();
    m_pPlayer->stopAction();
    
    if(pScene->getChildByTag(TAG_FADELAYER))
    {
        auto WhiteLayer = pScene->getChildByTag(TAG_FADELAYER);
        auto FadeOutAction = FadeOut::create(3);
        WhiteLayer->runAction(FadeOutAction);
    }
    
}

void C_STAGEMNG::stageEvent29(cocos2d::Layer* pScene)
{
    if(pScene->getChildByTag(TAG_FADELAYER))
    {
        m_pPlayer->setPlayerFlippedX(true);
        
        auto WhiteLayer = pScene->getChildByTag(TAG_FADELAYER);
        if(WhiteLayer->getOpacity() == 0)
        {
            pScene->removeChild(WhiteLayer);
        }
    }
    else
    {
        m_nEventTimer += 1;
        
        if(m_nEventTimer < 150 && m_nEventTimer >= 0)
        {
            m_pPlayer->setPlayerFlippedX(false);
        }
        else if(m_nEventTimer < 10000 && m_nEventTimer >= 150)
        {
            m_pPlayer->remotePlayer(-80.0f);
        }
        
        
        if(m_pPlayer->getPositionX() < 0.0f)
        {
            setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
            return;
        }
    }
}

void C_STAGEMNG::stageData30(cocos2d::Layer* pScene)
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    C_UIMNG::getInstance()->removeGameSceneUI(pScene);

    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(GAME_WIDTH + 100.0f, 106.2f);
    m_pPlayer->setRemoteMode();
    
}

void C_STAGEMNG::stageEvent30(cocos2d::Layer* pScene)
{
    m_pPlayer->remotePlayer(-80.0f);
    
    if(m_pPlayer->getPositionX() < 0.0f)
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
        return;
    }
}

void C_STAGEMNG::stageData31(cocos2d::Layer* pScene)
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ALL_AT_ONCE);
    C_UIMNG::getInstance()->removeGameSceneUI(pScene);
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));
    
    m_pPlayer->setPositionBody(GAME_WIDTH + 100.0f, 106.2f);
    m_pPlayer->setRemoteMode();
    
    
}
void C_STAGEMNG::stageEvent31(cocos2d::Layer* pScene)
{
    if(m_isEventLock)
    {
        if(pScene->getChildByTag(TAG_FADELAYER))
        {
            auto BlackLayer = pScene->getChildByTag(TAG_FADELAYER);
            
            if(BlackLayer->getOpacity() == 255)
            {
                pScene->removeChild(BlackLayer);
                setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
                return;
            }
        }
        return;
    }
    
    float fPlayerPos = m_pPlayer->getPosition().x;
    if(fPlayerPos > 138.0f)
    {
        m_pPlayer->remotePlayer(fPlayerPos - 1);
    }
    else
    {
        m_pPlayer->stopAction();
        m_pPlayer->setPlayerFlippedX(false);
        
        m_nEventTimer += 1;
        
        if(m_nEventTimer >= 200)
        {
            auto pFadeAction = FadeIn::create(4);
            auto BlackLayer = LayerColor::create(Color4B(0, 0, 0, 0));
            BlackLayer->setTag(TAG_FADELAYER);
            pScene->addChild(BlackLayer, TAG_FADELAYER);
            BlackLayer->runAction(pFadeAction);
            
            m_isEventLock = true;
        }
        
    }
}


void C_STAGEMNG::stageDataDefaultOnePlayer(cocos2d::Layer* pScene)
{
    
    m_pTerrain->createTerrain(C_TERRAIN::E_VOID_BOX, Rect(-100.0f , 0.0f , 1400.0f, 100.0f));

	m_pObject->createObjectWithSize(C_OBJECTMNG::E_OBJ_VOIDBOX, 1);
	m_pObject->addObjectToScene(C_OBJECTMNG::E_OBJ_VOIDBOX, 0, Rect(0.0f - 10.0f, 100.0f, 10.0f, 300), pScene);

    m_pPlayer->setPositionBody(50.0f, 106.2f);
    
}

void C_STAGEMNG::stageEventDefaultOnePlayer(cocos2d::Layer* pScene)
{
    
    
    if(isFalled(m_pPlayer->getPositionBodyY(), -100.0f))
    {
        ((GamePlayScene*)pScene)->changeScene((GamePlayScene*)pScene);
        return;
    }
    
    if(isCheckPoint(m_pPlayer->getPositionX(), GAME_WIDTH + 30))
    {
        setStageToScene((GamePlayScene*)pScene, m_nStageNum + 1);
        return;
    }

    
}

void C_STAGEMNG::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_STAGEMNG;
        log("C_STAGEMNG :: createInstance() : StageMng Instance created");
    }
}

void C_STAGEMNG::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_STAGEMNG :: releaseInstance() : StageMng Instance released");
    }
}

C_STAGEMNG* C_STAGEMNG::getInstance()
{
    return m_pInstance;
}


