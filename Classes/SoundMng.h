//
//  SoundMng.h
//  projectHelp02
//
//  Created by JungYonghoon on 2015. 3. 28..
//
//

#ifndef __projectHelp02__SoundMng__
#define __projectHelp02__SoundMng__

#include <stdio.h>
#include "SimpleAudioEngine.h"




class C_SOUNDMNG
{
    
    
private:
    
    static C_SOUNDMNG* m_pInstance;
    
private:
    CocosDenshion::SimpleAudioEngine* m_pSndEngine;
	bool m_isSndOff;

private:
    
    C_SOUNDMNG();
    //this class is singleton pattern..
    
    C_SOUNDMNG(C_SOUNDMNG&);
    C_SOUNDMNG& operator = (C_SOUNDMNG&);
    //Do not use Copy Constructor, Destructor, Operator=
    
public:
    
    void init();
    void loadSoundData();
    void releaseSoundData();

	bool setSoundToggle();
    
    void setSoundVolume(float fVolumeLevel);

    void playBG(const char* SND_BG);
    void playBGOnce(const char* SND_BG);


    void resumeBG(const char* SND_BG);
    void stopBG();
    
    bool isPlayBG(const char* SND_BG);
    
    unsigned int playEffectForever(const char* SND_EF);
    unsigned int playEffectOnce(const char* SND_EF);
    void stopEffect(unsigned int nEffectIndex);
    
    void stopAllSound();
    
public:
    
    static C_SOUNDMNG* getInstance();
    
    static void createInstance();
    static void releaseInstance();
    
};



#endif /* defined(__projectHelp02__SoundMng__) */

