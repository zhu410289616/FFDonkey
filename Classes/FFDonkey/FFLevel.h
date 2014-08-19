//
//  FFLevel.h
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#ifndef __FFDonkey__FFLevel__
#define __FFDonkey__FFLevel__

#include "cocos2d.h"

USING_NS_CC;

class FFLevel : public CCObject
{
public:
    static FFLevel *levelWithDictionary(CCDictionary *dict);
    
public:
    FFLevel(CCDictionary *dict);
    FFLevel();
    ~FFLevel();
    
    void resetMapElements();
    
public:
    int m_nLevel;
    CCString *m_pBackgroundMusic;
    CCString *m_pPushEffect;
    CCString *m_pWinEffect;
    CCArray *m_pMapElements;
    
private:
    CCString *m_pMapName;
    CCString *m_pMapString;
};

#endif /* defined(__FFDonkey__FFLevel__) */
