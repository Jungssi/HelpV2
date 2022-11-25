//
//  DeadZone.h
//  projectHelp02
//
//  Created by JungYonghoon on 2015. 3. 4..
//
//

#ifndef __projectHelp02__DeadZone__
#define __projectHelp02__DeadZone__

#include <cocos2d.h>
#include "AppMacros.h"

class C_DEADZONE
{
    
private:
    static C_DEADZONE* m_pInstance;

private:
    float m_fVelocity;
    cocos2d::DrawNode* m_pDrawNode;
    
    
private:
    
    C_DEADZONE();
    //this class is singleton pattern..
    
    C_DEADZONE(C_DEADZONE&);
    C_DEADZONE& operator = (C_DEADZONE&);
    //Do not use Copy Constructor, Destructor, Operator=
    
public:
    
    static C_DEADZONE* getInstance();
    
    static void createInstance();
    static void releaseInstance();
    
public:
    
    void init();
    void releaseDeadZone();
    
    void addDeadZone(cocos2d::Layer* pScene);
    void moveDeadZone();
    void setDeadZoneVelocity(float fSpeed);
    void removeDeadZone(cocos2d::Layer* pScene);
    
    const float getDeadZoneLength();
    
};


#endif /* defined(__projectHelp02__DeadZone__) */
