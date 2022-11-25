//
//  ObjectMng.cpp
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 17..
//
//

#include "ObjectMng.h"
#include "AppMacros.h"
#include "GamePlayScene.h"
#include "SoundMng.h"

USING_NS_CC;

C_OBJECTMNG* C_OBJECTMNG::m_pInstance = NULL;

C_OBJECTMNG::C_OBJECTMNG():
m_pWorldMng(NULL)
{
    for(int i = E_OBJ_DEFAULT; i < E_OBJ_MAX; i++)
    {
        m_pTexture[i] = NULL;
    }
    
    m_pCreateObject[E_OBJ_BRIDGE]         = &C_OBJECTMNG::createBridge;
    m_pCreateObject[E_OBJ_FLOOR]          = &C_OBJECTMNG::createFloor;
    m_pCreateObject[E_OBJ_BTNSWITCH_RED]  = &C_OBJECTMNG::createBtnswitchRed;
    m_pCreateObject[E_OBJ_BTNSWITCH_BLUE] = &C_OBJECTMNG::createBtnswitchBlue;
    m_pCreateObject[E_OBJ_BUSH]           = &C_OBJECTMNG::createBush;
    m_pCreateObject[E_OBJ_TORCH]          = &C_OBJECTMNG::createTorch;
    m_pCreateObject[E_OBJ_PHYSICSS_TOURCH]= &C_OBJECTMNG::createPhysicsTorch;
    m_pCreateObject[E_OBJ_ALPHABG12]      = &C_OBJECTMNG::createAlphaBG12;
    m_pCreateObject[E_OBJ_FRONTGROUND12]  = &C_OBJECTMNG::createFrontGround12;
    m_pCreateObject[E_OBJ_VOIDBOX]        = &C_OBJECTMNG::createVoidBox;
}


void C_OBJECTMNG::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_OBJECTMNG;
        log("C_OBJECTMNG :: Object Manager Instance created");
    }
}

void C_OBJECTMNG::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_OBJECTMNG :: Object Manager Instance released");
    }
}

C_OBJECTMNG* C_OBJECTMNG::getInstance()
{
    return m_pInstance;
}

void C_OBJECTMNG::init(C_WORLDMNG* pWorldMng)
{
    m_pWorldMng = pWorldMng;
}

void C_OBJECTMNG::loadTexture()
{
    m_pTexture[E_OBJ_TYPE::E_OBJ_BRIDGE] = Director::getInstance()->getTextureCache()->addImage("image/obj_bridge.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_FLOOR] = Director::getInstance()->getTextureCache()->addImage("image/obj_floor.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_BTNSWITCH_RED] = Director::getInstance()->getTextureCache()->addImage("image/obj_button_red.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_BTNSWITCH_BLUE] = Director::getInstance()->getTextureCache()->addImage("image/obj_button_blue.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_BUSH] = Director::getInstance()->getTextureCache()->addImage("image/obj_bush.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_TORCH] = Director::getInstance()->getTextureCache()->addImage("image/obj_torch.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_PHYSICSS_TOURCH] = Director::getInstance()->getTextureCache()->addImage("image/obj_torch.png");
    m_pTexture[E_OBJ_TYPE::E_OBJ_ALPHABG12] = Director::getInstance()->getTextureCache()->addImage("image/obj_alphabg_12.png");
    
    //It must modify!!!!!!!!
    m_pTexture[E_OBJ_TYPE::E_OBJ_FRONTGROUND12] = Director::getInstance()->getTextureCache()->addImage("image/obj_front_ground_12.png");
    
    m_pTexture[E_OBJ_TYPE::E_OBJ_VOIDBOX] = Director::getInstance()->getTextureCache()->addImage("image/obj_voidbox.png");
    
    log("C_OBJECTMNG :: loadTexture() : Object Textures Loaded");
}


void C_OBJECTMNG::releaseTexture()
{
    for(int i = E_OBJ_DEFAULT + 1; i < E_OBJ_MAX; i++){
        Director::getInstance()->getTextureCache()->removeTexture(m_pTexture[i]);
    }
}

void C_OBJECTMNG::createObjectWithSize(E_OBJ_TYPE eType, int nMaxSize)
{

    m_vObjectData[eType].reserve(nMaxSize);
    m_vObjectData[eType].resize(nMaxSize);
    
    for(int i = 0; i < m_vObjectData[eType].size(); i++)
    {
        S_OBJECT *pData = new S_OBJECT;
        pData->S_OBJECT::pSprite = NULL;
        pData->S_OBJECT::pBody = NULL;
        pData->S_OBJECT::pAnimation = NULL;
        pData->S_OBJECT::pAnimate = NULL;
        pData->S_OBJECT::pRepeatForever = NULL;
        pData->S_OBJECT::nType = 0;
        pData->S_OBJECT::nSoundIndex = 0;
        pData->S_OBJECT::isLock = false;
        
        m_vObjectData[eType][i] = pData;
    }
    log("C_OBJECTMNG :: createObjectWithSize() : Object created with Size.");
}

void C_OBJECTMNG::addObjectToScene(E_OBJ_TYPE eType, int nIndex, const Rect& pLocation, Node* pNode)
{
    if(m_vObjectData[eType][nIndex]->pSprite)
    {
        return;
    }

    (this->*m_pCreateObject[eType])(nIndex, pLocation, pNode);
    
}

void C_OBJECTMNG::addObjectToSceneBySeq(E_OBJ_TYPE eType, int nIndex, const cocos2d::Rect& pLocation, cocos2d::Node* pNode)
{
    if(m_vObjectData[eType][nIndex]->pSprite)
    {
        return;
    }
    
    (this->*m_pCreateObject[eType])(nIndex, pLocation, pNode);
    
    cocos2d::FadeIn* pFadeIn;
    pFadeIn = FadeIn::create(1.0f);
    m_vObjectData[eType][nIndex]->pSprite->runAction(pFadeIn);
}

std::vector<C_OBJECTMNG::S_OBJECT*>* C_OBJECTMNG::getObjectArrayWithType(E_OBJ_TYPE eType)
{
    return &m_vObjectData[eType];
}

C_OBJECTMNG::S_OBJECT* C_OBJECTMNG::getObjectDataWithIndex(E_OBJ_TYPE eType, int nIndex)
{
    return m_vObjectData[eType][nIndex];
}

void C_OBJECTMNG::removeObjectBySeq(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pNode)
{
    S_OBJECT* tempObject = m_vObjectData[eType][nIndex];
    if(!tempObject || !tempObject->pSprite)
    {
        //not data
        return;
    }

	if (tempObject->isLock)
	{
        //locked
		return;
	}

	tempObject->isLock = true;
    
    tempObject->nType = (int)eType;
    
    //struct's sprite's userData setting to eType
    tempObject->pSprite->setUserData((void*) &(tempObject->nType));
    
    //Remove Actions
    cocos2d::Sequence* pSeqRemove;
    cocos2d::CallFuncN* pCallBack;
    cocos2d::FadeOut* pFadeOut;
    
    if(eType == E_OBJ_BUSH)
    {
        tempObject->nSoundIndex = C_SOUNDMNG::getInstance()->playEffectOnce(SND_EF_BUSH);
    }
    
    pCallBack = CallFuncN::create(CC_CALLBACK_1(C_OBJECTMNG::callBackFuncRemoveObject, this, nIndex));
    
    pFadeOut = FadeOut::create(2.0f);
    
    pSeqRemove = Sequence::create(pFadeOut, pCallBack, NULL);
    tempObject->pSprite->runAction(pSeqRemove);
}

void C_OBJECTMNG::callBackFuncRemoveObject(cocos2d::Node *pSender, int nIndex)
{
    Sprite *pSpr = (Sprite*)pSender;
    
    if(!pSpr)
    {
        //object has been already removed.
        return;
    }
    
    int *eType = (int*)pSpr->getUserData();
    Node *pParent = pSpr->getParent();
    
    removeObject((E_OBJ_TYPE)*eType, nIndex, pParent);
}

void C_OBJECTMNG::removeObject(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pNode)
{
    //if called removeObjectBySeq in a row, which function uses removed object's data
    if(eType <= E_OBJ_DEFAULT || eType > E_OBJ_MAX)
    {
        log("C_OBJECTMNG :: removeObject : invalid parameter..");
        return;
    }
    
    S_OBJECT* pTempStruct = m_vObjectData[eType][nIndex];
    
	if (!pTempStruct || !pTempStruct->pSprite)
    {
        return;
    }
    
    pNode->removeChild(pTempStruct->pSprite, false);
    
    if(pTempStruct->pSprite)
    {
        pNode->removeChild(pTempStruct->pSprite, false);
        pTempStruct->pSprite->release();
        pTempStruct->pSprite = NULL;
    }
    
    if(pTempStruct->pBody)
    {
        C_WORLDMNG::g_world->DestroyBody(pTempStruct->pBody);
        pTempStruct->pBody = NULL;
    }
    
    if(pTempStruct->pAnimation)
    {
        pTempStruct->pAnimation->release();
        pTempStruct->pAnimation = NULL;
    }
    
    if(pTempStruct->pAnimate)
    {
        pTempStruct->pAnimate->release();
        pTempStruct->pAnimate = NULL;
    }
    
    
    if(pTempStruct->pRepeatForever)
    {
        pTempStruct->pRepeatForever->release();
        pTempStruct->pRepeatForever = NULL;
    }
    pTempStruct->nType = 0;
    
    if(pTempStruct->nSoundIndex)
    {
        C_SOUNDMNG::getInstance()->stopEffect(pTempStruct->nSoundIndex);
        pTempStruct->nSoundIndex = 0;
        
    }
    
    pTempStruct->isLock = false;
    
    log("C_OBJECTMNG :: removeObject() : Object Removed..");
    
}

void C_OBJECTMNG::releaseObject(E_OBJ_TYPE eType, int nIndex, Node* pNode)
{
    removeObject(eType, nIndex, pNode);
    
    delete m_vObjectData[eType][nIndex];
    m_vObjectData[eType][nIndex] = NULL;
    
    log("C_OBJECTMNG :: releaseObject() : Object Released..");
}


void C_OBJECTMNG::releaseAndRemoveAllObject(Layer* pScene)
{
    for(int i = E_OBJ_DEFAULT + 1; i < E_OBJ_MAX; i++)
    {
        for(int j = 0; j < m_vObjectData[i].size(); j++)
        {
            if(m_vObjectData[i][j]){
                
                if(m_vObjectData[i][j]->pSprite)
                {
                    //torch object's parent is Scene Layer or Player Sprite.
                    //so, It needs detect parent, and remove from different parent
                    if(m_vObjectData[i][j]->pSprite->getTag() == TAG_TORCH)
                    {
                        Sprite* pSprPlayer = C_PLAYER::getInstance()->getSpriteWithType(C_PLAYER::E_STAND);
                        if(pSprPlayer->getChildByTag(TAG_TORCH))
                        {
                            //when torch's parent is Player
                            pSprPlayer->removeChild(m_vObjectData[i][j]->pSprite, false);
                        }
                        else
                        {
                            //when torch's parent is Scene
                            pScene->removeChild(m_vObjectData[i][j]->pSprite, false);
                        }
                        
                    }
                    else
                    {
                        //when another object (not torch) It will be always added in Scene
                        pScene->removeChild(m_vObjectData[i][j]->pSprite, false);
                    }
                    
                    m_vObjectData[i][j]->pSprite->release();
                    m_vObjectData[i][j]->pSprite = NULL;
                }
                
                if(m_vObjectData[i][j]->pBody)
                {
                    C_WORLDMNG::g_world->DestroyBody(m_vObjectData[i][j]->pBody);
                    m_vObjectData[i][j]->pBody = NULL;
                }
                
                if(m_vObjectData[i][j]->pAnimation)
                {
                    m_vObjectData[i][j]->pAnimation->release();
                    m_vObjectData[i][j]->pAnimation = NULL;
                }
                
                if(m_vObjectData[i][j]->pAnimate)
                {
                    m_vObjectData[i][j]->pAnimate->release();
                    m_vObjectData[i][j]->pAnimate = NULL;
                }
                
                
                if(m_vObjectData[i][j]->pRepeatForever)
                {
                    m_vObjectData[i][j]->pRepeatForever->release();
                    m_vObjectData[i][j]->pRepeatForever = NULL;
                }
                
                m_vObjectData[i][j]->nType = 0;
                
                if(m_vObjectData[i][j]->nSoundIndex)
                {
                    C_SOUNDMNG::getInstance()->stopEffect(m_vObjectData[i][j]->nSoundIndex);
                    m_vObjectData[i][j]->nSoundIndex = 0;
                    
                }
                
                m_vObjectData[i][j]->isLock = false;
                
                delete m_vObjectData[i][j];
                m_vObjectData[i][j] = NULL;
            }
        }
        m_vObjectData[i].clear();
    }
    log("C_OBJECTMNG :: releaseAndRemoveAllObject() : All Object release and Remove from Scene");
}

cocos2d::Sprite* C_OBJECTMNG::createSpriteAndAddToScene(Texture2D* pTexture, const Rect& pLocation, Node* pNode, int nTAG)
{
    Sprite* _pSprTemp = Sprite::createWithTexture(pTexture);
    drawSpriteAtRect(_pSprTemp, pLocation);
    
    pNode->addChild(_pSprTemp, nTAG);

    return _pSprTemp;
}

//This is modify Texture object's sprite.
//1.remove object sprite from node
//2.get object tag
//3.release object sprite
//4.change sprite texture and create new sprite
//5.if object has action, new sprite run action
//6.set tag to new sprite
//7.add new Sprite to node
void C_OBJECTMNG::modifyObjectSpriteTexture(E_OBJ_TYPE eType, int nIndex, const Rect& pLocation, const Rect& pTextureRect, Layer* pScene)
{
    if(m_vObjectData[eType][nIndex]->isLock)
    {
        return;
    }
    
    S_OBJECT *pTempStruct = m_vObjectData[eType][nIndex];
    Texture2D *pTempTexture = m_pTexture[eType];
    
    int nTAG = pTempStruct->pSprite->getTag();

    pScene->removeChild(pTempStruct->pSprite, false);
    pTempStruct->pSprite->release();
    pTempStruct->pSprite = NULL;

    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, pTextureRect);
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    pTempStruct->pSprite->setTag(nTAG);
    pTempStruct->pSprite->retain();
    
    if(pTempStruct->pRepeatForever)
    {
        pTempStruct->pSprite->runAction(pTempStruct->pRepeatForever);
    }
    
    pScene->addChild(pTempStruct->pSprite, nTAG);
    
}

void C_OBJECTMNG::modifyObjectParent(E_OBJ_TYPE eType, int nIndex, cocos2d::Node* pDestParent, cocos2d::Node* pSrcParent)
{
    if(m_vObjectData[eType][nIndex]->isLock)
    {
        return;
    }
    
    if(m_vObjectData[eType][nIndex]->pBody)
    {
        C_WORLDMNG::g_world->DestroyBody(m_vObjectData[eType][nIndex]->pBody);
        m_vObjectData[eType][nIndex]->pBody = NULL;
    }
    
    m_vObjectData[eType][nIndex]->pSprite->setAnchorPoint(Vec2::ZERO);
    m_vObjectData[eType][nIndex]->pSprite->setPosition(Vec2::ZERO);
    
    
    pDestParent->removeChild(m_vObjectData[eType][nIndex]->pSprite, false);
    
    int _nSprTAG = m_vObjectData[eType][nIndex]->pSprite->getTag();
    
    if(_nSprTAG == TAG_TORCH)
    {
        pSrcParent->addChild(m_vObjectData[eType][nIndex]->pSprite, TAG_TORCH_USE);
    }
    else
    {
        pSrcParent->addChild(m_vObjectData[eType][nIndex]->pSprite, _nSprTAG);
    }
    
}

void C_OBJECTMNG::removeBodyObject(E_OBJ_TYPE eType, int nIndex)
{
    if(m_vObjectData[eType][nIndex]->pBody)
    {
        C_WORLDMNG::g_world->DestroyBody(m_vObjectData[eType][nIndex]->pBody);
        m_vObjectData[eType][nIndex]->pBody = NULL;
    }
}


void C_OBJECTMNG::lockObjectModify(E_OBJ_TYPE eType, int nIndex)
{
    m_vObjectData[eType][nIndex]->isLock = true;
}

void C_OBJECTMNG::unlockObjectModify(E_OBJ_TYPE eType, int nIndex)
{
    m_vObjectData[eType][nIndex]->isLock = false;
}


void C_OBJECTMNG::createBridge(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_BRIDGE][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_BRIDGE];
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture);
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    
    //BRIDGE MUST SET OPACITY!!
    //MUST USE FADEIN ACTION!
    pTempStruct->pSprite->setOpacity(0);
    pTempStruct->pSprite->retain();
    
    pNode->addChild(pTempStruct->pSprite, TAG_OBJECT);

    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_BRIDGE, pTempStruct->pSprite, pLocation, 0.0f, -3.5f);
    
    pTempStruct->nSoundIndex = C_SOUNDMNG::getInstance()->playEffectOnce(SND_EF_BRIDGE);
    
    log("C_OBJECTMNG :: createBridge() : Object Bridge added");
}

void C_OBJECTMNG::createFloor(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_FLOOR][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_FLOOR];
    
    pTempStruct->pSprite = createSpriteAndAddToScene(pTempTexture, pLocation, pNode, TAG_FOOR);
    pTempStruct->pSprite->setTag(TAG_FOOR);
    pTempStruct->pSprite->retain();
    
    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_FLOOR, pTempStruct->pSprite, pLocation, -10.0f, -10.0f);
    
    log("C_OBJECTMNG :: createFloor() : Object Floor added");
}

void C_OBJECTMNG::createBtnswitchRed(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_BTNSWITCH_RED][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_BTNSWITCH_RED];
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, Rect(0, 0, 30, 12));
    
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    pTempStruct->pSprite->setTag(TAG_BTN);
    pNode->addChild(pTempStruct->pSprite, TAG_BTN);
    pTempStruct->pSprite->retain();
    log("C_OBJECTMNG :: createBtnswitchRed() : Object Button Switch Red added");
}

void C_OBJECTMNG::createBtnswitchBlue(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_BTNSWITCH_BLUE][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_BTNSWITCH_BLUE];
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, Rect(0, 0, 30, 12));
    
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    pTempStruct->pSprite->setTag(TAG_BTN);
    pNode->addChild(pTempStruct->pSprite, TAG_BTN);
    pTempStruct->pSprite->retain();
    log("C_OBJECTMNG :: createBtnswitchBlue() : Object Button Switch Blue added");
}

void C_OBJECTMNG::createBush(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_BUSH][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_BUSH];
    
    pTempStruct->pSprite = createSpriteAndAddToScene(pTempTexture, pLocation, pNode, TAG_BUSH);
    pTempStruct->pSprite->retain();
    
    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_VOID_BOX, pTempStruct->pSprite, pTempStruct->pSprite->getBoundingBox(), -30.0f, -20.0f);
    
    log("C_OBJECTMNG :: createBush() : Object Bush added");
}

void C_OBJECTMNG::createTorch(int nIndex, const Rect& pLocation, Node* pNode)
{
   
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_TORCH][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_TORCH];
    
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, Rect(0, 0, 40, 44));
    
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    
    pTempStruct->pAnimation = Animation::create();
    pTempStruct->pAnimation->setDelayPerUnit(0.5f);
    animationCreator(pTempStruct->pAnimation, pTempTexture, 2, 2, 40, 44);
    
    pTempStruct->pAnimate = Animate::create(pTempStruct->pAnimation);
    pTempStruct->pAnimate->retain();
    
    pTempStruct->pRepeatForever = RepeatForever::create(pTempStruct->pAnimate);
    pTempStruct->pRepeatForever->retain();
    
    pTempStruct->pSprite->runAction(pTempStruct->pRepeatForever);
    
    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_PHYSICS_TORCH, pTempStruct->pSprite, pTempStruct->pSprite->getBoundingBox(), -10.0f, 15.0f);
    
    pNode->addChild(pTempStruct->pSprite, TAG_TORCH);
    pTempStruct->pSprite->setTag(TAG_TORCH);
    pTempStruct->pSprite->retain();
    log("C_OBJECTMNG :: createTorch() : Object Torch added");
}

void C_OBJECTMNG::createPhysicsTorch(int nIndex, const Rect& pLocation, Node* pNode)
{
    
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_PHYSICSS_TOURCH][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_PHYSICSS_TOURCH];
    
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, Rect(0, 0, 40, 44));
    
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    
    pTempStruct->pAnimation = Animation::create();
    pTempStruct->pAnimation->setDelayPerUnit(0.5f);
    animationCreator(pTempStruct->pAnimation, pTempTexture, 2, 2, 40, 44);
    
    pTempStruct->pAnimate = Animate::create(pTempStruct->pAnimation);
    pTempStruct->pAnimate->retain();
    
    pTempStruct->pRepeatForever = RepeatForever::create(pTempStruct->pAnimate);
    pTempStruct->pRepeatForever->retain();
    
    pTempStruct->pSprite->runAction(pTempStruct->pRepeatForever);
    
    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_PHYSICS_TORCH, pTempStruct->pSprite, pTempStruct->pSprite->getBoundingBox(), -10.0f, 15.0f);
    
    
    pNode->addChild(pTempStruct->pSprite, TAG_TORCH);
    pTempStruct->pSprite->setTag(TAG_TORCH);
    pTempStruct->pSprite->retain();
    log("C_OBJECTMNG :: createPhysicsTorch() : Object PhysicsTorch added");
}

void C_OBJECTMNG::createAlphaBG12(int nIndex, const Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_ALPHABG12][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_ALPHABG12];

    pTempStruct->pSprite = createSpriteAndAddToScene(pTempTexture, pLocation, pNode, TAG_ALPHABG);
    pTempStruct->pSprite->setTag(TAG_ALPHABG);
    pTempStruct->pSprite->retain();
    
    log("C_OBJECTMNG :: createAlphaBG12() : Object AlphaBG12 added");
}

void C_OBJECTMNG::createFrontGround12(int nIndex, const cocos2d::Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_FRONTGROUND12][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_FRONTGROUND12];
    
    pTempStruct->pSprite = Sprite::createWithTexture(pTempTexture, Rect(504.0f, 0, 296.0f, GAME_HEIGHT));
    
    drawSpriteAtRect(pTempStruct->pSprite, pLocation);
    pNode->addChild(pTempStruct->pSprite, TAG_FRONTGROUND);
    pTempStruct->pSprite->setTag(TAG_FRONTGROUND);
    pTempStruct->pSprite->retain();
    
    
    log("C_OBJECTMNG :: createFrontGround12() : Object FrontGround12 added");
}

void C_OBJECTMNG::createVoidBox(int nIndex, const cocos2d::Rect& pLocation, Node* pNode)
{
    S_OBJECT *pTempStruct = m_vObjectData[E_OBJ_VOIDBOX][nIndex];
    Texture2D *pTempTexture = m_pTexture[E_OBJ_VOIDBOX];
    
    pTempStruct->pSprite = createSpriteAndAddToScene(pTempTexture, pLocation, pNode, TAG_VOIDBOX);
    pTempStruct->pSprite->setVisible(false);
    pTempStruct->pSprite->retain();
    
    pTempStruct->pBody = m_pWorldMng->createBodyWithType(C_WORLDMNG::E_BODY_VOID_BOX, pTempStruct->pSprite, pTempStruct->pSprite->getBoundingBox());
    
    log("C_OBJECTMNG :: createVoidBox() : Object VoidBox added");
}