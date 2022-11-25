#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
private:
    
	bool m_isSndOn;
    bool m_isNew;
    bool m_isResume;

    
    cocos2d::Scene* m_SceneGamePlay;
    
    cocos2d::EventListenerTouchAllAtOnce* m_pTouchListener;
    
public:
    
    MenuScene();

	static cocos2d::Scene* createScene();

    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
  
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


    CREATE_FUNC(MenuScene);
    
private:
    
    void initBG();
    
    void initMenu();
    
    void initLabel();

    void changeScene();
    
    void newGame();
    void LoadGame();
    
    void scheduleCallback(float delta);
    
    void callBackNewGameYES();
    void callBackNewGameNO();
    
};

#endif // __MENU_SCENE_H__
