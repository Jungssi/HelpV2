//
//  UiMng.h
//  ProjectH
//
//  Created by JungYonghoon on 2014. 12. 11..
//
//

#ifndef __ProjectH__UiMng__
#define __ProjectH__UiMng__

#include <cocos2d.h>

class C_UIMNG
{
public:
    
    enum E_UI
    {
        E_UI_DEAFUALT,
        E_UI_NEWGAME_ON,
        E_UI_NEWGAME_OFF,
        E_UI_RESUMEGAME_ON,
        E_UI_RESUMEGAME_OFF,
		E_UI_SND_ON,
		E_UI_SND_OFF,
        E_UI_MENU_BTN,
        E_UI_LEFT,
        E_UI_RIGHT,
        E_UI_USE,
        E_UI_JUMP,
        E_UI_MAX
    };
    
private:
    
    cocos2d::Texture2D* m_pTextureUiBtn[E_UI_MAX];
    cocos2d::Sprite* m_pSprUiBtn[E_UI_MAX];
    
private:
    
    static C_UIMNG* m_pInstance;
    
private:
    
    C_UIMNG();
    //this class is singleton pattern..
    
    C_UIMNG(C_UIMNG&);
    C_UIMNG& operator = (C_UIMNG&);
    //Do not use Copy Constructor, Destructor, Operator=
    
public:
    
    void loadUiData();
    void initSprites();
    
    void releaseUiData();
    
    void addMenuUI(cocos2d::Layer* pScene);
    void removeMenuUI(cocos2d::Layer* pScene);
    
    void addGameSceneUI(cocos2d::Layer* pScene);
    void removeGameSceneUI(cocos2d::Layer* pScene);
    
    cocos2d::Sprite* getSprUiBtn(int eUi);
    const cocos2d::Rect getSprUiBtnRect(int eUi);
    
public:
    
    static C_UIMNG* getInstance();
    
    static void createInstance();
    static void releaseInstance();
    
};

#endif /* defined(__ProjectH__UiMng__) */
