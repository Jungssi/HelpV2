#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"

class GamePlayScene : public cocos2d::Layer
{
    

public:
    
    enum E_BTN
    {
        E_BTN_DEFUALT,
        E_LEFT,
        E_RIGHT,
        E_USE,
        E_JUMP,
        E_MENU,
        E_BTN_MAX
    };
    
    
private:
    cocos2d::Scene* m_SceneMenu;

    cocos2d::Rect m_rBtn[E_BTN_MAX];
    bool m_bBtn[E_BTN_MAX];
    
public:

    static cocos2d::Scene* createScene();

    
public:

    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *unUsed_event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    
    void tick(float dt);
    
public:
    
    GamePlayScene();
    
    void update();

    void changeScene(Ref * sender);
    CREATE_FUNC(GamePlayScene);
    
    bool getBtn(E_BTN eBtn);
    
    
private:

    void createDebugMode(bool isDEBUG);
    void updateDebugMode(bool isDEBUG);
    
    


};

#endif // __GAMEPLAY_SCENE_H__
