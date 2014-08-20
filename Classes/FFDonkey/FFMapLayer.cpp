//
//  FFMapLayer.cpp
//  FFDonkey
//
//  Created by pig on 14-8-16.
//
//

#include "FFMapLayer.h"
#include "SimpleAudioEngine.h"

bool FFMapLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    this->m_pBoxes = CCArray::createWithCapacity(5);
    this->m_pBoxes->retain();
    this->m_pBoxArray = CCArray::createWithCapacity(5);
    this->m_pBoxArray->retain();
    this->m_pDestArray = CCArray::createWithCapacity(5);
    this->m_pDestArray->retain();
    this->start = CCPointZero;
    this->end = CCPointZero;
    return true;
}

void FFMapLayer::setDelegate(FFMapLayerDelegate *delegate)
{
    this->m_pDelegate = delegate;
}

void FFMapLayer::loadMapWithLevel(FFLevel *level)
{
    this->m_pLevel = level;
    this->reloadMap();
}

void FFMapLayer::reloadMap()
{
    this->m_pBoxes->removeAllObjects();
    this->m_pBoxArray->removeAllObjects();
    this->m_pDestArray->removeAllObjects();
//    this->m_pBoxMan->removeFromParentAndCleanup(true);
    CC_SAFE_DELETE(this->m_pBoxMan);
    while (this->getChildByTag(2)) {
        this->removeChildByTag(2, true);
    }
    this->m_pLevel->resetMapElements();
    this->m_pMapElements = this->m_pLevel->m_pMapElements;
    this->m_nRowCount = this->m_pMapElements->count();
    if (this->m_nRowCount > 0) {
        CCArray *columnArray = (CCArray *)this->m_pMapElements->objectAtIndex(0);
        this->m_nColumnCount = columnArray->count();
    }
    this->loadMap();
}

#pragma mark private

void FFMapLayer::loadMap()
{
    int width = kBoxManLength * this->m_nColumnCount;
    int height = kBoxManLength * this->m_nRowCount;
    this->setContentSize(CCSizeMake(width, height));
    for (int i=0; i<this->m_nRowCount; i++) {
        CCArray *columnArray = (CCArray *)this->m_pMapElements->objectAtIndex(i);
        for (int j=0; j<this->m_nColumnCount; j++) {
            CCString *object = (CCString *)columnArray->objectAtIndex(j);
            int type = object->intValue();
            CCPoint position = this->pointAtIndexPath(FFIndexPathMake(i, j));
            CCSprite *sprite = CCSprite::create("green_road.png");
            sprite->setPosition(position);
            this->addChild(sprite, 99, 2);
            
            switch (type) {
                case FFMapElementRedHouse:
                {
                    CCSprite *treeSprite = CCSprite::create("house_red.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBlueHouse:
                {
                    CCSprite *treeSprite = CCSprite::create("house_blue.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementYellowHouse:
                {
                    CCSprite *treeSprite = CCSprite::create("house_yellow.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBluePoolUp:
                {
                    CCSprite *treeSprite = CCSprite::create("pool_up.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBluePoolDown:
                {
                    CCSprite *treeSprite = CCSprite::create("pool_down.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBluePoolLeft:
                {
                    CCSprite *treeSprite = CCSprite::create("pool_left.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBluePoolRight:
                {
                    CCSprite *treeSprite = CCSprite::create("pool_right.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_5));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementGreenTree:
                {
                    // 种树 . 如果是树的话 稍微往上 种一点
                    CCSprite *treeSprite = CCSprite::create("green_tree.png");
                    treeSprite->setPosition(ccp(position.x, position.y + kBoxManLength_4));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementScenryTree:
                {
                    // 风景树
                    CCSprite *treeSprite = CCSprite::create("scenery_tree.png");
                    treeSprite->setPosition(ccp(position.x, position.y));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementGreenShrub:
                {
                    // 绿色草垛
                    CCSprite *treeSprite = CCSprite::create("green_shrub.png");
                    treeSprite->setPosition(ccp(position.x, position.y));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementYellowFlower:
                {
                    CCSprite *treeSprite = CCSprite::create("yellow_flower.png");
                    treeSprite->setPosition(ccp(position.x, position.y));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementRedWall:
                {
                    CCSprite *treeSprite = CCSprite::create("red_wall.png");
                    treeSprite->setPosition(ccp(position.x, position.y));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementRedBarricade:
                {
                    CCSprite *treeSprite = CCSprite::create("red_barricade.png");
                    treeSprite->setPosition(ccp(position.x, position.y));
                    this->addChild(treeSprite, 991, 2);
                }
                    break;
                case FFMapElementBox:
                {
                    CCSprite *boxSprite = CCSprite::create("box.png");
                    boxSprite->setPosition(position);
                    this->addChild(boxSprite, 992, 2);
                    this->m_pBoxes->addObject(boxSprite);
                    this->m_pBoxArray->addObject(stringFromIndexPath(FFIndexPathMake(i, j)));
                }
                    break;
                case FFMapElementDst:
                {
                    CCSprite *treeSprite = CCSprite::create("balloon.png");
                    treeSprite->setPosition(position);
                    this->addChild(treeSprite, 990, 2);
                    this->m_pBoxes->addObject(stringFromIndexPath(FFIndexPathMake(i, j)));
                }
                    break;
                case FFMapElementMan:
                {
                    if (!this->m_pBoxMan) {
                        this->m_pBoxMan = FFBoxMan::create();
                        this->m_pBoxMan->setPosition(position);
                        this->addChild(this->m_pBoxMan, 993, 2);
                    }
                }
                    break;
                    
                default:
                    break;
            }//switch
        }//for
    }//for
    
    if (this->m_pDelegate) {
        this->m_pDelegate->didGameStart();
    }
    this->setTouchEnabled(true);
}

FFIndexPath FFMapLayer::indexPathAtPoint(CCPoint point)
{
    int x = point.x;
    int y = this->getContentSize().height - point.y;
    int length = kBoxManLength;
    return FFIndexPathMake(y/length, x/length);
}

CCPoint FFMapLayer::pointAtIndexPath(FFIndexPath indexPath)
{
    float x = indexPath.column * kBoxManLength;
    float y = (this->m_nRowCount - indexPath.row) * kBoxManLength;
    return ccp(x, y);
}

FFDirection FFMapLayer::directionFromPoint(CCPoint start, CCPoint end)
{
    FFDirection direction = FFDirectionUnknown;
    if (!start.equals(end)) {
        float offsetX = end.x - start.x;
        float offsetY = end.y - start.y;
        if (fabsf(offsetX) >= fabsf(offsetY)) {
            // 以X移动为准
            if (offsetX > kBoxManLength) {
                direction = FFDirectionRight;
            } else if (offsetX < -kBoxManLength) {
                direction = FFDirectionLeft;
            }
        } else {
            if (offsetY > kBoxManLength) {
                direction = FFDirectionDown;
            } else if (offsetY < -kBoxManLength) {
                direction = FFDirectionUp;
            }
        }
    }
    return direction;
}

FFMoveType FFMapLayer::shouldMoveWithDirection(FFDirection direction)
{
    FFMoveType type = FFMoveDisabled;
    FFIndexPath indexPath = this->indexPathAtPoint(this->m_pBoxMan->getPosition());
    CCArray *mapElementArray = this->m_pMapElements;
    
    switch (direction) {
        case FFDirectionUp:
        {
            if (indexPath.row >= 1) {
                if (intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row-1, indexPath.column) > FFMapElementBox) {
                    type = FFMoveEnabledWithMan;
                } else if (indexPath.row >= 2 && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row-1, indexPath.column) == FFMapElementBox && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row-2, indexPath.column) > FFMapElementBox) {
                    type = FFMoveEnabledWithBoxMan;
                }
            }
        }
            break;
        case FFDirectionDown:
        {
            if (indexPath.row <= this->m_nRowCount-2) {
                if (intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row+1, indexPath.column) > FFMapElementBox) {
                    type = FFMoveEnabledWithMan;
                } else if (indexPath.row <= this->m_nRowCount-3 && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row+1, indexPath.column) == FFMapElementBox && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row+2, indexPath.column) > FFMapElementBox) {
                    type = FFMoveEnabledWithBoxMan;
                }
            }
        }
            break;
        case FFDirectionLeft:
        {
            if (indexPath.column >= 1) {
                if (intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column-1) > FFMapElementBox) {
                    type = FFMoveEnabledWithMan;
                } else if (indexPath.column >= 2 && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column-1) == FFMapElementBox && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column-2) > FFMapElementBox) {
                    type = FFMoveEnabledWithBoxMan;
                }
            }
        }
            break;
        case FFDirectionRight:
        {
            if (indexPath.column <= this->m_nColumnCount-2) {
                if (intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column+1) > FFMapElementBox) {
                    type = FFMoveEnabledWithMan;
                } else if (indexPath.column <= this->m_nColumnCount-3 && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column+1) == FFMapElementBox && intValueFromArrayAtRowAndColumn(mapElementArray, indexPath.row, indexPath.column+2) > FFMapElementBox) {
                    type = FFMoveEnabledWithBoxMan;
                }
            }
        }
            break;
            
        default:
            break;
    }
    return type;
}

void FFMapLayer::moveManWithDirection(FFDirection direction, FFIndexPath indexPath)
{
    FFIndexPath nextIndexPath;
    switch (direction) {
        case FFDirectionUp:
        {
            nextIndexPath = FFIndexPathMake(indexPath.row - 1, indexPath.column);
        }
            break;
        case FFDirectionDown:
        {
            nextIndexPath = FFIndexPathMake(indexPath.row + 1, indexPath.column);
        }
            break;
        case FFDirectionLeft:
        {
            nextIndexPath = FFIndexPathMake(indexPath.row, indexPath.column - 1);
        }
            break;
        case FFDirectionRight:
        {
            nextIndexPath = FFIndexPathMake(indexPath.row, indexPath.column + 1);
        }
            break;
            
        default:
            break;
    }
    CCPoint position = this->pointAtIndexPath(nextIndexPath);
    CCMoveTo *moveTo = CCMoveTo::create(kMoveDuration, position);
    this->m_pBoxMan->runAction(moveTo);
    
    setArrayAtIndexPath(this->m_pMapElements, indexPath, CCString::createWithFormat("%d", FFMapElementGreenRoad));
    setArrayAtIndexPath(this->m_pMapElements, nextIndexPath, CCString::createWithFormat("%d", FFMapElementMan));
    
    //delegate
    if (this->m_pDelegate) {
        this->m_pDelegate->didBoxManMovedWithBox(false);
    }
}

void FFMapLayer::moveBoxWithDirection(FFDirection direction, FFIndexPath indexPath)
{
    FFIndexPath manIndexPath, boxIndexPath;
    switch (direction) {
        case FFDirectionUp:
        {
            manIndexPath = FFIndexPathMake(indexPath.row - 1, indexPath.column);
            boxIndexPath = FFIndexPathMake(indexPath.row - 2, indexPath.column);
        }
            break;
        case FFDirectionDown:
        {
            manIndexPath = FFIndexPathMake(indexPath.row + 1, indexPath.column);
            boxIndexPath = FFIndexPathMake(indexPath.row + 2, indexPath.column);
        }
            break;
        case FFDirectionLeft:
        {
            manIndexPath = FFIndexPathMake(indexPath.row, indexPath.column - 1);
            boxIndexPath = FFIndexPathMake(indexPath.row, indexPath.column - 2);
        }
            break;
        case FFDirectionRight:
        {
            manIndexPath = FFIndexPathMake(indexPath.row, indexPath.column + 1);
            boxIndexPath = FFIndexPathMake(indexPath.row, indexPath.column + 2);
        }
            break;
            
        default:
            break;
    }
    
    CCObject *object;
    CCARRAY_FOREACH(this->m_pBoxes, object) {
        CCSprite *sprite = (CCSprite *)object;
        FFIndexPath indexPath = this->indexPathAtPoint(sprite->getPosition());
        if (FFIndexPathEqual(manIndexPath, indexPath)) {
            CCPoint manPosition = this->pointAtIndexPath(manIndexPath);
            CCMoveTo *manMoveTo = CCMoveTo::create(kMoveDuration, manPosition);
            this->m_pBoxMan->runAction(manMoveTo);
            
            CCPoint boxPosition = this->pointAtIndexPath(boxIndexPath);
            CCMoveTo *boxMoveTo = CCMoveTo::create(kMoveDuration, boxPosition);
            sprite->runAction(boxMoveTo);
            
            int index = this->m_pBoxes->indexOfObject(sprite);
            this->m_pBoxArray->replaceObjectAtIndex(index, stringFromIndexPath(boxIndexPath));
            break;
        }
    }
    
    setArrayAtIndexPath(this->m_pMapElements, indexPath, CCString::createWithFormat("%d", FFMapElementGreenRoad));
    setArrayAtIndexPath(this->m_pMapElements, indexPath, CCString::createWithFormat("%d", FFMapElementMan));
    setArrayAtIndexPath(this->m_pMapElements, indexPath, CCString::createWithFormat("%d", FFMapElementBox));
    
    //delegate
    if (this->m_pDelegate) {
        this->m_pDelegate->didBoxManMovedWithBox(true);
    }
    
    //todo check finish
    bool finish = false;
    CCObject *boxObject;
    CCARRAY_FOREACH(this->m_pBoxArray, boxObject) {
        CCString *boxValue = (CCString *)boxObject;
        FFIndexPath boxIndexPath = indexPathFromString(boxValue);
        
        bool isContains = false;
        CCObject *destObject;
        CCARRAY_FOREACH(this->m_pDestArray, destObject) {
            CCString *destValue = (CCString *)destObject;
            FFIndexPath destIndexPath = indexPathFromString(destValue);
            isContains = FFIndexPathEqual(boxIndexPath, destIndexPath);
            if (isContains) {
                break;
            }
        }
        if (isContains) {
            finish = true;
            break;
        }
    }
    if (finish) {
        this->scheduleOnce(schedule_selector(FFMapLayer::win), kMoveDuration);
    }
}

void FFMapLayer::enabledTouch()
{
    this->setTouchEnabled(true);
}

void FFMapLayer::win()
{
    if (this->m_pDelegate) {
        this->m_pDelegate->didGameFinish();
    }
}

void FFMapLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    this->start = touch->getLocationInView();
}

void FFMapLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    this->end = touch->getLocationInView();
    FFDirection direction = this->directionFromPoint(this->start, this->end);
    if (direction != FFDirectionUnknown) {
        this->setTouchEnabled(false);
        this->m_pBoxMan->stopAllActions();
        FFIndexPath indexPath = this->indexPathAtPoint(this->m_pBoxMan->getPosition());
        FFMoveType moveType = this->shouldMoveWithDirection(direction);
        if (moveType == FFMoveEnabledWithMan) {
            this->moveManWithDirection(direction, indexPath);
        } else if (moveType == FFMoveEnabledWithBoxMan) {
            this->moveBoxWithDirection(direction, indexPath);
        }
        this->scheduleOnce(schedule_selector(FFMapLayer::enabledTouch), kMoveDuration);
    }
}

void FFMapLayer::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->start = CCPointZero;
    this->end = CCPointZero;
}
