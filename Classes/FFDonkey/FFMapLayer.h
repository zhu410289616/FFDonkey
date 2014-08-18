//
//  FFMapLayer.h
//  FFDonkey
//
//  Created by pig on 14-8-16.
//
//

#ifndef FFDonkey_FFMapLayer_h
#define FFDonkey_FFMapLayer_h

#include "cocos2d.h"
#include "FFLevel.h"

USING_NS_CC;

class FFMapLayer : public cocos2d::CCLayer
{
public:
    static CCScene* scene();
    
public:
    virtual bool init();
    
    void loadMapWithLevel(FFLevel *level);
    void reloadMap();
private:
    FFLevel *m_pLevel;
    CCArray *m_pMapElements;
    int m_nRowCount;
    int m_nColumnCount;
};

#endif
