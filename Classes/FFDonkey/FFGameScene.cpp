//
//  FFGameScene.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFGameScene.h"
#include "FFLevelManager.h"

CCScene* FFGameScene::scene()
{
    CCScene *scene = CCScene::create();
    FFGameScene *layer = FFGameScene::create();
    layer->setContentSize(CCDirector::sharedDirector()->getWinSize());
    scene->addChild(layer);
    return scene;
}

bool FFGameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->m_pMapLayer = new FFMapLayer(); //FFMapLayer::create();
    this->m_pMapLayer->loadMapWithLevel(FFLevelManager::sharedInstance()->currentLevel());
    this->addChild(this->m_pMapLayer, 1);
    
    CCMenuItemFont *pExitItem = CCMenuItemFont::create("exit", this, menu_selector(FFGameScene::menuExitCallback));
    pExitItem->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    
    CCMenu* pMenu = CCMenu::create(pExitItem, NULL);
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu, 1);
    
    return true;
}

void FFGameScene::menuExitCallback(CCObject *pSender)
{
    CCLOG("menuExitCallback...");
}
