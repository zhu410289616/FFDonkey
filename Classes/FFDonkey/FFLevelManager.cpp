//
//  FFLevelManager.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFLevelManager.h"

static FFLevelManager *instance = NULL;

FFLevelManager* FFLevelManager::sharedInstance()
{
    if (!instance) {
        instance = FFLevelManager::create();
        instance->init();
    }
    return instance;
}

FFLevelManager* FFLevelManager::create()
{
    FFLevelManager *pLevelManager = new FFLevelManager();
    if (pLevelManager) {
        pLevelManager->autorelease();
        return pLevelManager;
    }
    CC_SAFE_RELEASE(pLevelManager);
    return NULL;
}

FFLevelManager::FFLevelManager()
{
}

FFLevelManager::~FFLevelManager()
{
}

bool FFLevelManager::init()
{
    bool bRet = false;
    
    do {
        this->m_pLevelArray = CCArray::create();
        
        const char *plistPath = "level.plist";
        CCArray *plistArray = CCArray::createWithContentsOfFile(plistPath);
        CCObject *object;
        CCARRAY_FOREACH(plistArray, object)
        {
            CCDictionary *dict = (CCDictionary *)object;
            FFLevel *level = FFLevel::levelWithDictionary(dict);
            this->m_pLevelArray->addObject(level);
        }
        
        //read data from cache
        //todo
        if (plistArray->count() > 0 && this->m_nCurrentLevel < plistArray->count()) {
            this->m_pLevel = (FFLevel *)this->m_pLevelArray->objectAtIndex(this->m_nCurrentLevel);
        }
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}

bool FFLevelManager::hasPrevLevel()
{
    return (this->m_nCurrentLevel > 0);
}

bool FFLevelManager::hasNextLevel()
{
    return (this->m_nCurrentLevel < this->m_pLevelArray->count() - 1);
}

FFLevel* FFLevelManager::prevLevel()
{
    int prevLevel = this->m_nCurrentLevel - 1;
    if (prevLevel >= 0) {
        this->m_nCurrentLevel--;
        return (FFLevel *)this->m_pLevelArray->objectAtIndex(prevLevel);
    }
    return NULL;
}

FFLevel* FFLevelManager::nextLevel()
{
    int nextLevel = this->m_nCurrentLevel + 1;
    if (nextLevel < this->m_pLevelArray->count()) {
        this->m_nCurrentLevel++;
        return (FFLevel *)this->m_pLevelArray->objectAtIndex(nextLevel);
    }
    return NULL;
}
