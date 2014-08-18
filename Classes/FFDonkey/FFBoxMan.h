//
//  FFBoxMan.h
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#ifndef __FFDonkey__FFBoxMan__
#define __FFDonkey__FFBoxMan__

#include "cocos2d.h"

USING_NS_CC;

#define kBoxManLength   30.0f
#define kBoxManLength_2 15.0f
#define kBoxManLength_3 10.0f
#define kBoxManLength_4 7.5f
#define kBoxManLength_5 6.0f

typedef enum FFDirection {
    FFDirectionUp,
    FFDirectionDown,
    FFDirectionLeft,
    FFDirectionRight,
    FFDirectionUnknown,
} FFDirection;

class FFBoxMan : public CCSprite
{
public:
    static FFBoxMan *create();
    
public:
    virtual bool init();
    void setDirection(FFDirection direction);
    
public:
    FFDirection direction;
};

#endif /* defined(__FFDonkey__FFBoxMan__) */
