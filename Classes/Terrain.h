//
//  Terrain.h
//  projectH
//
//  Created by JungYonghoon on 2014. 10. 20..
//
//

#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <cocos2d.h>
#include "Box2D/Box2D.h"
#include "GamePlayScene.h"
#include "WorldMng.h"

class C_TERRAIN
{
public:
    enum E_TERRAIN_TYPE
    {
        E_TYPE_DEFAULT,
        E_VOID_BOX,
        E_GREENBOX,
        E_TYPE_MAX
    };
    
public:
    
    struct S_TERRAIN
    {
        b2Body* pBody;
        cocos2d::Sprite* pSprite;
        cocos2d::Rect rPos;
    };
    
    
private:
    static C_TERRAIN* m_pInstance;
    cocos2d::Texture2D* m_pTexture[E_TYPE_MAX];
    std::list<S_TERRAIN*> m_lTerrain;
    
    C_WORLDMNG* m_pWorldMng;
    
private:
    C_TERRAIN();
    
    C_TERRAIN(C_TERRAIN&);
    C_TERRAIN& operator = (C_TERRAIN&);
    //Do not use Copy Constructor, Destructor, Operator=
    
public:
    
    static void createInstance();
    static void releaseInstance();
    static C_TERRAIN* getInstance();
    
    std::list<S_TERRAIN*>& getTerrainList();
    
    void init(C_WORLDMNG* pWorldMng);
    void loadTexture();
    void createTerrain(E_TERRAIN_TYPE eType, const cocos2d::Rect& rLocation);
    
    //if you create terrain with Sprite, use it stageEvent at last
    void addAllTerrainSpriteToSceane(cocos2d::Layer* pScene);
    
    void releaseAllTerrain(cocos2d::Layer* pScene);
    
};

#endif /* defined(__projectH__Terrain__) */
