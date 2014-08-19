//
//  FFDonkeyScene.cpp
//  FFDonkey
//
//  Created by pig on 14-8-16.
//
//

#include "FFDonkeyScene.h"
#include "FFLevelManager.h"
#include "FFGameScene.h"

USING_NS_CC;

CCScene* FFDonkeyScene::scene()
{
    CCScene *scene = CCScene::create();
    
    FFDonkeyScene *layer = FFDonkeyScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool FFDonkeyScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *pBackground = CCSprite::create("background@2x.png");
    pBackground->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pBackground, 0);
    
    CCMenuItemFont *pStartItem = CCMenuItemFont::create("start", this, menu_selector(FFDonkeyScene::menuStartCallback));
    pStartItem->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    
//    CCMenuItemImage *pTestItem = CCMenuItemImage:create();
    
    FFLevelManager::sharedInstance();
    
    CCMenu* pMenu = CCMenu::create(pStartItem, NULL);
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu, 1);
    
    return true;
}

void FFDonkeyScene::menuStartCallback(CCObject *pSender)
{
    CCLOG("menuStartCallback...");
    
    FFLevelManager::sharedInstance()->setCurrentLevel(1);
    CCDirector::sharedDirector()->replaceScene(FFGameScene::scene());
}
