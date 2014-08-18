//
//  FFMapLayer.cpp
//  FFDonkey
//
//  Created by pig on 14-8-16.
//
//

#include "FFMapLayer.h"

bool FFMapLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    return true;
}

void FFMapLayer::loadMapWithLevel(FFLevel *level)
{
    this->m_pLevel = level;
    this->reloadMap();
}

void FFMapLayer::reloadMap()
{
}
