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
#include "FFBoxMan.h"

USING_NS_CC;

#define kMoveDuration 0.3f

/**
 *  该结构体用于存储行和列，都为int值，常用语二维数组
 */
typedef struct FFIndexPath {
    int row;            //第几行
    int column;         //第几列
} FFIndexPath;

/**
 *  创建一个FFIndexPath
 *
 *  @param row    该indexPath的行，第几行
 *  @param column 该indexPath的列，第几列
 *
 *  @return 根据行，列创建的FFIndexPath
 */
static inline FFIndexPath FFIndexPathMake(int row, int column) {
    FFIndexPath indexPath;
    indexPath.row = row;
    indexPath.column = column;
    return indexPath;
}

/**
 *  行列为零 的FFIndexPath
 */
const FFIndexPath FFIndexPathZero = FFIndexPathMake(0, 0);

/**
 *  比较两个SIndexPath是否相等，如果两个FFIndexPath的行，列均相等，则认为两个FFIndexPath相等
 *
 *  @param indexPath1 indexPath1 需要比较的indexPath
 *  @param indexPath2 indexPath2 需要比较的indexPath
 *
 *  @return 返回两个indexPath的行列是否都相等
 */
static inline bool FFIndexPathEqual(FFIndexPath indexPath1, FFIndexPath indexPath2) {
    return (indexPath1.row == indexPath2.row) && (indexPath1.column == indexPath2.column);
}

/**
 *  将SIndexPath转换成字符串
 *
 *  @param indexPath 参见FFIndexPath 包含row，column
 *
 *  @return 返回根据indexPath的row，column生成的字符串 格式为[indexPath.row,indexPath.column]
 */
static inline CCString* stringFromIndexPath(FFIndexPath indexPath) {
    return CCString::createWithFormat("[%d,%d]", indexPath.row, indexPath.column);
}

/**
 *  从字符串中获取SIndexPath
 *
 *  @param string 字符串格式必须是[row,column] row,column必须是int类型
 *
 *  @return 返回 字符串解析后的indexPath
 */
static inline FFIndexPath indexPathFromString(CCString* string) {
    FFIndexPath indexPath = FFIndexPathMake(0, 0);
    std::string tempString = string->m_sString;
    if (tempString.length() > 0) {
        int begin = tempString.find_first_of("[");
        int end = tempString.find_first_of("]");
        int middle = tempString.find_first_of(",");
        CCString* row = CCString::create(tempString.substr(begin+1, middle));
        CCString* column = CCString::create(tempString.substr(middle+1, end));
        indexPath.row = row->intValue();
        indexPath.column = column->intValue();
    }
    return indexPath;
}

/**
 *  设置数组在某行某列的值
 *
 *  @param rowAndColumnArray 需要设置的二维数组数组
 *  @param indexPath         参见FFIndexPath，表示行列
 *  @param newValue          需要设置的值
 *
 *  @return 返回是否设置成功
 */
static inline bool setArrayAtIndexPath(CCArray *rowAndColumnArray, FFIndexPath indexPath, CCString *newValue) {
    bool result = false;
    if (rowAndColumnArray->count() > indexPath.row) {
        CCArray *columnArray = (CCArray *)rowAndColumnArray->objectAtIndex(indexPath.row);
        if (columnArray->count() > indexPath.column) {
            columnArray->replaceObjectAtIndex(indexPath.column, newValue);
            result = true;
        }
    }
    return result;
}

/**
 *  设置数组在某行某列的值
 *
 *  @param rowAndColumnArray 需要设置的二维数组数组
 *  @param row               需要设置的行
 *  @param column            需要设置的列
 *  @param newValue          需要设置的值
 *
 *  @return 返回是否设置成功
 */
static inline bool setArrayAtRowAndColumn(CCArray *rowAndColumnArray, int row, int column, CCString *newValue) {
    return setArrayAtIndexPath(rowAndColumnArray, FFIndexPathMake(row, column), newValue);
}

/**
 *  读取该数组中某个indexPath下的值
 *
 *  @param rowAndColumnArray 需要读取的二维数组
 *  @param indexPath         参见FFIndexPath，表示行列
 *
 *  @return 返回该行列下的值
 */
static inline CCString* valueFromArrayAtIndexPath(CCArray *rowAndColumnArray, FFIndexPath indexPath) {
    CCString *value = NULL;
    if (rowAndColumnArray->count() > indexPath.row) {
        CCArray *columnArray = (CCArray *)rowAndColumnArray->objectAtIndex(indexPath.row);
        if (columnArray->count() > indexPath.column) {
            value = (CCString *)columnArray->objectAtIndex(indexPath.column);
        }
    }
    return value;
}

/**
 *  读取该数组中某个indexPath下的int值
 *
 *  @param rowAndColumnArray 需要读取的二维数组
 *  @param indexPath         参见FFIndexPath，表示行列
 *
 *  @return 返回该行列下的int值
 */
static inline int intValueFromArrayAtIndexPath(CCArray *rowAndColumnArray, FFIndexPath indexPath) {
    CCString *value = valueFromArrayAtIndexPath(rowAndColumnArray, indexPath);
    if (value) {
        return value->intValue();
    }
    return 0;
}

/**
 *  读取该数组中某行某列的int值
 *
 *  @param rowAndColumnArray 需要读取的二维数组
 *  @param row               需要读取的行
 *  @param column            需要读取的列
 *
 *  @return 返回该行列下的int值
 */
static inline int intValueFromArrayAtRowAndColumn(CCArray *rowAndColumnArray, int row, int column) {
    return intValueFromArrayAtIndexPath(rowAndColumnArray, FFIndexPathMake(row, column));
}

/**
 *  地图中元素的类型，包括 障碍物，搬运工，目标，路线等
 */
typedef enum _ElementType {
    FFMapElementRedHouse         = 10,    // 红色的房子
    FFMapElementYellowHouse      = 11,    // 黄色的房子
    FFMapElementBlueHouse        = 12,    // 蓝色的房子
    FFMapElementBluePoolUp       = 13,    // 蓝色的纵向池塘上
    FFMapElementBluePoolDown     = 14,    // 蓝色的纵向池塘下
    FFMapElementBluePoolLeft     = 15,    // 蓝色的横向池塘左
    FFMapElementBluePoolRight    = 16,    // 蓝色的横向池塘右
    
    FFMapElementGreenTree        = 20,    // 绿色的树
    FFMapElementScenryTree       = 21,    // 风景树
    FFMapElementGreenShrub       = 22,    // 绿色的草垛
    FFMapElementYellowFlower     = 23,    // 黄色的花
    FFMapElementRedWall          = 30,    // 红色的墙
    FFMapElementRedBarricade     = 40,    // 红色的路障
    FFMapElementBox              = 60,    // 箱子
    FFMapElementGreenRoad        = 70,    // 绿色的路
    FFMapElementMan              = 80,    // 搬运工
    FFMapElementDst              = 90     // 目标，暂用泡泡表示
} FFMapElementType;

/**
 *  可以移动的类型
 */
typedef enum _MoveType {
    FFMoveDisabled,          // 不能移动
    FFMoveEnabledWithMan,    // 只能移动人
    FFMoveEnabledWithBoxMan  // 可以移动人和箱子
} FFMoveType;

class FFMapLayerDelegate
{
public:
    virtual void didGameStart() = 0;
    virtual void didGameFinish() = 0;
    virtual void didBoxManMovedWithBox(bool isWithBox) = 0;
};

class FFMapLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(FFMapLayer);
    
    void setDelegate(FFMapLayerDelegate *delegate);
    
    void loadMapWithLevel(FFLevel *level);
    void reloadMap();
    
private:
    FFMapLayerDelegate *m_pDelegate;
    
    void loadMap();
    FFIndexPath indexPathAtPoint(CCPoint point);
    CCPoint pointAtIndexPath(FFIndexPath indexPath);
    FFDirection directionFromPoint(CCPoint start, CCPoint end);
    FFMoveType shouldMoveWithDirection(FFDirection direction);
    void moveManWithDirection(FFDirection direction, FFIndexPath indexPath);
    void moveBoxWithDirection(FFDirection direction, FFIndexPath indexPath);
    void enabledTouch();
    void win();
    
protected:
    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
private:
    FFLevel *m_pLevel;                  //当前关数
    CCArray *m_pMapElements;            //地图中的数据
    int m_nRowCount;                    //共有几行
    int m_nColumnCount;                 //共有多少列
    FFBoxMan *m_pBoxMan;                //搬运工，保证地图中只有一个
    CCArray *m_pBoxes;                     //所有的箱子
    CCArray *m_pBoxArray;                  //箱子所在的位置
    CCArray *m_pDestArray;                 //目的地所在的位置
    CCPoint start;                     //移动的起点
    CCPoint end;                       //移动的终点
};

#endif
