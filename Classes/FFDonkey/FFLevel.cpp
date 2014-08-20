//
//  FFLevel.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFLevel.h"
#include "FFFileManager.h"

FFLevel* FFLevel::create(CCDictionary *dict)
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
    CCString *value = (CCString *)dict->objectForKey(key);
    this->m_nLevel = value->intValue();
    
    key = "map";
    value = (CCString *)dict->objectForKey(key);
    this->m_pMapName = new CCString(value->m_sString);
    
    key = "background_music";
    value = (CCString *)dict->objectForKey(key);
    this->m_pBackgroundMusic = new CCString(value->m_sString);
    
    key = "push_effect";
    value = (CCString *)dict->objectForKey(key);
    this->m_pPushEffect = new CCString(value->m_sString);
    
    key = "win_effect";
    value = (CCString *)dict->objectForKey(key);
    this->m_pWinEffect = new CCString(value->m_sString);
    
    //
    this->m_pMapElements = new CCArray();
    
    std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(this->m_pMapName->m_sString.c_str());
    std::string mapString = FFFileManager::readFileWithPath(path.c_str());
    this->m_pMapString = new CCString(mapString);
    CCLog("this->m_pMapString->retainCount(): %d", this->m_pMapString->retainCount());
    
    this->resetMapElements();
}

FFLevel::~FFLevel()
{
    CC_SAFE_RELEASE(this->m_pMapName);
    CC_SAFE_RELEASE(this->m_pBackgroundMusic);
    CC_SAFE_RELEASE(this->m_pPushEffect);
    CC_SAFE_RELEASE(this->m_pWinEffect);
    CC_SAFE_RELEASE(this->m_pMapElements);
    CC_SAFE_RELEASE(this->m_pMapString);
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
            
            this->m_pMapElements->addObject(columnArray);
            
            rowPos++;
            rowBegin = rowPos;
            
        }//while
    }//if
}
