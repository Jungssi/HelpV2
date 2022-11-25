//
//  ObjectMng.h
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 17..
//
//

#ifndef __ProjectH__ObjectMng__
#define __ProjectH__ObjectMng__

#include <cocos2d.h>
#include "Box2D/Box2D.h"
#include "WorldMng.h"
#include "Player.h"

class C_OBJECTMNG
{
public:
    enum E_OBJ_TYPE
    {
        E_OBJ_DEFAULT,
        E_OBJ_BRIDGE,
        E_OBJ_FLOOR,
        E_OBJ_BTNSWITCH_RED,
        E_OBJ_BTNSWITCH_BLUE,
        E_OBJ_BUSH,
        E_OBJ_TORCH,
        E_OBJ_PHYSICSS_TOURCH,
        E_OBJ_ALPHABG12,
        E_OBJ_FRONTGROUND12,
        E_OBJ_VOIDBOX,
        E_OBJ_MAX
    };
    
public:
    
    struct S_OBJECT
    {
        b2Body* pBody;
        cocos2d::Sprite* pSprite;
        cocos2d::Animation* pAnimation;
        cocos2d::Animate* pAnimate;
        cocos2d::RepeatForever* pRepeatForever;

        //nType uses like 'userdata'
        int nType;
        int nSoundIndex;
        
        //for use 'once' in continuation call situation
        //ex)
        //update(float dt){
        //   if(event == true)
        //      createObject() <--It needs call once. then, use isLock
        //}
        bool isLock;
    };
    
    
private:
    static C_OBJECTMNG* m_pInstance;
    
private:
    std::vector<S_OBJECT*> m_vObjectData[E_OBJ_MAX];

private:
    
    C_OBJECTMNG();
    
    C_OBJECTMNG(C_OBJECTMNG&);
    C_OBJECTMNG& operator = (C_OBJECTMNG&);
    //Do not use Copy Constructor, Destructor, Operator=
    
    
private:
    
    C_WORLDMNG* m_pWorldMng;
    
    cocos2d::Texture2D* m_pTexture[E_OBJ_MAX];
    
public:
    
    static void createInstance();
    static void releaseInstance();
    
    static C_OBJECTMNG* getInstance();

public:
    void init(C_WORLDMNG* pWorldMng);
    
    void loadTexture();
    void releaseTexture();
    
    void createObjectWithSize(E_OBJ_TYPE eType, int nMaxSize);
    
    void addObjectToScene(E_OBJ_TYPE eType, int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    
    //add Object to Scene with fadeIn action
    void addObjectToSceneBySeq(E_OBJ_TYPE eType, int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    
    void modifyObjectSpriteTexture(E_OBJ_TYPE eType, int nIndex, const cocos2d::Rect& pLocation, const cocos2d::Rect& pTextureRect, cocos2d::Layer* pScene);
    
    //switch Object's Parent. ex)torch(Scene to Player)
    void modifyObjectParent(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pDestParent, cocos2d::Node* pSrcParent);
    
    //remove Object's Box2D fixture
    void removeBodyObject(E_OBJ_TYPE eType, int nIndex);
    
    void lockObjectModify(E_OBJ_TYPE eType, int nIndex);
    void unlockObjectModify(E_OBJ_TYPE eType, int nIndex);
    
    S_OBJECT* getObjectDataWithIndex(E_OBJ_TYPE eType, int nIndex);
    std::vector<S_OBJECT*>* getObjectArrayWithType(E_OBJ_TYPE eType);

    
    //remove Object with fadeOut action
    void removeObjectBySeq(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pNode);
    void removeObject(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pNode);
    void releaseObject(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pNode);
    
    void releaseAndRemoveAllObject(cocos2d::Layer* pScene);
    
private:
    //CallFuncN's 'CC_CALLBACK_1' support only 2 parameters, so I can't use 'removeObject' directly.(removeObject needs 3 parameters)
    void callBackFuncRemoveObject(cocos2d::Node *pSender, int nIndex);

    
private:
    cocos2d::Sprite* createSpriteAndAddToScene(cocos2d::Texture2D* pTexture, const cocos2d::Rect& pLocation, cocos2d::Node* pNode, int nTAG);
    
private:
    //CREATE OBJECT FUNCTIONS POINTER
    //create and Add to Node same time.
    //these private function pointer use by addObjectToScene, addObjectToSceneBySeq
    void (C_OBJECTMNG::*m_pCreateObject[E_OBJ_MAX])(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    
    void createBridge(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createFloor(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createBtnswitchRed(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createBtnswitchBlue(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createBush(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createTorch(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createPhysicsTorch(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createAlphaBG12(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createFrontGround12(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    void createVoidBox(int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode);
    
};

#endif /* defined(__ProjectH__ObjectMng__) */
