//
//  Terrain.cpp
//  projectH
//
//  Created by JungYonghoon on 2014. 10. 20..
//
//

#include "Terrain.h"
#include <cocos2d.h>
#include "GamePlayScene.h"
#include "Box2D/Box2D.h"
#include "AppMacros.h"

USING_NS_CC;

C_TERRAIN* C_TERRAIN::m_pInstance = NULL;

C_TERRAIN::C_TERRAIN():
m_lTerrain(),
m_pWorldMng(NULL)
{
    for(int i = E_TYPE_DEFAULT; i < E_TYPE_MAX; i++)
    {
        m_pTexture[i] = NULL;
    }
}

void C_TERRAIN::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_TERRAIN;
        log("C_TERRAIN :: Terrian Instance created");
    }
}

void C_TERRAIN::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_TERRAIN :: Terrian Instance released");
    }
}

C_TERRAIN* C_TERRAIN::getInstance()
{
    return m_pInstance;
}

void C_TERRAIN::init(C_WORLDMNG* pWorldMng)
{
    m_pWorldMng = pWorldMng;
}

void C_TERRAIN::loadTexture()
{
    m_pTexture[E_VOID_BOX] = nullptr;
    m_pTexture[E_GREENBOX] = Director::getInstance()->getTextureCache()->addImage("image/terrain_test01.png");
}

void C_TERRAIN::createTerrain(E_TERRAIN_TYPE eType, const Rect& rLocation)
{
    
    S_TERRAIN *pData = new S_TERRAIN;
    
    pData->S_TERRAIN::pBody = NULL;
    pData->S_TERRAIN::pSprite = NULL;
    pData->S_TERRAIN::rPos = rLocation;
    
    switch (eType) {
        case E_VOID_BOX:
            pData->S_TERRAIN::pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_VOID_BOX, pData->S_TERRAIN::pSprite, pData->S_TERRAIN::rPos);
            break;
        case E_GREENBOX:
            pData->S_TERRAIN::pSprite = Sprite::createWithTexture(m_pTexture[eType]);
            drawSpriteAtRect(pData->S_TERRAIN::pSprite, pData->S_TERRAIN::rPos);
            pData->S_TERRAIN::pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_BRIDGE, pData->S_TERRAIN::pSprite, pData->S_TERRAIN::rPos);
            break;
        default:
            break;
    }
    
    
    m_lTerrain.push_back(pData);
    log("C_TERRAIN :: createTerrain() : Terrain List Data push backed!");
}

void C_TERRAIN::addAllTerrainSpriteToSceane(Layer* pScene)
{

    //addNewSpriteAtPosition(nullptr, Point(640.0f, 0.0f), 1280.0f, 310.0f);
    std::list<S_TERRAIN*>::iterator it;
        
    for(it = m_lTerrain.begin(); it != m_lTerrain.end(); it++)
    {
        if((*it)->pSprite)
        {
            pScene->addChild((*it)->pSprite, TAG_TERRAIN);
            
        }
    }
    log("C_TERRAIN :: addAllTerrainToSceane() : All Terrains Sprite Added in Node!");
}

void C_TERRAIN::releaseAllTerrain(Layer* pScene)
{
    std::list<S_TERRAIN*>::iterator it;
    
    for(it = m_lTerrain.begin(); it != m_lTerrain.end(); it++)
    {
        pScene->removeChild((*it)->pSprite);
        
        Sprite* pSpr = (Sprite*)(*it)->pBody->GetUserData();
        pScene->removeChild(pSpr);
        
        C_WORLDMNG::g_world->DestroyBody((*it)->pBody);
        (*it)->pBody = NULL;
        
        delete *it;
        *it = NULL;

    }
    
    m_lTerrain.clear();
    
    log("C_TERRAIN :: releaseAllTerrain() : All Teerain lists Data deleted!");
}

std::list<C_TERRAIN::S_TERRAIN*>& C_TERRAIN::getTerrainList()
{
    return m_lTerrain;
}

