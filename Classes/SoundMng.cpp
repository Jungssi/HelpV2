//
//  SoundMng.cpp
//  projectHelp02
//
//  Created by JungYonghoon on 2015. 3. 28..
//
//

#include "SoundMng.h"
#include "AppMacros.h"
#include "StageMng.h"

using namespace CocosDenshion;
USING_NS_CC;

C_SOUNDMNG* C_SOUNDMNG::m_pInstance = NULL;

C_SOUNDMNG::C_SOUNDMNG():
m_pSndEngine(NULL),
m_isSndOff(false)
{
}

bool C_SOUNDMNG::setSoundToggle()
{
	m_isSndOff = UserDefault::getInstance()->getBoolForKey("bool_snd_onoff");
	

	if (m_isSndOff)
	{
		UserDefault::getInstance()->setBoolForKey("bool_snd_onoff", false);
		m_isSndOff = UserDefault::getInstance()->getBoolForKey("bool_snd_onoff");

		if (m_pSndEngine->isBackgroundMusicPlaying())
		{
			m_pSndEngine->pauseBackgroundMusic();
		}
		else
		{
			if (C_STAGEMNG::getInstance()->isAllClear())
			{
				C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU_CLEAR);
			}
			else
			{
				C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU);
			}
		}
				
		m_pSndEngine->setBackgroundMusicVolume(0.0f);
		m_pSndEngine->setEffectsVolume(0.0f);

		log("C_SOUNDMNG :: setOnoff : sound toggled True to FALSE");
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey("bool_snd_onoff", true);
		m_isSndOff = UserDefault::getInstance()->getBoolForKey("bool_snd_onoff");

		if (m_pSndEngine->isBackgroundMusicPlaying())
		{
			m_pSndEngine->resumeBackgroundMusic();
			log("dd");
		}
		else
		{
			if (C_STAGEMNG::getInstance()->isAllClear())
			{
				
				C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU_CLEAR);
			}
			else
			{
				
				C_SOUNDMNG::getInstance()->playBG(SND_BG_MENU);
			}
			log("dd2");
		}
		
		m_pSndEngine->setBackgroundMusicVolume(1.0f);
		m_pSndEngine->setEffectsVolume(0.5f);

		log("C_SOUNDMNG :: setOnoff : sound toggled False to TRUE");
	}
	
	return m_isSndOff;
}


void C_SOUNDMNG::init()
{
    m_pSndEngine = SimpleAudioEngine::getInstance();

	bool isSecondPlay = UserDefault::getInstance()->getBoolForKey("bool_second_play");

	//when first play game, snd is on.
	//second and over game, snd onoff set from UserDefault Data "bool_snd_onoff" value.
	if (!isSecondPlay)
	{
		UserDefault::getInstance()->setBoolForKey("bool_second_play", true);
		UserDefault::getInstance()->setBoolForKey("bool_snd_onoff", true);
	}

	m_isSndOff = UserDefault::getInstance()->getBoolForKey("bool_snd_onoff");

	if (m_isSndOff)
	{
		m_pSndEngine->setBackgroundMusicVolume(1.0f);
		m_pSndEngine->setEffectsVolume(0.5f);
	}
	else
	{
		m_pSndEngine->setBackgroundMusicVolume(0.0f);
		m_pSndEngine->setEffectsVolume(0.0f);
	}

}

void C_SOUNDMNG::loadSoundData()
{
    m_pSndEngine->preloadBackgroundMusic(SND_BG_FOREST);
    m_pSndEngine->preloadBackgroundMusic(SND_BG_MENU);
	m_pSndEngine->preloadBackgroundMusic(SND_BG_MENU_CLEAR);
    m_pSndEngine->preloadBackgroundMusic(SND_BG_CAVE);
    m_pSndEngine->preloadBackgroundMusic(SND_BG_WIND);
    m_pSndEngine->preloadBackgroundMusic(SND_BG_ENDING);
    
    m_pSndEngine->preloadEffect(SND_EF_BRIDGE);
    m_pSndEngine->preloadEffect(SND_EF_BUSH);
    m_pSndEngine->preloadEffect(SND_EF_BUTTON);
    m_pSndEngine->preloadEffect(SND_EF_CAVESTEP);
    m_pSndEngine->preloadEffect(SND_EF_STEP);
    m_pSndEngine->preloadEffect(SND_EF_WOLF);
    m_pSndEngine->preloadEffect(SND_EF_WOO);
	

    
    log("C_SOUNDMNG :: loadSoundData() : Sound Data preload ended");
}

void C_SOUNDMNG::releaseSoundData()
{
    m_pSndEngine->stopAllEffects();
    m_pSndEngine->stopBackgroundMusic();

    m_pSndEngine->unloadEffect(SND_EF_BRIDGE);
    m_pSndEngine->unloadEffect(SND_EF_BUSH);
    m_pSndEngine->unloadEffect(SND_EF_BUTTON);
    m_pSndEngine->unloadEffect(SND_EF_CAVESTEP);
    m_pSndEngine->unloadEffect(SND_EF_STEP);
    m_pSndEngine->unloadEffect(SND_EF_WOLF);
    m_pSndEngine->unloadEffect(SND_EF_WOO);
}

void C_SOUNDMNG::setSoundVolume(float fVolumeLevel)
{
    m_pSndEngine->setBackgroundMusicVolume(fVolumeLevel);
    m_pSndEngine->setEffectsVolume(fVolumeLevel);
}

void C_SOUNDMNG::playBG(const char* SND_BG)
{
	if(!m_isSndOff)
	{
		return;
	}

    m_pSndEngine->playBackgroundMusic(SND_BG, true);
}

void C_SOUNDMNG::playBGOnce(const char* SND_BG)
{
	if(!m_isSndOff)
		{
			return;
		}

	m_pSndEngine->playBackgroundMusic(SND_BG, false);
}


void C_SOUNDMNG::resumeBG(const char* SND_BG)
{
    m_pSndEngine->resumeBackgroundMusic();
}

void C_SOUNDMNG::stopBG()
{
    m_pSndEngine->stopBackgroundMusic();
}

bool C_SOUNDMNG::isPlayBG(const char* SND_BG)
{
    return m_pSndEngine->isBackgroundMusicPlaying();
}

unsigned int C_SOUNDMNG::playEffectForever(const char* SND_EF)
{
	if (!m_isSndOff)
	{
		return 0;
	}

    int nEffectIndex = m_pSndEngine->playEffect(SND_EF, true);
    return nEffectIndex;
}

unsigned int C_SOUNDMNG::playEffectOnce(const char* SND_EF)
{
	if (!m_isSndOff)
	{
		return 0;
	}

    int nEffectIndex = m_pSndEngine->playEffect(SND_EF);
    return nEffectIndex;
}

void C_SOUNDMNG::stopEffect(unsigned int nEffectIndex)
{
    m_pSndEngine->stopEffect(nEffectIndex);
}

void C_SOUNDMNG::stopAllSound()
{
    m_pSndEngine->stopAllEffects();
    m_pSndEngine->stopBackgroundMusic();
}

void C_SOUNDMNG::createInstance()
{
    if(!m_pInstance)
    {
        m_pInstance = new C_SOUNDMNG;
        log("C_SOUNDMNG :: UIMMR Instance created");
    }
    
}

C_SOUNDMNG* C_SOUNDMNG::getInstance()
{
    return m_pInstance;
}

void C_SOUNDMNG::releaseInstance()
{
    if(m_pInstance)
    {
        delete m_pInstance;
        m_pInstance = NULL;
        log("C_SOUNDMNG :: UIMNG Instance released");
    }
}

