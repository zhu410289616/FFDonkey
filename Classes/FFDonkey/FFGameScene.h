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
    FFGameScene();
    ~FFGameScene();
    
    virtual bool init();
    CREATE_FUNC(FFGameScene);
    
    void menuExitCallback(CCObject* pSender);
    
public:
    unsigned int m_nLevel;
    FFMapLayer *m_pMapLayer;
};

#endif /* defined(__FFDonkey__FFGameScene__) */
