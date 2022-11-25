/*
 * AppMecros.h
 *
 *  Created on: 2014. 9. 22.
 *      Author: jungyonghoon
 *
 * define macros and common functions
 */

#ifndef APPMACROS_H_
#define APPMACROS_H_

#include "cocos2d.h"

//Game Resolution
#define GAME_WIDTH 800
#define GAME_HEIGHT 480

//Debug Mode flag
//1 : Debug Mode on
//0 : Debug Mode off
#define IS_DEBUG 1

//Debug Mode Stage setting
//set for start stage number, This is work in only Debug Mode
//in debug mode, new game's start stage is this number.
//ex) 1 : Start stage is 1
//ex) 20 : Start stage is 20
#define DEBUG_STAGE 1

//Max Stage setting
//If you add more stages, increase number more
//This is Stage Manager's important data
#define MAX_STAGE 31


//tag for Menu Scene
#define TAG_UI_ON    10
#define TAG_UI_OFF   20
#define TAG_BG_ALPHA 5

#define TAG_MENU_DIALOG_BOX 30


//tag for GamePlay Scene
//Sprite Tag setting, It decides Sprite depth.(z buffer)
//set different number each other
//Do not use same number.
#define TAG_VOIDBOX     1
#define TAG_BG          10

#define TAG_TERRAIN     50
#define TAG_ALPHABG     60
#define TAG_OBJECT      70
#define TAG_TORCH       71
#define TAG_BTN         76
#define TAG_BUSH        77
#define TAG_FOOR        75
#define TAG_TORCH_USE   110
#define TAG_FRONTGROUND 120

#define TAG_NPC         90
#define TAG_DEBUG_TEXT  99
#define TAG_PLAYER      100

#define TAG_DEADZONE    200
#define TAG_FADELAYER   210

//for cave stage shadow, light
#define TAG_CLIPPINGNODE 500
#define TAG_SHADOWLAYER  510
#define TAG_LIGHTSTENCIL 520

#define TAG_UI 600


#if(defined _WIN32) || (defined _W64)

//sound macro
#define SND_BG_FOREST      "snd/wav/snd_forest.wav"
#define SND_BG_MENU        "snd/wav/snd_menu.wav"
#define SND_BG_MENU_CLEAR  "snd/wav/snd_menu_clear.wav"
#define SND_BG_CAVE        "snd/wav/snd_cave.wav"
#define SND_BG_WIND        "snd/wav/snd_wind.wav"
#define SND_BG_ENDING      "snd/wav/snd_ending.wav"

#define SND_EF_BRIDGE      "snd/wav/snd_bridge.wav"
#define SND_EF_BUSH        "snd/wav/snd_bush.wav"
#define SND_EF_BUTTON      "snd/wav/snd_button.wav"
#define SND_EF_CAVESTEP    "snd/wav/snd_cavestep.wav"
#define SND_EF_STEP        "snd/wav/snd_step.wav"
#define SND_EF_WOLF        "snd/wav/snd_wolf.wav"
#define SND_EF_WOO         "snd/wav/snd_woo.wav"


#else

//sound macro
#define SND_BG_FOREST      "snd/snd_forest.mp3"
#define SND_BG_MENU        "snd/snd_menu.mp3"
#define SND_BG_MENU_CLEAR  "snd/snd_menu_clear.mp3"
#define SND_BG_CAVE        "snd/snd_cave.mp3"
#define SND_BG_WIND        "snd/snd_wind.mp3"
#define SND_BG_ENDING      "snd/snd_ending.mp3"

#define SND_EF_BRIDGE      "snd/snd_bridge.mp3"
#define SND_EF_BUSH        "snd/snd_bush.mp3"
#define SND_EF_BUTTON      "snd/snd_button.mp3"
#define SND_EF_CAVESTEP    "snd/snd_cavestep.mp3"
#define SND_EF_STEP        "snd/snd_step.mp3"
#define SND_EF_WOLF        "snd/snd_wolf.mp3"
#define SND_EF_WOO         "snd/snd_woo.mp3"

#endif

//Box2d :: world per cocos2d-x resolution ratio setting, do not modify.
#define PTM_RATIO 32

//main render size
static cocos2d::Size designResolutionSize = cocos2d::Size(GAME_WIDTH, GAME_HEIGHT);


//Common functions

//draw image at Rect
static void drawSpriteAtRect(cocos2d::Sprite* pSpr, const cocos2d::Rect &location)
{
    float _fScaleWidth = 0.0f;
    float _fScaleHeight = 0.0f;
    
    pSpr->setAnchorPoint(cocos2d::Vec2::ZERO);
    pSpr->setScale(1.0f, 1.0f);
    
    _fScaleWidth =  location.size.width / pSpr->getBoundingBox().size.width;
    _fScaleHeight =  location.size.height / pSpr->getBoundingBox().size.height;
    
    pSpr->setPosition(cocos2d::Vec2(location.origin.x, location.origin.y));
    
    pSpr->setScale(_fScaleWidth, _fScaleHeight);
    
}

static void animationCreator(cocos2d::Animation* pDstAnimation, cocos2d::Texture2D* pTexture, int nMaxFrame, int nMaxColumn, int nFrameWidth, int nFrameHeight)
{
    for(int i = 0; i < nMaxFrame; i++)
    {
        int column = i % nMaxColumn;
        int row = i / nMaxColumn;
        
        pDstAnimation->addSpriteFrameWithTexture(pTexture, cocos2d::Rect(column * nFrameWidth, row * nFrameHeight, nFrameWidth, nFrameHeight));
    }
}

#endif /* __APPMACROS_H__ */
