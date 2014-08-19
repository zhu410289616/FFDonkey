//
//  FFLevel.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFLevel.h"
#include "FFFileManager.h"

FFLevel* FFLevel::levelWithDictionary(CCDictionary *dict)
{
    FFLevel *pLevel = new FFLevel(dict);
    if (pLevel) {
        pLevel->autorelease();
        return pLevel;
    }
    CC_SAFE_RELEASE(pLevel);
    return NULL;
}

FFLevel::FFLevel(CCDictionary *dict)
{
    std::string key = "level";
    this->m_nLevel = ((CCString *)dict->objectForKey(key))->intValue();
    key = "map";
    this->m_pMapName = (CCString *)dict->objectForKey(key);
    key = "background_music";
    this->m_pBackgroundMusic = (CCString *)dict->objectForKey(key);
    key = "push_effect";
    this->m_pPushEffect = (CCString *)dict->objectForKey(key);
    key = "win_effect";
    this->m_pWinEffect = (CCString *)dict->objectForKey(key);
    
    //
    this->m_pMapElements = CCArray::create();
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->m_pMapName->m_sString.c_str());
    std::string mapString = FFFileManager::readFileWithPath(path.c_str());
    this->m_pMapString = CCString::create(mapString);
    this->m_pMapString->retain();
    
    this->resetMapElements();
}

FFLevel::FFLevel()
{
}

FFLevel::~FFLevel()
{
}

void FFLevel::resetMapElements()
{
    std::string tempString = this->m_pMapString->m_sString;
    
    if (tempString.length() > 0) {
        
        this->m_pMapElements->removeAllObjects();
        
        const char *rowEndFlag = "\n";
        int rowBegin = 0;
        int rowPos = rowBegin;
        while ((rowPos = tempString.find_first_of(rowEndFlag, rowBegin)) != string::npos) {
            std::string rowString = tempString.substr(rowBegin, rowPos-rowBegin);
            CCLog("-------------- rowBegin: %d, rowPos: %d, rowString: \n%s", rowBegin, rowPos, rowString.c_str());
            
            CCArray *columnArray = CCArray::create();
            
            const char *columnEndFlag = ",";
            int columnBegin = 0;
            int columnPos = columnBegin;
            while ((columnPos = rowString.find_first_of(columnEndFlag, columnBegin)) != string::npos) {
                std::string columnString = rowString.substr(columnBegin, columnPos-columnBegin);
                CCLog("columnBegin: %d, columnPos: %d, columnString: %s", columnBegin, columnPos, columnString.c_str());
                
                CCString *element = CCString::create(columnString);
                columnArray->addObject(element);
                
                columnPos++;
                columnBegin = columnPos;
            }
            
            rowPos++;
            rowBegin = rowPos;
            
        }//while
    }//if
}
