//
//  DeadZone.cpp
//  projectHelp02
//
//  Created by JungYonghoon on 2015. 3. 4..
//
//

#include "DeadZone.h"

USING_NS_CC;

C_DEADZONE* C_DEADZONE::m_pInstance = NULL;

C_DEADZONE::C_DEADZONE():
m_fVelocity(0.0f),
m_pDrawNode(NULL)
{

}

void C_DEADZONE::init()
{
    m_pDrawNode = DrawNode::create();
    m_pDrawNode->retain();
    m_pDrawNode->setTag(TAG_DEADZONE);
    
    m_pDrawNode->setPosition(Vec2(-GAME_WIDTH, 0.0f));
    
    Vec2 rectangle[4];
    rectangle[0] = Vec2(0.0f, 0.0f);
    rectangle[1] = Vec2(GAME_WIDTH , 0.0f);
    rectangle[2] = Vec2(GAME_WIDTH, GAME_HEIGHT);
    rectangle[3] = Vec2(0.0f, GAME_HEIGHT);
    
    Color4F tmpColor4F(255, 255, 255, 100);
    
    m_pDrawNode->drawPolygon(rectangle, 4, tmpColor4F, 0, tmpColor4F);
}


void C_DEADZONE::addDeadZone(cocos2d::Layer* pScene)
{
    m_pDrawNode->setPosition(Vec2(-GAME_WIDTH, 0.0f));
    pScene->addChild(m_pDrawNode, TAG_DEADZONE);
}

void C_DEADZONE::moveDeadZone()
{

    float fPosX = m_pDrawNode->getPositionX();
    
    if(fPosX >= 0.0f)
    {
        return;
    }
    
    m_pDrawNode->setPosition(Vec2(fPosX + 0.3f, 0.0f));
    
}

void C_DEADZONE::setDeadZoneVelocity(float fSpeed)
{
    m_fVelocity = fSpeed;
}

void C_DEADZONE::removeDeadZone(cocos2d::Layer* pScene)
{
    if(!pScene->getChildByTag(TAG_DEADZONE))
    {
        return;
    }
    
    pScene->removeChild(m_pDrawNode);
}

const float C_DEADZONE::getDeadZoneLength()
{
    return m_pDrawNode->getPosition().x + GAME_WIDTH;
}

C_DEADZONE* C_DEADZONE::getInstance()
{
    return m_pInstance;
}

void C_DEADZONE::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_DEADZONE;
        log("C_DEADZONE :: Rect Instance created");
    }
}

void C_DEADZONE::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_DEADZONE :: Rect Instance released");
    }
}
