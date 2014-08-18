//
//  FFFileManager.h
//  FFDonkey
//
//  Created by pig on 14-8-18.
//
//

#ifndef __FFDonkey__FFFileManager__
#define __FFDonkey__FFFileManager__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class FFFileManager : CCObject
{
public:
    static FFFileManager *sharedInstance();
    static FFFileManager *create();
    
    static string readFileWithPath(const char* pPath);
    static bool writeFileWithPath(char* pContent, const char* pPath);
    
private:
    FFFileManager();
    ~FFFileManager();
};

#endif /* defined(__FFDonkey__FFFileManager__) */
