//
//  FFLevelManager.h
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#ifndef __FFDonkey__FFLevelManager__
#define __FFDonkey__FFLevelManager__

#include "cocos2d.h"
#include "FFLevel.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FFLevelManager : CCObject
{
public:
    static FFLevelManager *sharedInstance();
    
public:
    FFLevelManager();
    ~FFLevelManager();
    
    virtual bool init();
    CREATE_FUNC(FFLevelManager);
    
    bool setCurrentLevel(unsigned int currentLevel);
    FFLevel *currentLevel();
    bool hasPrevLevel();
    bool hasNextLevel();
    FFLevel *prevLevel();
    FFLevel *nextLevel();
    
private:
    CCArray *m_pLevelArray;
    unsigned int m_nCurrentLevel;
    FFLevel *m_pLevel;
};

#endif /* defined(__FFDonkey__FFLevelManager__) */
