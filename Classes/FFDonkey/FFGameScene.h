//
//  FFGameScene.h
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#ifndef __FFDonkey__FFGameScene__
#define __FFDonkey__FFGameScene__

#include "cocos2d.h"
#include "FFMapLayer.h"

USING_NS_CC;

class FFGameScene : public CCLayer
{
public:
    static CCScene* scene();
    
public:
    virtual bool init();
    void menuExitCallback(CCObject* pSender);
    CREATE_FUNC(FFGameScene);
    
public:
    unsigned int m_nLevel;
private:
    FFMapLayer *m_pMapLayer;
    
};

#endif /* defined(__FFDonkey__FFGameScene__) */
