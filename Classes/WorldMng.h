//
//  B2World.h
//  ProjectH
//
//  Created by JungYonghoon on 2014. 10. 28..
//
//

#ifndef __WORLDMNG_H__
#define __WORLDMNG_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "cocostudio/CocoStudio.h"


class C_WORLDMNG : public b2ContactListener
{
public:
    enum E_BODY_TYPE
    {
        E_BODY_DEAFAULT,
        E_BODY_VOID_BOX,
        E_BODY_PHYSICS_TORCH,
        E_BODY_BRIDGE,
        E_BODY_FLOOR,
        E_BODY_MAX
    };
    
private:
    int m_BodyType[E_BODY_MAX];
    
    static C_WORLDMNG* m_pInstance;
    
    //this is fixtureDef's collution filter group Index data
    //player and npc is in this group, there are not collide each other
    //it must be - value
    static short CULLIDE_GROUP_PLAYER;
    
private:
    
    GLESDebugDraw *debugDraw;
    b2PolygonShape m_polygonShape;
    
private:
    
    C_WORLDMNG();
    
    C_WORLDMNG(C_WORLDMNG&);
    C_WORLDMNG& operator = (C_WORLDMNG&);
    //Do not use Copy Constructor, Destructor, Operator=
    
    float32 transPointToB2Coord(float fCocosPoint);
    float32 transPointToB2CoordDouble(float fCocosPoint);
    
public:
    
    static b2World* g_world;
    
    bool createWorld(const b2Vec2& Vec2gravity, bool isDebug);
    b2World* getB2World();
    
    //player and NPC in same collide group
    b2Body* createPlayerBodyWithSprite(cocos2d::Sprite* pSprite);
    b2Body* createNPCBodyWithSprite(cocos2d::Sprite* pSprite);
    
    
    b2Body* createBodyWithType(E_BODY_TYPE eType, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize = 0.0f, float fAddHeightSize = 0.0f);
    
    //this is collution funtion for one-way playform
    //override from parent 'b2ContactListener class'
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    
    void destroyWorld();
    
    static void createInstance();
    static void releaseInstance();
    static C_WORLDMNG* getInstance();
    
private:
    
    //those fuctions are object create fuctions
    //if need more object's body create fuction, add more and mapping pointer.
    
    //fuction pointer
    b2Body* (C_WORLDMNG::*m_pCreateBody[E_BODY_MAX])(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize, float fAddHeightSize);
    

    b2Body* createBodyVoidBox(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize, float fAddHeightSize);
    
    b2Body* createBodyPhysicsTorch(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize, float fAddHeightSize);
    
    b2Body* createBodyBridge(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize, float fAddHeightSize);
    
    b2Body* createBodyFloor(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, cocos2d::Sprite* pSprite, const cocos2d::Rect& rPos, float fAddWidthSize, float fAddHeightSize);
    
};

#endif /* defined(__ProjectH__B2World__) */
