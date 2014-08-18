//
//  FFBoxMan.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFBoxMan.h"

FFBoxMan* FFBoxMan::create()
{
    FFBoxMan *boxMan = new FFBoxMan();
    if (boxMan && boxMan->init()) {
        boxMan->setDirection(FFDirectionDown);
        boxMan->autorelease();
        return boxMan;
    }
    CC_SAFE_RELEASE(boxMan);
    return NULL;
}

bool FFBoxMan::init()
{
    return initWithFile("man_baby.png");
}

void FFBoxMan::setDirection(FFDirection direction)
{
    if (direction != this->direction) {
        std::string imageName = "man_baby.png";
        switch (direction) {
            case FFDirectionUp:
                imageName = "man_baby_up.png";
                break;
            case FFDirectionDown:
                imageName = "man_baby_down.png";
                break;
            case FFDirectionLeft:
                imageName = "man_baby_left.png";
                break;
            case FFDirectionRight:
                imageName = "man_baby_right.png";
                break;
                
            default:
                break;
        }
        this->initWithFile(imageName.c_str());
        this->direction = direction;
    }
}
