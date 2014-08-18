//
//  FFFileManager.cpp
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#include "FFFileManager.h"

static FFFileManager *instance = NULL;

FFFileManager* FFFileManager::sharedInstance()
{
    if (!instance) {
        instance = new FFFileManager();
    }
    return instance;
}

FFFileManager* FFFileManager::create()
{
    FFFileManager *pFileManager = new  FFFileManager();
    if (pFileManager) {
        pFileManager->autorelease();
        return pFileManager;
    }
    CC_SAFE_RELEASE(pFileManager);
    return NULL;
}

string FFFileManager::readFileWithPath(const char *pPath)
{
    CCLog("read path: %s", pPath);
    
    FILE *file = fopen(pPath, "r");
    if (file) {
        char *buf;
        int len;
        
        fseek(file, 0, SEEK_END);
        len = ftell(file);
        rewind(file);
        CCLog("count the file content len: %d", len);
        
        buf = (char *)malloc(sizeof(char) * len + 1);
        if (!buf) {
            CCLog("malloc space is not enough.");
            return NULL;
        }
        
        int rLen = fread(buf, sizeof(char), len, file);
        buf[rLen] = '\0';
        CCLog("has read length: %d", rLen);
        CCLog("has read content: \n%s", buf);
        
        string result = buf;
        fclose(file);
        free(buf);
        return result;
    } else {
        CCLog("[readFile: %s] open file error.", pPath);
    }
    
    return NULL;
}

bool FFFileManager::writeFileWithPath(char *pContent, const char *pPath)
{
    CCLog("write path: %s", pPath);
    
    FILE *file = fopen(pPath, "w");
    if (file) {
        fputs(pContent, file);
        fclose(file);
        return true;
    } else {
        CCLog("[writeFile: %s] open file error.", pPath);
    }
    
    return false;
}

FFFileManager::FFFileManager()
{}

FFFileManager::~FFFileManager()
{}


