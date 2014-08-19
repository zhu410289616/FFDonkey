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
    }
    return instance;
}

FFLevelManager::~FFLevelManager()
{
//    CC_SAFE_DELETE_ARRAY(this->m_pLevelArray);
}

bool FFLevelManager::init()
{
    bool bRet = false;
    
    do {
        this->m_pLevelArray = CCArray::create();
        this->m_pLevelArray->retain();
        
        const char *plistPath = "level.plist";
        CCArray *plistArray = CCArray::createWithContentsOfFile(plistPath);
        CCObject *object;
        CCARRAY_FOREACH(plistArray, object)
        {
            CCDictionary *dict = (CCDictionary *)object;
            FFLevel *level = new FFLevel(dict);//FFLevel::levelWithDictionary(dict);
            level->retain();
            this->m_pLevelArray->addObject(level);
        }
        
        //read data from cache
        //todo
        this->setCurrentLevel(this->m_nCurrentLevel);
        
        bRet = true;
        
    } while (0);
    
    return bRet;
}

bool FFLevelManager::setCurrentLevel(unsigned int currentLevel)
{
    if (this->m_pLevelArray->count() == 0) {
        return false;
    }
    this->m_nCurrentLevel = MAX(0, currentLevel);
    this->m_nCurrentLevel = MIN(this->m_pLevelArray->count()-1, currentLevel);
    this->m_pLevel = (FFLevel *)this->m_pLevelArray->objectAtIndex(this->m_nCurrentLevel);
    return true;
}

FFLevel* FFLevelManager::currentLevel()
{
    return this->m_pLevel;
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
