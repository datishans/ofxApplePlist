//
//  ofxPlist.h
//  mySketch
//
//  Created by Hans Bijkerk on 09-03-17.
//
//
#pragma once

#include "ofMain.h"
#include "Poco/Any.h"

class ofxApplePlist {
    ofXml plist;
    Poco::Any toAny();
    
public:
    Poco::Any load(ofFile file);
    Poco::Any load(string plistdata);
};
