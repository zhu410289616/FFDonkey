//
//  FFDonkeyScene.h
//  FFDonkey
//
//  Created by pig on 14-8-16.
//
//

#ifndef FFDonkey_FFDonkeyScene_h
#define FFDonkey_FFDonkeyScene_h

#include "cocos2d.h"

USING_NS_CC;

class FFDonkeyScene : public cocos2d::CCLayer {
    
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void menuStartCallback(CCObject* pSender);
    
    CREATE_FUNC(FFDonkeyScene);
};

#endif
