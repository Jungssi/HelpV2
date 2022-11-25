//
//  B2World.cpp
//  ProjectH
//
//  Created by JungYonghoon on 2014. 10. 28..
//
//


/*------------------------------------------------------------//
 *Box2D World Manager
 *
 *1.create world
 *2.create fixture per All Object which need body
 * -player, NPC, terrain, some object
 *3.override contact(collution) function
 * -for one-way plaform
 *4.include Box2D debug mode
 *
 *-------------------------------------------------------------//
 */

#include "WorldMng.h"
#include "AppMacros.h"
#include "Terrain.h"
#include "NpcWoman.h"

USING_NS_CC;

C_WORLDMNG* C_WORLDMNG::m_pInstance = NULL;
b2World* C_WORLDMNG:: g_world = NULL;

//it must be - value
short C_WORLDMNG::CULLIDE_GROUP_PLAYER = -8;

C_WORLDMNG::C_WORLDMNG():
debugDraw(NULL),
m_polygonShape()
{
    for(int i = E_BODY_DEAFAULT; i < E_BODY_MAX; i++)
    {
        m_BodyType[i] = 0;
    }
    
    m_pCreateBody[E_BODY_VOID_BOX]      = &C_WORLDMNG::createBodyVoidBox;
    m_pCreateBody[E_BODY_PHYSICS_TORCH] = &C_WORLDMNG::createBodyPhysicsTorch;
    m_pCreateBody[E_BODY_BRIDGE]        = &C_WORLDMNG::createBodyBridge;
    m_pCreateBody[E_BODY_FLOOR]         = &C_WORLDMNG::createBodyFloor;
}

bool C_WORLDMNG::createWorld(const b2Vec2& Vec2gravity, bool isDebug)
{
    
    if(g_world){
        log("C_WORLDMNG :: World has already been created, world creating failed..");
        return false;
    }
    
    g_world = new b2World(Vec2gravity);
    g_world->SetAllowSleeping(true);
    g_world->SetContinuousPhysics(true);
    
    
    if(isDebug)
    {
        //debug mode visual settings
        
        debugDraw = new GLESDebugDraw(PTM_RATIO);
        g_world->SetDebugDraw(debugDraw);
        
        uint32  flags  =  0 ;
        flags +=  b2Draw::e_shapeBit ;
        //flags += b2Draw::e_jointBit;
        //flags += b2Draw::e_aabbBit;
        //flags += b2Draw::e_pairBit;
        //flags += b2Draw::e_centerOfMassBit;
        debugDraw->SetFlags (flags);
    }
    
    
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    
    b2Body *groundBody = g_world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    
    boxShapeDef.shape = &groundEdge;
    
    int _nVoidSpace = 300;
    
    groundEdge.Set(b2Vec2((0 - _nVoidSpace) / PTM_RATIO, (0 - _nVoidSpace) / PTM_RATIO), b2Vec2((GAME_WIDTH + _nVoidSpace) / PTM_RATIO, (0 - _nVoidSpace) / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    //down
    
    groundEdge.Set(b2Vec2((0 - _nVoidSpace) / PTM_RATIO, 0 - _nVoidSpace / PTM_RATIO), b2Vec2((0 - _nVoidSpace) / PTM_RATIO, (GAME_HEIGHT + _nVoidSpace) / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    //left
    
    groundEdge.Set(b2Vec2((GAME_WIDTH + _nVoidSpace) / PTM_RATIO, (0 - _nVoidSpace) / PTM_RATIO), b2Vec2((GAME_WIDTH + _nVoidSpace) / PTM_RATIO, (GAME_HEIGHT + _nVoidSpace) / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    //right
    
    groundEdge.Set(b2Vec2((GAME_WIDTH + _nVoidSpace) / PTM_RATIO, (GAME_HEIGHT + _nVoidSpace)/ PTM_RATIO), b2Vec2((0 - _nVoidSpace) / PTM_RATIO, (GAME_HEIGHT + _nVoidSpace) / PTM_RATIO));
    groundBody->CreateFixture(&boxShapeDef);
    //up
    
    log("C_WORLDMNG :: World created!");
    
    return true;
}

b2World* C_WORLDMNG::getB2World()
{
    return g_world;
}

b2Body* C_WORLDMNG::createPlayerBodyWithSprite(cocos2d::Sprite* pSprite)
{
    if(!g_world)
    {
        log("world is not created, Creating player body failed");
        return NULL;
    }
    
    if(C_PLAYER::getInstance()->getPlayerBody())
    {
        log("C_WORLDMNG :: createPlayerBodyWithSprite() : player body has already been created");
        return C_PLAYER::getInstance()->getPlayerBody();
    }
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pSprite->getPositionX() / PTM_RATIO, pSprite->getPositionY() / PTM_RATIO);
    
    pSprite->setAnchorPoint(Vec2(0.5f, 0.06f));
    bodyDef.userData = pSprite;
    
    b2Body* pBody = g_world->CreateBody(&bodyDef);
    
    m_polygonShape.SetAsBox(pSprite->getBoundingBox().size.width / 3.0f / (PTM_RATIO * 2), pSprite->getBoundingBox().size.height / 9.0f / (PTM_RATIO * 2));
    
    b2FixtureDef fixtureDef;
    
    fixtureDef.shape = &m_polygonShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.7f;
    fixtureDef.restitution = 0.0f;
    //collide group setting
    fixtureDef.filter.groupIndex = CULLIDE_GROUP_PLAYER;
    
    pBody->CreateFixture( &fixtureDef );
    pBody->SetFixedRotation(true);
    
    
    
    
    
    float width = (pSprite->getBoundingBox().size.width / 3.0f / (PTM_RATIO )) / 2;
    float height = (pSprite->getBoundingBox().size.height / 9.0f / (PTM_RATIO )) / 2;
    
    b2Vec2 verts[4];
    
    verts[0].Set( width , -height + 0.01f);
    verts[1].Set( width , height);
    verts[2].Set( -width, height);
    verts[3].Set( -width, -height + 0.01f);
    
    
    
    
    
    b2BodyDef BodyDefwall;
    BodyDefwall.position.Set(pSprite->getPositionX() / PTM_RATIO, pSprite->getPositionY() / PTM_RATIO);
    
    
    b2EdgeShape wallEdge;
    b2FixtureDef wallFixDef;
    
    wallFixDef.shape = &wallEdge;
    fixtureDef.density = 0.0f;
    wallFixDef.friction = 0.0f;
    wallFixDef.filter.groupIndex = CULLIDE_GROUP_PLAYER;
    
    b2Vec2 b2Vec2add = b2Vec2(0.0f, 0.0f);
    
    wallEdge.Set(verts[0] + b2Vec2add, verts[1] + b2Vec2add);
    pBody->CreateFixture(&wallFixDef);
    
    wallEdge.Set(verts[2] - b2Vec2add, verts[3] - b2Vec2add);
    pBody->CreateFixture(&wallFixDef);
    
    
    
    
   
    log("C_WORLDMNG :: Player b2Body created!");
    
    return pBody;
}

b2Body* C_WORLDMNG::createNPCBodyWithSprite(cocos2d::Sprite* pSprite)
{
    if(!g_world)
    {
        log("world is not created, Creating player body failed");
        return NULL;
    }
    
    if(C_NPCWOMAN::getInstance()->getNPCBody())
    {
        log("C_WORLDMNG :: createNPCBodyWithSprite() : NPC body has already been created");
        return C_NPCWOMAN::getInstance()->getNPCBody();
    }
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pSprite->getPositionX() / PTM_RATIO, pSprite->getPositionY() / PTM_RATIO);
    
    bodyDef.userData = pSprite;
    
    b2Body* pBody = g_world->CreateBody(&bodyDef);
    
    m_polygonShape.SetAsBox(pSprite->getBoundingBox().size.width / (PTM_RATIO * 2), pSprite->getBoundingBox().size.height / (PTM_RATIO * 2));
    
    b2FixtureDef fixtureDef;
    
    fixtureDef.shape = &m_polygonShape;
    fixtureDef.density = 0.8f;
    fixtureDef.friction = 0.7f;
    fixtureDef.restitution = 0.0f;
    
    //collide group setting
    fixtureDef.filter.groupIndex = CULLIDE_GROUP_PLAYER;
    
    pBody->CreateFixture( &fixtureDef );
    pBody->SetFixedRotation(true);
    

    
    log("C_WORLDMNG :: NPC b2Body created!");
    
    return pBody;
}

void C_WORLDMNG::destroyWorld()
{
    if(g_world)
    {
        delete g_world;
        g_world = NULL;
        log("C_WORLDMNG :: World destroyed!");
    }
    
    if(debugDraw)
    {
        delete debugDraw;
        debugDraw = NULL;
    }
}

void C_WORLDMNG::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_WORLDMNG;
        log("C_WORLDMNG :: b2World Instance created");
    }
}

void C_WORLDMNG::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_WORLDMNG :: b2World Instance released");
    }
}

C_WORLDMNG* C_WORLDMNG::getInstance()
{
    return m_pInstance;
}

float32 C_WORLDMNG::transPointToB2Coord(float fCocosPoint)
{
    float32 _fResult = 0;
    
    _fResult = fCocosPoint / PTM_RATIO;
    
    return _fResult;
}

float32 C_WORLDMNG::transPointToB2CoordDouble(float fCocosPoint)
{
    float32 _fResult = 0;
    
    _fResult = fCocosPoint / (PTM_RATIO * 2);
    
    return _fResult;

}

void C_WORLDMNG::BeginContact(b2Contact* contact)
{
    
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    
    //check if one of the fixtures is the platform
    b2Fixture* platformFixture = NULL;
    b2Fixture* otherFixture = NULL;
    
    if ( fixtureA->GetUserData()) {
        platformFixture = fixtureA;
        otherFixture = fixtureB;
    }
    else if ( fixtureB->GetUserData()) {
        platformFixture = fixtureB;
        otherFixture = fixtureA;
    }
    
    if ( !platformFixture )
    {
        return;
   
    }
    
    int numPoints = contact->GetManifold()->pointCount;
    b2WorldManifold worldManifold;
    contact->GetWorldManifold( &worldManifold );
    
    b2Body* platformBody = platformFixture->GetBody();
    b2Body* otherBody = otherFixture->GetBody();
    
    for (int i = 0; i < numPoints; i++) {
        b2Vec2 pointVelPlatform =
        platformBody->GetLinearVelocityFromWorldPoint( worldManifold.points[i] );
        
        b2Vec2 pointVelOther =
        otherBody->GetLinearVelocityFromWorldPoint( worldManifold.points[i] );
        
        b2Vec2 relativeVel = platformBody->GetLocalVector( pointVelOther - pointVelPlatform );
        
        //if other body's vector is -y value from a playform's vector position, it collides
        //else, it's not collides
        if ( relativeVel.y < -2 )
        {
            return;
        }
   
    }

    contact->SetEnabled(false);
}


void C_WORLDMNG::EndContact(b2Contact* contact)
{
    contact->SetEnabled(true);
}

b2Body* C_WORLDMNG::createBodyWithType(E_BODY_TYPE eType, Sprite* pSprite, const Rect& rPos, float fAddWidthSize, float fAddHeightSize)
{
    if(!g_world)
    {
        log("world is not created, Creating player body failed");
        return NULL;
    }
    
    float32 _f32RectPosX = transPointToB2Coord(rPos.origin.x);
    float32 _f32RectPosY = transPointToB2Coord(rPos.origin.y);
    
    b2BodyDef bodyDef;
    bodyDef.position.Set(_f32RectPosX, _f32RectPosY);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_polygonShape;
    
    fAddWidthSize = transPointToB2Coord(fAddWidthSize);
    fAddHeightSize = transPointToB2Coord(fAddHeightSize);
    
    return (this->*m_pCreateBody[eType])(&bodyDef, &fixtureDef, pSprite, rPos, fAddWidthSize, fAddHeightSize);
}



b2Body* C_WORLDMNG::createBodyVoidBox(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, Sprite* pSprite, const Rect& rPos, float fAddWidthSize, float fAddHeightSize)
{
    float32 _f32RectWidth = transPointToB2Coord(rPos.size.width);
    float32 _f32RectHeight = transPointToB2Coord(rPos.size.height);
    
    pBodyDef->type = b2_staticBody;
    
    b2Vec2 verts[4];
    
    verts[0].Set(_f32RectWidth + fAddWidthSize, 0  - fAddHeightSize);
    verts[1].Set( _f32RectWidth + fAddWidthSize, _f32RectHeight + fAddHeightSize);
    verts[2].Set(0 - fAddWidthSize, _f32RectHeight + fAddHeightSize);
    verts[3].Set(0 - fAddWidthSize, 0 - fAddHeightSize);
    m_polygonShape.Set( verts, 4 );
    
    pBodyDef->userData = NULL;
    pFixDef->shape = &m_polygonShape;
    pFixDef->density = 1.0f;
    pFixDef->friction = 0.7f;
    pFixDef->restitution = 0.0f;
    
    b2Body* pBody = g_world->CreateBody(pBodyDef);
    pBody->CreateFixture(pFixDef);
    
    
    log("C_WORLDMNG :: createBodyVoidBox() : Void Box body is created in World!");
    return pBody;
}


b2Body* C_WORLDMNG::createBodyPhysicsTorch(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, Sprite* pSprite, const Rect& rPos, float fAddWidthSize, float fAddHeightSize)
{
    float32 _f32RectWidth = transPointToB2Coord(rPos.size.width);
    float32 _f32RectHeight = transPointToB2Coord(rPos.size.height);

    
    pBodyDef->type = b2_dynamicBody;
    pBodyDef->userData = pSprite;
    
    b2Body* pBody = g_world->CreateBody(pBodyDef);
    
    b2Vec2 verts[4];
    
    verts[0].Set(_f32RectWidth + fAddWidthSize, 0  - fAddHeightSize);
    verts[1].Set( _f32RectWidth + fAddWidthSize, _f32RectHeight + fAddHeightSize);
    verts[2].Set(0 - fAddWidthSize, _f32RectHeight + fAddHeightSize);
    verts[3].Set(0 - fAddWidthSize, 0 - fAddHeightSize);
    m_polygonShape.Set( verts, 4 );
    
    pFixDef->shape = &m_polygonShape;
    pFixDef->density = 1.0f;
    pFixDef->friction = 1.0f;
    pFixDef->restitution = 0.0f;
    pFixDef->filter.groupIndex = CULLIDE_GROUP_PLAYER;
    
    

    pBody->CreateFixture( pFixDef );
    pBody->SetFixedRotation(true);
    
    log("C_WORLDMNG :: createBodyVoidBox() : Void Box body is created in World!");
    return pBody;
}

b2Body* C_WORLDMNG::createBodyBridge(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, Sprite* pSprite, const Rect& rPos, float fAddWidthSize, float fAddHeightSize)
{
    float32 _f32SprWidth = transPointToB2Coord(pSprite->getBoundingBox().size.width);
    float32 _f32SprHeight = transPointToB2Coord(pSprite->getBoundingBox().size.height);
    
    pBodyDef->type = b2_staticBody;
    
    b2Vec2 verts[6];
    
    pBodyDef->userData = pSprite;
    verts[0].Set(_f32SprWidth + fAddWidthSize, 0.0f  - fAddHeightSize);
    verts[1].Set( _f32SprWidth + fAddWidthSize, (_f32SprHeight / 1.07) + fAddHeightSize);
    verts[2].Set( _f32SprWidth - 0.4f + fAddWidthSize, _f32SprHeight + fAddHeightSize);
    verts[3].Set(0.0f +  0.4f - fAddWidthSize, _f32SprHeight + fAddHeightSize);
    verts[4].Set(0.0f - fAddWidthSize, (_f32SprHeight / 1.07) + fAddHeightSize);
    verts[5].Set(0.0f - fAddWidthSize, 0.0f - fAddHeightSize);
    m_polygonShape.Set( verts, 6 );
    
    pBodyDef->userData = pSprite;
    
    pFixDef->shape = &m_polygonShape;
    pFixDef->density = 1.0f;
    pFixDef->friction = 0.7f;
    pFixDef->restitution = 0.0f;
    
    b2Body* pBody = g_world->CreateBody(pBodyDef);
    pBody->CreateFixture(pFixDef);
    
    log("C_WORLDMNG :: createBodyTerrian() : Terrain body is created in World!");
    return pBody;
}


b2Body* C_WORLDMNG::createBodyFloor(b2BodyDef *pBodyDef, b2FixtureDef *pFixDef, Sprite* pSprite, const Rect& rPos, float fAddWidthSize, float fAddHeightSize)
{
    float32 _f32SprWidth = transPointToB2Coord(pSprite->getBoundingBox().size.width);
    float32 _f32SprHeight = transPointToB2Coord(pSprite->getBoundingBox().size.height);
    
    b2Vec2 verts[4];
    
    
    
    pBodyDef->userData = pSprite;
    verts[0].Set(_f32SprWidth + fAddWidthSize, 0  - fAddHeightSize);
    verts[1].Set( _f32SprWidth + fAddWidthSize, _f32SprHeight + fAddHeightSize);
    verts[2].Set(0 - fAddWidthSize, _f32SprHeight + fAddHeightSize);
    verts[3].Set(0 - fAddWidthSize, 0 - fAddHeightSize);
    m_polygonShape.Set( verts, 4 );
    
    pBodyDef->userData = pSprite;
    
    pFixDef->shape = &m_polygonShape;
    pFixDef->density = 1.0f;
    pFixDef->friction = 0.7f;
    pFixDef->restitution = 0.0f;
    
    b2Body* pBody = g_world->CreateBody(pBodyDef);
    
    b2Fixture* pFixture = pBody->CreateFixture( pFixDef );

    //This is one-way platform
    pFixture->SetUserData((void*)1);
    
    log("C_WORLDMNG :: createBodyFloor: Floor body is created in World!");
    return pBody;
}
